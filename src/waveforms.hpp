#pragma once
#include <stdint.h>
#include "global.h"

namespace Waveform
{
    uint32_t square();
    uint32_t triangle(uint32_t phaseAcc);
    uint32_t sawtooth(uint32_t phaseAcc);
}
