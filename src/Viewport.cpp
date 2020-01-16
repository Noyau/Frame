#include "Viewport.h"

/////////////////////////////////////////////////
// VIEWPORT
/////////////////////////////////////////////////
Viewport::Viewport(size_t width, size_t height)
    :Viewport(0, 0, width, height)
{}

Viewport::Viewport(size_t x, size_t y, size_t width, size_t height)
    : m_X{ x }
    , m_Y{ y }
    , m_Width{ width }
    , m_Height{ height }
{}

Viewport::Viewport(const Viewport& other)
    : Viewport(other.m_X, other.m_Y, other.m_Width, other.m_Height)
{}

float Viewport::GetRatio() const
{
    return m_Width / static_cast<float>(m_Height);
}

void Viewport::Resize(size_t w, size_t h)
{
    m_Width = w;
    m_Height = h;
}

Viewport& Viewport::operator=(const Viewport& other)
{
    m_X = other.m_X;
    m_Y = other.m_Y;
    m_Width = other.m_Width;
    m_Height = other.m_Height;
    return *this;
}