// Stir Pins
#define MOTOR_PWM 10
#define FREQ_PIN 2

// Stir PID
#define stirKP 0.2
#define stirKI 0.0008
#define stirKD 0.0

// Motor Constants
#define NPULSES 70.0 // Number of pulses per revolution
#define FREQ_TO_RPM (60.0 / NPULSES)
#define RPM_MAX 1350 // Max RPM indicated by sensor (to mitigate any noise)
#define T_MIN (6e7/RPM_MAX/NPULSES)

// Heating Pins
#define HEATER_PWM 9 //to be changed
#define THERMISTOR 3 //to be changed

// Heating PID
#define heatKP 1.0 //to be changed
#define heatKI 0.0 //to be changed
#define heatKD 0.0 //to be changed
