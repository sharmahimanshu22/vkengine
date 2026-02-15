#pragma once

#include <vulkan/vulkan_core.h>
#include "vulkanobjects.h"


SyncResources createSyncObjects(VkDevice device, int MAX_FRAMES_IN_FLIGHT);