#include "recreateswapchain.h"
#include "vulkanobjects.h"
#include "cleanup.h"
#include "swapchain.h"
#include "swapchainimageviews.h"
#include "createdepthresources.h"
#include "createframebuffer.h"



void recreateSwapChain(VulkanContext ctx, GLFWwindow* window) {

  int width = 0, height = 0;
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(window, &width, &height);
    glfwWaitEvents();
  }
  
  vkDeviceWaitIdle(ctx.device);
  
  cleanupSwapChain(ctx);

    ctx.swapchaincontext = createSwapChain(ctx.physicalDevice, ctx.surface, window, ctx.device, ctx.queueFamilies);

    ctx.swapchainImageViews = createSwapChainImageViews(ctx.device, ctx.swapchaincontext.swapChainImages, ctx.swapchaincontext.swapChainImageFormat);

    ctx.depthImageResources = createDepthResources(ctx.device, ctx.physicalDevice, ctx.swapchaincontext.swapChainExtent);

    ctx.swapChainFramebuffers = createFramebuffers(ctx.device, ctx.swapchainImageViews, ctx.depthImageResources.depthImageView,
                                                    ctx.renderPass, ctx.swapchaincontext.swapChainExtent);
}