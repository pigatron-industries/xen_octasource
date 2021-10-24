
// Teensy Pins
#define CV_SELECT_PIN 10
#define CV_MOSI_PIN 11
#define CV_MISO_PIN 12
#define CV_SCLK_PIN 13
#define CV_INTERUPT 14
#define CV_CNVT_PIN 15
#if defined(OCTASOURCE_MKI)
    #define ENCODER_BTN_PIN 0
    #define ENCODER_PIN1 1
    #define ENCODER_PIN2 2
#endif
#if defined(OCTASOURCE_MKII)
    #define ENCODER_BTN_PIN 2
    #define ENCODER_PIN1 3
    #define ENCODER_PIN2 4
    #define GATE_OUTPUT_PIN 5
#endif

#define DAC1_SYNC_PIN 9
#define DAC2_SYNC_PIN 8

#define SCL_PIN 19
#define SDA_PIN 18
#define I2C_SPEED 1000000

// MAX11300 Pins
#define LENGTH_CV_PIN 3
#define LENGTH_POT_PIN 4
#define RATE_CV_PIN 5
#define RATE_POT_PIN 6
#define WAVE_CV_PIN 7
#define WAVE_POT_PIN 8
#define TRIGGER_IN_PIN 9

#define OUTPUT_CV_PIN_START 10
#define OUTPUT_CV_COUNT 8
#define OUTPUT_GATE_PIN 2
#define OUTPUT_GATE_TIME 10000

// Other config
#define SERIAL_BAUD 115200
#if defined(OCTASOURCE_MKI)
    #define SAMPLE_RATE 1000
#endif
#if defined(OCTASOURCE_MKII)
    #define SAMPLE_RATE 48000
#endif