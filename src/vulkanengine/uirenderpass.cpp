#include <stdexcept>
#include "uirenderpass.h"



// This does not include depth attachment unlike the main render pass
VkRenderPass createUIRenderPass(VkDevice device, VkFormat swapChainImageFormat) {
    VkRenderPass uiRenderPass;

    VkAttachmentDescription colorattachment = {};
    colorattachment.format = swapChainImageFormat;
    colorattachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorattachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    colorattachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorattachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorattachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorattachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    colorattachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment = {};
    color_attachment.attachment = 0;
    color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment;

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;  // or VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info.attachmentCount = 1;
    info.pAttachments = &colorattachment;
    info.subpassCount = 1;
    info.pSubpasses = &subpass;
    info.dependencyCount = 1;
    info.pDependencies = &dependency;
    if (vkCreateRenderPass(device, &info, nullptr, &uiRenderPass) != VK_SUCCESS) {
      throw std::runtime_error("Could not create Dear ImGui's render pass");
    }
    return uiRenderPass;
}

