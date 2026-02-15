#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"


void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VulkanContext ctx, MeshObject obj, int currentFrame);
