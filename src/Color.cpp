#include "Color.h"

/////////////////////////////////////////////////
// COLOR
/////////////////////////////////////////////////
Color::Color()
    : Color(0.f)
{}

Color::Color(float value)
    : Color(value, value, value)
{}

Color::Color(float r, float g, float b)
    : Color(r, g, b, 1.f)
{}

Color::Color(float r, float g, float b, float a)
    : m_R{ r }
    , m_G{ g }
    , m_B{ b }
    , m_A{ a }
{}