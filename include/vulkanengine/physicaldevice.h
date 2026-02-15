#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include "vulkanobjects.h"





const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};


PhysicalDeviceSelection pick_physical_device(const VkInstance& instance, const VkSurfaceKHR& surface);