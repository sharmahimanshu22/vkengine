#pragma once

#include <callbacks/windowcallbacks.h>



struct WinodowCallbackFunctions {
    GLFWframebuffersizefun frfun;
    GLFWmousebuttonfun mbfun;
    GLFWcursorposfun cpfun;
    GLFWcursorenterfun cefun;
    GLFWscrollfun scrollcbfun;
};


GLFWwindow* init_window(int width, int height)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

    return window;

    // glfwSetWindowUserPointer(window, &windowcallbackstate);

    // glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    // glfwSetCursorPosCallback(window, cursor_position_callback);
    // glfwSetMouseButtonCallback(window, mouse_button_callback);
    // glfwSetCursorEnterCallback(window, cursor_enter_callback);
    // glfwSetScrollCallback(window, scroll_callback);
    return window;
}