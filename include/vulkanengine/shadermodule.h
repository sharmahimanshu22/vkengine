#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

VkShaderModule createShaderModule(VkDevice device, const std::vector<char> &code);
