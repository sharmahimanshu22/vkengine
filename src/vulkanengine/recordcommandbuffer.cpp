#include "recordcommandbuffer.h"
#include <stdexcept>
#include <array>



void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VulkanContext ctx, MeshObject obj, int currentFrame) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  
  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }
  
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = ctx.renderPass;
  renderPassInfo.framebuffer = ctx.swapChainFramebuffers[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = ctx.swapchaincontext.swapChainExtent;
  
  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{0.0f, 1.0f, 1.0f, 1.0f}};
  clearValues[1].depthStencil = {1.0f, 0};
  
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();
  
  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, ctx.graphicsPipelineContext.graphicsPipeline);
  
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float) ctx.swapchaincontext.swapChainExtent.width;
  viewport.height = (float) ctx.swapchaincontext.swapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
  
  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = ctx.swapchaincontext.swapChainExtent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);    
  
  VkBuffer vertexBuffers[] = {obj.vertexBuffer};
  VkDeviceSize offsets[] = {0};
  
  if(obj.vertices.size() > 0) {
    std::cout << obj.vertices.size() << "  obj.vertices.size() \n\n\n";
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, obj.indexBuffer, 0, VK_INDEX_TYPE_UINT32);
  }
  
  vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, ctx.graphicsPipelineContext.pipelineLayout, 0, 1, &ctx.descriptorSets[currentFrame], 0, nullptr);
  

  vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(obj.indices.size()), 1, 0, 0, 0);
  //vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
  //vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
  
  vkCmdEndRenderPass(commandBuffer);

  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }
}