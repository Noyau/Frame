#pragma once

#include <string>

#include "Viewport.h"

struct GLFWwindow;

/////////////////////////////////////////////////
// FRAME
/////////////////////////////////////////////////
class Frame
{
    friend class FrameFactory;

protected:
    Frame(size_t width, size_t height, const std::string& title);

public:
    virtual ~Frame();

    void Run();

    // Callbacks
    virtual void OnResize(size_t w, size_t h);

protected:
    // Update
    virtual void OnUpdate(float deltaTime);
    virtual void OnRender();

protected:
    GLFWwindow* m_Window;
    float m_NearClip{ 1e-3f };
    float m_FarClip{ 1e+4f };
    Viewport m_Viewport;
};