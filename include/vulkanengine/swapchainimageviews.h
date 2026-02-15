#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

std::vector<VkImageView> createSwapChainImageViews(VkDevice device, const std::vector<VkImage>& images, VkFormat swapChainImageFormat);