#pragma once

#include <vulkan/vulkan_core.h>

#include "vulkanobjects.h"

GraphicsPipelineContext createGraphicsPipeline(const VkDevice &device, const VkDescriptorSetLayout &descriptorSetLayout,
                            const VkRenderPass &renderPass);