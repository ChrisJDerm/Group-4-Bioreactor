// Constants.h

// Stir Pins (existing)
#define MOTOR_PWM 10
#define FREQ_PIN 2

// Stir PID
#define stirKP 0.05
#define stirKI 0.0003
#define stirKD 0

// Motor Constants (existing)
#define NPULSES 70.0
#define FREQ_TO_RPM (60.0 / NPULSES)
#define RPM_MAX 1350
#define T_MIN (6e7/RPM_MAX/NPULSES)

// Heating Pins
#define HEATER_PWM 9
#define THERMISTOR_PIN A1

// Temperature Settings
#define TARGET_TEMP 19  // Target temperature in Celsius
#define MAX_TEMP 100.0    // Safety cutoff temperature
#define MIN_TEMP 0.0      // Minimum settable temperature

// Heating PID
#define heatKP 2    // Proportional gain
#define heatKI 0.0   // Integral gain
#define heatKD 0.0    // Derivative gain