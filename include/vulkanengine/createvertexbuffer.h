#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <vertex.h>
#include "bufferutils.h"


BufferResources createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, 
                        const std::vector<Vertex> vertices);

BufferResources createIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, 
                        const std::vector<uint32_t> indices);