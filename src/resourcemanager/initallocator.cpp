#include <vulkan/vulkan.hpp>
#include "vk_mem_alloc.h"
#include "resourcemanager/initallocator.h"

VmaAllocator allocator;

void initAllocator(vk::Instance instance,
                   vk::PhysicalDevice physicalDevice,
                   vk::Device device) {

    VmaAllocatorCreateInfo info{};
    info.instance = instance;
    info.physicalDevice = physicalDevice;
    info.device = device;

    vmaCreateAllocator(&info, &allocator);
}
