#pragma once

#include <vulkan/vulkan_core.h>


struct ImageResources {
    VkImage image;
    VkDeviceMemory imageMemory;
};

ImageResources createImage(VkDevice device, VkPhysicalDevice physicalDevice, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, 
    VkImageUsageFlags usage, VkMemoryPropertyFlags properties);

VkImageView createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

void transitionImageLayout(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, 
                            VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

void copyBufferToImage(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, 
                        VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);