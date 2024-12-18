// Constants.h

//STIRRING

// Stir Pins (existing)
#define MOTOR_PWM 11
#define FREQ_PIN 2

// Stir PID
#define stirKP 0.013
#define stirKI 0.0035
#define stirKD 0

// Motor Constants (existing)
#define NPULSES 70.0
#define FREQ_TO_RPM (60.0 / NPULSES)
#define RPM_MAX 1350
#define T_MIN (6e7/RPM_MAX/NPULSES)

// HEATING

// Heating Pins
#define HEATER_PWM 3
#define THERMISTOR_PIN A1

// Temperature Settings
#define TARGET_TEMP 19  // Target temperature in Celsius
#define MAX_TEMP 100.0    // Safety cutoff temperature
#define MIN_TEMP 0.0      // Minimum settable temperature

// Heating PID
#define heatKP 1.3    // Proportional gain
#define heatKI 0.0   // Integral gain
#define heatKD 0.0    // Derivative gain


// pH

// Pins
#define PH_IN_PIN A2

#define NUM_READINGS 5