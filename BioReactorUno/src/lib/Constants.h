// Stir Pins
#define MOTOR_PWM 10
#define FREQ_PIN 2

// Stir PID
#define stirKP 1.0
#define stirKI 0.0
#define stirKD 0.0

// Motor Constants
#define NPULSES 70 // Number of pulses per revolution
#define FREQ_TO_RPM (60 / NPULSES)
#define RPM_MAX 1500 // Max RPM indicated by sensor (to mitigate any noise)
#define T_MIN (6e7/RPM_MAX/NPULSES)