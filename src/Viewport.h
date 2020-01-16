#pragma once

/////////////////////////////////////////////////
// VIEWPORT
/////////////////////////////////////////////////
struct Viewport
{
    Viewport(size_t width, size_t height);
    Viewport(size_t x, size_t y, size_t width, size_t height);
    Viewport(const Viewport& other);

    Viewport& operator=(const Viewport& other);

    float GetRatio() const;

    void Resize(size_t w, size_t h);

    size_t m_X;
    size_t m_Y;
    size_t m_Width;
    size_t m_Height;
};