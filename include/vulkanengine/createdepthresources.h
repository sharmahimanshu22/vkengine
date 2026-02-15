#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"



DepthImageResources createDepthResources(VkDevice device, VkPhysicalDevice physicalDevice, VkExtent2D swapChainExtent);