#define NUMBER_OF_BUTTONS 4
#define BUTTONS_ACTIVE_LOW  true
#define BEEP_DURATION_MS  350
#define RandPort  22

#define Port_button_1 21
#define Port_button_2 19
#define Port_button_3 18
#define Port_button_4 5

#define Port_led_1  15
#define Port_led_2  2
#define Port_led_3  4
#define Port_led_4  16

#define Pushes 5

const int pin_buttons[NUMBER_OF_BUTTONS] = {Port_button_1, Port_button_2, Port_button_3, Port_button_4};
const int pin_leds[NUMBER_OF_BUTTONS] = {Port_led_1, Port_led_2, Port_led_3, Port_led_4};
const int pin_buzzer = 23;

const int freqs[NUMBER_OF_BUTTONS] = {440, 494, 523, 587}; // numbers are freq.
int vic_freq[] = {523, 659, 784, 1047, 988, 1047, 1175, 1319};
int vic_duration[] = {200, 200, 200, 400, 200, 200, 200, 600};
int loss_freq[] = {523, 494, 440, 392, 349, 330, 294, 262};
int loss_duration[] = {300, 300, 300, 300, 300, 300, 300, 600};

byte sequence[Pushes];
int current_seq_len;

byte randNum;


bool button_pressed(int button_number){
  int button_state = digitalRead(pin_buttons[button_number]);

  if(BUTTONS_ACTIVE_LOW){
    return (button_state == LOW);
  } else{
    return (button_state == HIGH);
  }
}

void beep(int freq){
  tone(pin_buzzer, freq);
  delay(BEEP_DURATION_MS);
  noTone(pin_buzzer);
}

void play_melody(int melody[], int duration[], int length, int pin_buz){
  for (int i = 0; i < length; i++){
    int time_play = duration[i];
    tone(pin_buz, melody[i], time_play);
    delay(time_play * 1.3);
  }
  noTone(pin_buz);
}

void test(){
  for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
    digitalWrite(pin_leds[i], HIGH);
    while(!button_pressed(i));
    beep(freqs[i]);
    digitalWrite(pin_leds[i], LOW);
  }
}

void game_init(){
  // start the game
  current_seq_len = 1;
  for (int i = 0; i < Pushes; i++){
    sequence[i] = random(NUMBER_OF_BUTTONS);
  }
}

int wait_button_press(){
  while(true){
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
      if (button_pressed(i)) return i;
    }
    delay(20);
  }
}

bool all_button_rel(){
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
    if (button_pressed(i)) return false;
  }
  return true;
}

void button_release(){
  while(!all_button_rel()){
    delay(20);
  }
}

void show_moves(){
  // shows the sequence 
  for (int i = 0; i < current_seq_len; i++){
    int j = sequence[i];
    digitalWrite(pin_leds[j], HIGH);
    beep(freqs[j]);
    digitalWrite(pin_leds[j], LOW);
    delay(BEEP_DURATION_MS);
    delay(200);
  }
}

bool read_moves(){
  // reads sequence from user
  for (int i = 0; i < current_seq_len; i++){
    int j = sequence[i];
    if (wait_button_press() != j) return false;
    digitalWrite(pin_leds[j], HIGH);
    beep(freqs[j]);
    digitalWrite(pin_leds[j], LOW);
    button_release();    
  }
  return true;
}

void game_won(){
  // win animation
  for (int j = 0; j < 2; j++){
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
      digitalWrite(pin_leds[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
     digitalWrite(pin_leds[i], LOW);
    }
  }
  

  play_melody(vic_freq, vic_duration ,8 , pin_buzzer);
  delay(3000);
  game_init();
}

void game_lost(){
  // lost animation
  for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
    digitalWrite(pin_leds[i], HIGH);
    delay(500);
    digitalWrite(pin_leds[i], LOW);
  }
  play_melody(loss_freq, loss_duration ,8 , pin_buzzer);
  delay(3000);
  game_init();
}

void setup(){
  for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
    pinMode(pin_buttons[i], INPUT_PULLUP);
    pinMode(pin_leds[i], OUTPUT);
  }
  pinMode(pin_buzzer, OUTPUT);

  randomSeed(analogRead(RandPort));

  //test();
  game_init();
}

void loop(){
  show_moves();
  if (!read_moves()){
     game_lost();
  }
  else if (current_seq_len == Pushes){
    game_won();
  } 
  else{
    current_seq_len++;
  }
  delay (1000);
}
