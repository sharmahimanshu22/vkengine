#pragma once

#include <vulkan/vulkan_core.h>

#include "imageutils.h"

ImageResources createTextureImage2(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, 
VkQueue graphicsQueue, int texWidth, int texHeight, int texChannels, void* pixels);

ImageResources createTextureImage(VkDevice device,  VkPhysicalDevice physicalDevice, VkCommandPool commandPool, 
VkQueue graphicsQueue);


VkImageView createTextureImageView(VkDevice device, VkImage textureImage);