#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include "vulkanobjects.h"

std::vector<VkDescriptorSet> createDescriptorSets(VkDevice device, int MAX_FRAMES_IN_FLIGHT, VkDescriptorSetLayout descriptorSetLayout,
                            VkDescriptorPool descriptorPool, std::vector<VkBuffer> uniformBuffers, TextureResources texture);