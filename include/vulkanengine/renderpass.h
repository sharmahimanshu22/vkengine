#pragma once

#include <vulkan/vulkan_core.h>


VkRenderPass createRenderPass(VkDevice device,VkPhysicalDevice physicalDevice,  VkFormat swapChainImageFormat);