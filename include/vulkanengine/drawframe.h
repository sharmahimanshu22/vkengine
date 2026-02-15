#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"


uint32_t drawFrame(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers, uint32_t currentFrame);