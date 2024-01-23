#include "TinyIRremote.h"
#include <Ultrasonic.h>

#include "Constants.h"

IRreceiver irx(IRrecPin);
IRData irResults;