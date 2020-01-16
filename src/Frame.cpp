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
    : m_Window{ nullptr }
    , m_Viewport{ width,height }
{
    m_Window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

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
        glClearColor(.1f, .1f, .2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        { // viewport
            glViewport(m_Viewport.m_X, m_Viewport.m_Y, m_Viewport.m_Width, m_Viewport.m_Height);
        }

        { // projection
            GLdouble r{ .5 * m_Viewport.m_Width };
            GLdouble t{ .5 * m_Viewport.m_Height };
            GLdouble l{ -r };
            GLdouble b{ -t };

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(l, r, b, t, m_NearClip, m_FarClip);
        }

        { // models
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            OnRender();
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

///////////////////////////////////////
// FRAME CALLBACKS
void Frame::OnResize(size_t w, size_t h)
{
    m_Viewport.m_Width = w;
    m_Viewport.m_Height = h;
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