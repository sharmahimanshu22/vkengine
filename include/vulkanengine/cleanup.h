#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"

void cleanupSwapChain(VulkanContext ctx);

void cleanup(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers  );