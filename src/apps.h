#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
//#include "controllers/FrequencySpreadController.h"
//#include "controllers/VoltageSpreadController.h"
#include "controllers/FilterController.h"
#include "controllers/clock/ClockController.h"
// #include "controllers/clock/ClockMultiplierController.h"
#include "controllers/EnvelopeController.h"
#include "controllers/BurstController.h"
#include "controllers/BouncingBallController.h"
#include "controllers/TrochoidController.h"
#include "controllers/AttractorController.h"
#include "controllers/PendulumController.h"
#include "controllers/ThreeBodyController.h"
#include "controllers/RandomController.h"
#include "controllers/sequencequantizer/SequenceQuantizerController.h"
#include "controllers/DelayController.h"
#include "controllers/CalibrationController.h"

#define CONTROLLERS \
PhasedController, \
FrequencyController, \
FilterController, \
ClockController, \
EnvelopeController, \
BurstController, \
BouncingBallController, \
TrochoidController, \
AttractorController, \
PendulumController, \
ThreeBodyController, \
RandomController, \
SequenceQuantizerController, \
DelayController, \
CalibrationController
