#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Frame.h"
#include "FrameFactory.h"

/////////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////////
static constexpr size_t FRAME_DEFAULT_WIDTH{ 640 };
static constexpr size_t FRAME_DEFAULT_HEIGHT{ 480 };
static const std::string FRAME_TITLE{ "Frame" };

/////////////////////////////////////////////////
// HELPERS (declaration)
/////////////////////////////////////////////////
static bool InitializeGLFW(int& result);
static bool InitializeGLEW(int& result);

/////////////////////////////////////////////////
// GLFW CALLBACKS (declaration)
/////////////////////////////////////////////////
static void ErrorCallback(int error, const char* description);

/////////////////////////////////////////////////
// MAIN
/////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    int result{ EXIT_SUCCESS };

    glfwSetErrorCallback(&ErrorCallback);

    if (!InitializeGLFW(result))
    {
        return result;
    }

    if (Frame* frame = FrameFactory::Create<Frame>(FRAME_DEFAULT_WIDTH, FRAME_DEFAULT_HEIGHT, FRAME_TITLE))
    {
        if (InitializeGLEW(result))
        {
            std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
            std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
            std::cout << "OpenGL shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

            frame->Run();
        }
        delete frame;
    }

    glfwTerminate();

    return result;
}

/////////////////////////////////////////////////
// GLEW HELPERS (definition)
/////////////////////////////////////////////////
bool InitializeGLFW(int& result)
{
    if (glfwInit() != GLFW_TRUE)
    {
        //const char* errorDescription;
        //int errorCode{ glfwGetError(&errorDescription) };
        //ErrorCallback(errorCode, errorDescription);
        result = EXIT_FAILURE;
        return false;
    }

    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
    return true;
}

bool InitializeGLEW(int& result)
{
    glewExperimental = GL_TRUE;

    GLenum res{ glewInit() };

    if (res != GLEW_OK)
    {
        std::cerr << "GLEW: " << glewGetErrorString(res) << std::endl;
        result = EXIT_FAILURE;
        return false;
    }

    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
    return true;
}

/////////////////////////////////////////////////
// GLFW CALLBACKS (definition)
/////////////////////////////////////////////////
void ErrorCallback(int error, const char* description)
{
    std::cerr << "GFLW Error(" << error << "): " << description << std::endl;
}