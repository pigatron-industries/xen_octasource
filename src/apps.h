#include "controllers/PhasedController.h"
#include "controllers/FrequencyController.h"
//#include "controllers/FrequencySpreadController.h"
//#include "controllers/VoltageSpreadController.h"
#include "controllers/FilterController.h"
#include "controllers/clock/ClockController.h"
#include "controllers/EnvelopeController.h"
#include "controllers/BurstController.h"
#include "controllers/physical/BouncingBallController.h"
#include "controllers/physical/PendulumController.h"
#include "controllers/physical/ThreeBodyController.h"
#include "controllers/attractor/ContinuousAttractorController.h"
#include "controllers/attractor/DiscreteAttractorController.h"
#include "controllers/TrochoidController.h"
#include "controllers/RandomController.h"
#include "controllers/ShapeController.h"
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
ContinuousAttractorController, \
DiscreteAttractorController, \
PendulumController, \
ThreeBodyController, \
ShapeController, \
RandomController, \
SequenceQuantizerController, \
DelayController, \
CalibrationController
