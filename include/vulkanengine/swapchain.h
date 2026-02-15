#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include "vulkanobjects.h"


//SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& device);

SwapChainContext createSwapChain(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface, GLFWwindow* window, VkDevice& device, 
    QueueFamilyIndices queueFamilies);
