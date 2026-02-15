#pragma once

#include <vulkan/vulkan_core.h>

VkDescriptorSetLayout createDescriptorSetLayout(const VkDevice &device);
VkDescriptorPool createDescriptorPool(VkDevice device, int MAX_FRAMES_IN_FLIGHT);