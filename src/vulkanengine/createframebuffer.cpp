#include "createframebuffer.h"


// WITH DEPTH ATTACHMENT
std::vector<VkFramebuffer> createFramebuffers(VkDevice device, const std::vector<VkImageView> &swapChainImageViews, const VkImageView &depthImageView, VkRenderPass renderPass,
    VkExtent2D swapChainExtent) {
  
  std::vector<VkFramebuffer> frameBuffers;
  frameBuffers.resize(swapChainImageViews.size());
  
  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    std::array<VkImageView, 2> attachments = {
      swapChainImageViews[i],
      depthImageView
    };
    
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;
    
    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &frameBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
  return frameBuffers;
}

// Without Depth Attachment
std::vector<VkFramebuffer> createUIFramebuffers(VkDevice device, const std::vector<VkImageView> &swapChainImageViews, VkRenderPass uiRenderPass,
    VkExtent2D swapChainExtent) {
  
  std::vector<VkFramebuffer> uiFrameBuffers;
  uiFrameBuffers.resize(swapChainImageViews.size());
  
  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    
    VkFramebufferCreateInfo uiFramebufferInfo{};
    uiFramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    uiFramebufferInfo.renderPass = uiRenderPass;
    uiFramebufferInfo.attachmentCount = 1;
    uiFramebufferInfo.pAttachments = &swapChainImageViews[i];
    uiFramebufferInfo.width = swapChainExtent.width;
    uiFramebufferInfo.height = swapChainExtent.height;
    uiFramebufferInfo.layers = 1;
    
    if (vkCreateFramebuffer(device, &uiFramebufferInfo, nullptr, &uiFrameBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("failed to create framebuffer!");
    }
  }
  return uiFrameBuffers;
}