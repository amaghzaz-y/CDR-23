#pragma once

#include "version.h"
#include "RotateControlBase.h"
#include "StepControlBase.h"
#include "accelerators/LinRotAccelerator.h"
#include "accelerators/LinStepAccelerator.h"
#include "Arduino.h"
#include "timer/esp32/TimerField.h"

using MotorControl = MotorControlBase<TimerField>;

using RotateControl = RotateControlBase<LinRotAccelerator, TimerField>;
using StepControl = StepControlBase<LinStepAccelerator, TimerField>;
