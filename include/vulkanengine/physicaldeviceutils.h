#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include "vulkanobjects.h"

VkFormat findSupportedFormat( const VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, 
  VkImageTiling tiling, VkFormatFeatureFlags features) ;

VkFormat findDepthFormat( VkPhysicalDevice physicalDevice);

uint32_t findMemoryType(VkPhysicalDevice physicalDevice,uint32_t typeFilter, VkMemoryPropertyFlags properties);

SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);