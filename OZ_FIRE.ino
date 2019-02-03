#include <Adafruit_NeoPixel.h>

#define COLOR_COUNT 10
#define LED_PIN 6
#define FAN_PIN 11
#define NUMPIXELS 8
#define BUTTON_PIN 2

//FSM states
#define S_OFF 0
#define S_FADE_UP 1
#define S_RUN 2
#define S_FADE_OUT 3

//Button states
#define BTN_UP 0
#define BTN_DOWN 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t colors[] = {
  pixels.Color(200, 20, 0, 0),
  pixels.Color(200, 10, 0, 0),
  pixels.Color(200, 0, 0, 0),
  pixels.Color(155, 5, 0, 0),
  pixels.Color(155, 0, 0, 0),
  pixels.Color(100, 0, 0, 0),
  pixels.Color(50, 0, 0, 0),
  pixels.Color(25, 0, 0, 0),
  pixels.Color(0, 0, 4, 0), //Blue
  pixels.Color(5, 0, 0, 0),
  pixels.Color(80, 30, 0, 0),
  pixels.Color(150, 15, 0, 7),
  pixels.Color(100, 20, 0, 10),
  pixels.Color(0, 0, 0, 25),
  pixels.Color(0, 0, 0, 0),
};

uint8_t current_colors[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t *current_color = current_colors;
uint8_t out_state = 0;
uint8_t max_led_level = 255;
uint8_t led_level = 0;
uint8_t led_var = 255;
uint8_t max_fan_level = 255;
uint8_t fan_level = 0;
uint8_t fan_var = 12;
uint8_t fan_min = 64;
uint8_t step_delay = 2;

long debounce_timer = 0;
long debounce_time = 50; //50 ms.
bool button_pressed = false;
int last_button_state;
int button_state;
bool need_up_debounce = true;

byte state;

void setup() {
  state = S_OFF;
  //Need some good random.
  randomSeed(analogRead(0));

  pixels.begin(); // This initializes the NeoPixel library.
  // now we turn off the neopixels
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, 0,0,0,0); // Off
  }

  pixels.show(); // This sends the updated pixel color to the hardware.
  pinMode(FAN_PIN,OUTPUT);
}

void loop() {
  //debounce the Button. 
  if (digitalRead(BUTTON_PIN)){
    button_state = BTN_DOWN;
  } else {
    button_state = BTN_UP;
  }

  if (button_state != last_button_state){
    debounce_timer = millis(); //reset timer
  } else {
    if(millis() - debounce_timer > debounce_time){
      if(button_state == BTN_DOWN & need_up_debounce == false){
        button_pressed = true;
        need_up_debounce = true;
      } else if (button_state == BTN_UP){
        need_up_debounce = false;
      }
    }
  }
  last_button_state = button_state;

  //Manage update of state
  if(state == S_OFF){
    if (button_pressed){
      state = S_FADE_UP;
      button_pressed = false;
    }
    fan_level = fan_min -1;
    led_level = 0;
  } else if (state == S_FADE_UP) {
    if (button_pressed){
      state = S_RUN;
      button_pressed = false;
    }
    if (led_level < max_led_level) led_level++;
    if (fan_level < max_fan_level) fan_level++;
    if (fan_level >= max_fan_level & led_level >= max_led_level) state = S_RUN;
    delay(step_delay);
  } else if (state == S_RUN) {
    if (button_pressed){
      state = S_FADE_OUT;
      button_pressed = false;
    }
  } else if (state == S_FADE_OUT) {
    if (button_pressed){
      state = S_OFF;
      button_pressed = false;
    }
    if(led_level > 0) led_level--;
    if(fan_level >= fan_min) fan_level--;
    if(fan_level <= fan_min) fan_level = 0;
    if(fan_level == 0 & led_level == 0) state = S_OFF;
  }
  //Update effects
  fanUpdate(fan_level);
  flameGen(colors, current_color , COLOR_COUNT, led_level, led_var);
  delay(100);
}

void fanUpdate( uint8_t level){
  if(level < fan_min){
     analogWrite(FAN_PIN,0);
  } else if (level < fan_min + fan_var) {
    analogWrite(FAN_PIN, level);
  } else {
    analogWrite(FAN_PIN, level - rand(fan_var));
  }
}

void flameGen(uint32_t colors[COLOR_COUNT], uint8_t current_color[NUMPIXELS], uint8_t color_count, uint8_t Bright, uint8_t led_var) {
  int update_count = (int)random(led_var & 7);
  for (int i = 0; i < update_count; i++) {
    int led = random(NUMPIXELS) ;
    pixels.setPixelColor(led, colors[(int)random(led_var & 15)]);
  }
  pixels.setBrightness(Bright);
  pixels.show();
}

int genNewColor(int color, uint8_t led_var) {
  int distance = (int)random(led_var);
  color += distance;
  if (color > COLOR_COUNT) {
    color = 0;
  }
  return color;
}
