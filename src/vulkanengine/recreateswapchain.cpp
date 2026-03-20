#include "recreateswapchain.h"
#include "vulkanobjects.h"
#include "cleanup.h"
#include "swapchain.h"
#include "swapchainimageviews.h"
#include "createdepthresources.h"
#include "createframebuffer.h"



void recreateSwapChain(VulkanContext ctx, VulkanDeviceAndQueueContext dqcontext, GLFWwindow* window) {

  int width = 0, height = 0;
  while (width == 0 || height == 0) {
    glfwGetFramebufferSize(window, &width, &height);
    glfwWaitEvents();
  }
  
  vkDeviceWaitIdle(dqcontext.device);
  
  cleanupSwapChain(ctx, dqcontext);

    ctx.swapchaincontext = createSwapChain(dqcontext.physicalDevice, dqcontext.surface, window, dqcontext.device, dqcontext.queueFamilies);

    ctx.swapchainImageViews = createSwapChainImageViews(dqcontext.device, ctx.swapchaincontext.swapChainImages, ctx.swapchaincontext.swapChainImageFormat);

    ctx.depthImageResources = createDepthResources(dqcontext.device, dqcontext.physicalDevice, ctx.swapchaincontext.swapChainExtent);

    ctx.swapChainFramebuffers = createFramebuffers(dqcontext.device, ctx.swapchainImageViews, ctx.depthImageResources.depthImageView,
                                                    ctx.renderPass, ctx.swapchaincontext.swapChainExtent);
}