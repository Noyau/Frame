#pragma once

#include <string>

#include "Camera.h"
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
    virtual void OnResize(size_t width, size_t height);

protected:
    // Update
    virtual void OnUpdate(float deltaTime);
    virtual void OnRender();

protected:
    GLFWwindow* m_Window;
    Camera m_Camera;
};