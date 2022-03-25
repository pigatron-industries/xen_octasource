#include "Controls.h"

AnalogGateInput<AnalogInputPinT> Controls::syncInput = AnalogGateInput<AnalogInputPinT>(Hardware::hw.syncCvPin);
BipolarExpInput<AnalogInputSumPinT> Controls::bipolarRateCvInput = BipolarExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
ExpInput<AnalogInputSumPinT> Controls::expRateCvInput = ExpInput<AnalogInputSumPinT>(Hardware::hw.rateSumPin);
LinearInput<AnalogInputSumPinT> Controls::ampCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.ampSumPin, -5, 5, 0, 5);
LinearInput<AnalogInputSumPinT> Controls::waveCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.waveSumPin, -5, 5, 0, 5);
#if defined(OCTASOURCE_MKII)
    LinearInput<AnalogInputSumPinT> Controls::phaseCvInput = LinearInput<AnalogInputSumPinT>(Hardware::hw.phaseSumPin, -5, 5, 0, 5);
#endif

TriggerOutput<DigitalOutputDeviceT> Controls::triggerOutput = TriggerOutput<DigitalOutputDeviceT>(Hardware::hw.gateOutPin, 20000);
