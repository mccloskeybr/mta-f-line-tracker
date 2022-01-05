#define DEBUG true

#define WIFI_CHECK_DELAY_MILLIS 1000
#define LED_DELAY_TIME_MICROS 10

#define SELECT_0 6
#define SELECT_1 7
#define SELECT_2 8
#define SELECT_3 9
#define ENABLE_0 10
#define ENABLE_1 11
#define ENABLE_2 12

#define NUM_LEDS 90
#define NUM_SELECTOR_PINS 7

#define MAX_NUM_ENABLED_LEDS 4

// cache of relevant pin enablement combinations to light a LED.
// i.e. LED_0 is turned on by calling updateLeds(select_arr_cache[0]).
bool** select_arr_cache;

// the LEDs that should be turned on.
byte* enabled_leds;

/*
 * Update LEDs given boolean array.
 */
void updateLeds(const bool* select_arr) {
  digitalWrite(SELECT_0, select_arr[0]);
  digitalWrite(SELECT_1, select_arr[1]);
  digitalWrite(SELECT_2, select_arr[2]);
  digitalWrite(SELECT_3, select_arr[3]);
  digitalWrite(ENABLE_0, select_arr[4]);
  digitalWrite(ENABLE_1, select_arr[5]);
  digitalWrite(ENABLE_2, select_arr[6]);
}

/*
 * Convert integer into boolean array representation.
 * i.e. 0b...0101 -> [..., 0, 1, 0, 1].
 */
void convertLedIndexToSelectArray(byte led_index, bool* select_arr, int select_arr_size) {  
  for (int i = 0; i < select_arr_size; i++) {
    // ith element is ith bit in orig number.
    select_arr[i] = (led_index >> i) & 1;
  }
}

/**
 * Creates a 2d array of all select arrays of length cache_size and width arr_size.
 */
bool** createSelectArrayCache(int cache_size, int arr_size) {
  bool** select_arr_cache = (bool**) malloc(cache_size * sizeof(bool *));
  for(int i = 0; i < cache_size; i++) {
    *select_arr_cache = (bool*) malloc(arr_size * sizeof(bool));
    convertLedIndexToSelectArray(i, *select_arr_cache, arr_size);
  }
  return select_arr_cache;
}

/**
 * Determines which LEDs should be on.
 */
void updateEnabledLeds(byte* enabled_leds) {
  enabled_leds[0] = 0;
  enabled_leds[1] = 2;
  enabled_leds[2] = 16;
  enabled_leds[3] = 18;
}

/*
 * Creates an array to be used to save which leds should be enabled.
 */
byte* createEnabledLeds(int enabled_leds_size) {
  enabled_leds = (byte*) malloc(enabled_leds_size * sizeof(byte));
}


void setup() {
  Serial.begin(57600);
  
  pinMode(SELECT_0, OUTPUT);
  pinMode(SELECT_1, OUTPUT);
  pinMode(SELECT_2, OUTPUT);
  pinMode(SELECT_3, OUTPUT);
  pinMode(ENABLE_0, OUTPUT);
  pinMode(ENABLE_1, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);

  // create cache once instead of calculating combos multiple times a loop.
  select_arr_cache = createSelectArrayCache(NUM_LEDS, NUM_SELECTOR_PINS);
  enabled_leds = createEnabledLeds(MAX_NUM_ENABLED_LEDS);
}

void loop() {
  unsigned long start_time = millis();
  
  updateEnabledLeds(enabled_leds);

  // only check the MTA API every so often.
  while (millis() - start_time < WIFI_CHECK_DELAY_MILLIS) {
    // cycle lit LEDs to give the illusion we're actually lighting multiple at once.
    for (int i = 0; i < MAX_NUM_ENABLED_LEDS; i++) {
      updateLeds(select_arr_cache[enabled_leds[i]]);
      delayMicroseconds(LED_DELAY_TIME_MILLIS);
    }
  }
}
