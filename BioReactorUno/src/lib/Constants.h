// Stir Pins
#define MOTOR_PWM 10
#define FREQ_PIN 2

// Stir PID
#define stirKP 0.1
#define stirKI 0.0
#define stirKD 0

// Motor Constants
#define NPULSES 70.0 // Number of pulses per revolution
#define FREQ_TO_RPM (60.0 / NPULSES)
#define RPM_MAX 1350 // Max RPM indicated by sensor (to mitigate any noise)
#define T_MIN (6e7/RPM_MAX/NPULSES)