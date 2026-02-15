#include "createdepthresources.h"
#include "physicaldeviceutils.h"
#include "imageutils.h"


DepthImageResources createDepthResources(VkDevice device, VkPhysicalDevice physicalDevice, VkExtent2D swapChainExtent) {
    DepthImageResources depthImageResources;

    VkFormat depthFormat = findDepthFormat(physicalDevice);
  
    ImageResources imageresources = createImage(device, physicalDevice, swapChainExtent.width, swapChainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL,
	      VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    depthImageResources.depthImage = imageresources.image;
    depthImageResources.depthImageMemory = imageresources.imageMemory;
    depthImageResources.depthImageView = createImageView(device, imageresources.image, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
    return depthImageResources;
}