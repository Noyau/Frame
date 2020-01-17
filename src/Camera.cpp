#include "Camera.h"

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/////////////////////////////////////////////////
// CAMERA
/////////////////////////////////////////////////
Camera::Camera(size_t width, size_t height)
    : m_Viewport{ width,height }
{}

void Camera::Resize(size_t width, size_t height)
{
    m_Viewport.Resize(width, height);
}

void Camera::Render() const
{
    { // setup viewport
        glViewport(m_Viewport.m_X, m_Viewport.m_Y, m_Viewport.m_Width, m_Viewport.m_Height);
    }

    { // setup projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        switch (m_ProjectionMode)
        {
        case ProjectionMode::Orthographic:
            SetupOrthographicProjection();
            break;
        case ProjectionMode::Perspective:
            SetupPerspectiveProjection();
            break;
        default:
            throw std::string{ "Invalid projection mode!" };
        }
    }

    { // begin render
        SetupBackground();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
}

void Camera::SetupOrthographicProjection() const
{
    //const GLdouble r{ .5 * m_Viewport.m_Width };
    //const GLdouble t{ .5 * m_Viewport.m_Height };
    //const GLdouble l{ -r };
    //const GLdouble b{ -t };

    const float aspect{ m_Viewport.GetRatio() };

    const GLdouble r{ .5 * m_Orthographic.m_Size };
    const GLdouble t{ aspect * r };
    const GLdouble l{ -r };
    const GLdouble b{ -t };

    glOrtho(l, r, b, t, m_NearClip, m_FarClip);
}

void Camera::SetupPerspectiveProjection() const
{
    gluPerspective(m_Perspective.m_Fov, m_Viewport.GetRatio(), m_NearClip, m_FarClip);
}

void Camera::SetupBackground() const
{
    const Color& color{ m_Background.m_Color };
    glClearColor(color.m_R, color.m_G, color.m_B, color.m_A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}