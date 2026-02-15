#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

std::vector<VkFramebuffer> createFramebuffers(VkDevice device, const std::vector<VkImageView> &swapChainImageViews, 
    const VkImageView &depthImageView, VkRenderPass renderPass, VkExtent2D swapChainExtent);

std::vector<VkFramebuffer> createUIFramebuffers(VkDevice device, const std::vector<VkImageView> &swapChainImageViews, VkRenderPass uiRenderPass,
    VkExtent2D swapChainExtent);