#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"

void recreateSwapChain(VulkanInstance vkinstance, VulkanContext ctx, VulkanDeviceAndQueueContext dqcontext, GLFWwindow* window);