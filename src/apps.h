#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
#include "controllers/FilterController.h"
#include "controllers/ClockController.h"
#include "controllers/ClockMultiplierController.h"
#include "controllers/EnvelopeController.h"
#include "controllers/BurstController.h"
#include "controllers/BouncingBallController.h"
#include "controllers/AttractorController.h"
#include "controllers/PendulumController.h"
#include "controllers/ThreeBodyController.h"
#include "controllers/RandomController.h"
#include "controllers/QuantizerController.h"
#include "controllers/DelayController.h"
#include "controllers/VoltageReferenceController.h"

#define CONTROLLERS \
PhasedController, \
FrequencyController, \
FilterController, \
ClockController, \
ClockMultiplierController, \
EnvelopeController, \
BurstController, \
BouncingBallController, \
AttractorController, \
PendulumController, \
ThreeBodyController, \
RandomController, \
QuantizerController, \
DelayController, \
VoltageReferenceController
