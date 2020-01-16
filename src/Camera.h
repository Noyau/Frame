#pragma once

#include "Color.h"
#include "Viewport.h"

/////////////////////////////////////////////////
// PROJECTION MODE
/////////////////////////////////////////////////
enum class ProjectionMode
{
    Orthographic,
    Perspective,
};

/////////////////////////////////////////////////
// CAMERA
/////////////////////////////////////////////////
class Camera
{
public:
    Camera(size_t width, size_t height);

    void Resize(size_t width, size_t height);

    void Render() const;

private:
    void SetupOrthographicProjection() const;
    void SetupPerspectiveProjection() const;
    void SetupBackground() const;

private:
    ProjectionMode m_ProjectionMode{ ProjectionMode::Orthographic };
    float m_NearClip{ 1e-3f };
    float m_FarClip{ 1e+4f };
    Viewport m_Viewport;
    struct
    {
        Color m_Color{ ColorConstant::Black };
    } m_Background;
    struct
    {
        float m_Size{ 50.f };
    } m_Orthographic;
    struct
    {
        float m_Fov{ 60.f }; // degrees
    } m_Perspective;
};