#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>



VkInstance create_instance(bool enableValidationLayers, const std::vector<const char *> validationLayers);

bool checkValidationLayerSupport();

std::vector<const char *> getRequiredExtensions(bool enableValidationLayers);

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                             const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);

VkDebugUtilsMessengerEXT setup_debug_messenger(const VkInstance vkinstance, bool enableValidationLayers);

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
