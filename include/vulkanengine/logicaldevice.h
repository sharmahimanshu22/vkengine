#pragma once

#include <vulkan/vulkan_core.h>
#include "physicaldevice.h"

struct DeviceSelection {
    VkDevice device{};
    VkQueue graphicsQueue{};
    VkQueue presentQueue{};
};

DeviceSelection create_logical_device(const VkPhysicalDevice& physicalDevice, const QueueFamilyIndices& _queueFamilyIndices, 
    bool enableValidationLayers, const std::vector<const char *> validationLayers);