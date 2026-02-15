#include "vksurface.h"
#include <stdexcept>

VkSurfaceKHR create_surface(const VkInstance& instance, GLFWwindow* window)
{
    VkSurfaceKHR surface;

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }
    return surface;
}