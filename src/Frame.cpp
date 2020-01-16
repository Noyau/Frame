#include "Frame.h"

#include <GLFW/glfw3.h>

/////////////////////////////////////////////////
// GLFW CALLBACKS (declaration)
/////////////////////////////////////////////////
static Frame* GetFrameFromWindow(const GLFWwindow* window);
static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

/////////////////////////////////////////////////
// FRAME
/////////////////////////////////////////////////
Frame::Frame(size_t width, size_t height, const std::string& title)
    : m_Window{ m_Window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr) }
    , m_Camera{ width,height }
{
    if (m_Window != nullptr)
    {
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, this);

        glfwSetFramebufferSizeCallback(m_Window, &FramebufferSizeCallback);
    }
}

Frame::~Frame()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

void Frame::Run()
{
    double t0{ glfwGetTime() };

    while (glfwWindowShouldClose(m_Window) != GLFW_TRUE)
    {
        double t1{ glfwGetTime() };
        float dt{ static_cast<float>(t1 - t0) };
        t0 = t1;

        // Updating
        OnUpdate(dt);

        // Rendering
        m_Camera.Render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

///////////////////////////////////////
// FRAME CALLBACKS
void Frame::OnResize(size_t width, size_t height)
{
    m_Camera.Resize(width, height);
}

///////////////////////////////////////
// FRAME UPDATE
void Frame::OnUpdate(float /*deltaTime*/)
{}

void Frame::OnRender()
{}

/////////////////////////////////////////////////
// GLFW CALLBACKS (definition)
/////////////////////////////////////////////////
Frame* GetFrameFromWindow(const GLFWwindow* window)
{
    return static_cast<Frame*>(glfwGetWindowUserPointer(const_cast<GLFWwindow*>(window)));
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    if (Frame* frame = GetFrameFromWindow(window))
    {
        size_t w{ static_cast<size_t>(width) };
        size_t h{ static_cast<size_t>(height) };
        frame->OnResize(w, h);
    }
}