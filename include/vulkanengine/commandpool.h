#pragma once

#include <vulkan/vulkan_core.h>
#include <vulkanengine/physicaldevice.h>
#include <vector>
#include "vulkanobjects.h"

struct CommandResources {
    VkCommandPool commandPool{};
    std::vector<VkCommandBuffer> commandBuffers{};
};

VkCommandPool createCommandPool(VkDevice device, QueueFamilyIndices queueFamilyIndices);