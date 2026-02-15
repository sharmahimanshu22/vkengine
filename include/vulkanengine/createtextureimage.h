#pragma once

#include <vulkan/vulkan_core.h>

#include "imageutils.h"

ImageResources createTextureImage(VkDevice device,  VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue);

VkImageView createTextureImageView(VkDevice device, VkImage textureImage);