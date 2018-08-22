

// reader..

// calculations
// tire radius ~ 12.1 inches
// circumference = pi*2*r =~85 inches
// max speed of 35mph =~ 616inches/second
// max rps =~7.25

// wheel measurements
//                      radius == 12.1"
//              diameter (r*2) =~ 24.2" 61.47
//              diameter in cm = 61.47cm 
// circumfrence in cm (pi*r*2) =~ pi*61.47cm = 193.11cm
//
// 160934.4 cm per mile. * 100 = 16093440
//
// 16093440  / circumference = rotations per hour
//
// so: 16093440 / 193 =~ 83385
//
//
// 83385 / 60 / 60 = revolutions per second
//
// max RPS = 23.16 rps

// hall effect sensor config
byte oldSwitchState = LOW;
//const unsigned long debounceTime = 10;
unsigned long switchPressTime;
long countHESOpen;
long countHESClosed;
int mph;

// at 100mph, 1 rotation takes: 1000ms / 23.16rps =~ 44ms
// if we get a read more often than ~44ms then disregard it.
int debounceHESMs = 45;


