#ifndef FLEW_COLOR_H
#define FLEW_COLOR_H

#include "config.h"
#include <stdint.h>

FL_ENTER

template<typename Color>
struct ColorRGB
{
    static const uint32_t value = Color::value;
};


struct Red
{
    static const uint32_t value = 0xff0000;
};

struct Green
{
    static const uint32_t value = 0x00ff00;
};

struct Blue
{
    static const uint32_t value = 0x0000ff;
};

struct Black
{
    static const uint32_t value = 0x000000;
};

struct White
{
    static const uint32_t value = 0xffffff;
};


FL_LEAVE

#endif
