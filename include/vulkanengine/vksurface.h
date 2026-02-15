#pragma once

#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>

VkSurfaceKHR create_surface(const VkInstance& instance, GLFWwindow* window);
