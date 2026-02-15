#pragma once

#include <vulkan/vulkan_core.h>

struct BufferResources {
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
};

BufferResources createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
bool copyBuffer(VkDevice device, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool, VkQueue graphicsQueue);