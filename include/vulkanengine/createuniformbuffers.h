#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"


UniformBufferResources createUniformBuffers(VkDevice device, VkPhysicalDevice physicalDevice,  int MAX_FRAMES_IN_FLIGHT);