#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"

void cleanupSwapChain(VulkanContext ctx, VulkanDeviceAndQueueContext dqcontext);

void cleanup(VulkanContext ctx, VulkanInstance vkinstance, VulkanDeviceAndQueueContext dqcontext, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers  );