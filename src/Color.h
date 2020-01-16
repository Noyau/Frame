#pragma once

/////////////////////////////////////////////////
// COLOR
/////////////////////////////////////////////////
struct Color
{
    Color();
    Color(float value);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);

    union
    {
        struct
        {
            float m_R;
            float m_G;
            float m_B;
            float m_A;
        };
        float m_Data[4];
    };
};

/////////////////////////////////////////////////
// COLOR CONSTANT
/////////////////////////////////////////////////
namespace ColorConstant
{
const Color Clear{ 0.f,0.f,0.f,0.f };

const Color Black{ 0.f,0.f,0.f,1.f };
const Color White{ 1.f,1.f,1.f,1.f };

const Color Red{ 1.f,0.f,0.f,1.f };
const Color Green{ 0.f,1.f,0.f,1.f };
const Color Blue{ 0.f,0.f,1.f,1.f };

const Color Yellow{ 1.f,1.f,0.f,1.f };
const Color Cyan{ 0.f,1.f,0.f,1.f };
const Color Magenta{ 1.f,0.f,1.f,1.f };
}