#include "swapchainimageviews.h"
#include "imageutils.h"
#include <stdexcept>
#include <vector>




std::vector<VkImageView> createSwapChainImageViews(VkDevice device, const std::vector<VkImage>& images, VkFormat swapChainImageFormat)
{
    std::vector<VkImageView> swapChainImageViews(images.size());

    for (uint32_t i = 0; i < images.size(); i++)
    {
        swapChainImageViews[i] = createImageView(device, images[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
    }
    return swapChainImageViews;
}

/*
void createTextureImageView()
{
    textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
}
*/


