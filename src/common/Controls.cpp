#include "Controls.h"

AnalogGateInput<OctasourceInputDevice> Controls::syncInput = AnalogGateInput<OctasourceInputDevice>(Hardware::hw.syncCvPin);
BipolarExpInput<OctasourceInputDevice> Controls::bipolarRateCvInput = BipolarExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);
ExpInput<OctasourceInputDevice> Controls::expRateCvInput = ExpInput<OctasourceInputDevice>(Hardware::hw.rateCvPin);

LinearInput<OctasourceInputDevice> Controls::ampCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.ampCvPin, -5, 5, 0, 5);

// mod 1
LinearInput<OctasourceInputDevice> Controls::waveCvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.waveCvPin, -5, 5, 0, 5);

// mod 2
#if defined(OCTASOURCE_MKII)
    LinearInput<OctasourceInputDevice> Controls::mod2CvInput = LinearInput<OctasourceInputDevice>(Hardware::hw.phaseCvPin, -5, 5, 0, 5);
#endif

TriggerOutput<OctasourceInputDevice> Controls::triggerOutput = TriggerOutput<OctasourceInputDevice>(Hardware::hw.gateOutPin, 20000);
