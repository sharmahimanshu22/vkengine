#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

std::vector<VkCommandBuffer> createCommandBuffer(VkDevice device, VkCommandPool commandPool, const int MAX_FRAMES_IN_FLIGHT);