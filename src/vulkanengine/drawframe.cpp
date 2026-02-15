#include "drawframe.h"
#include "vulkanobjects.h"
#include <stdexcept>
#include "recreateswapchain.h"
#include "recordcommandbuffer.h"


uint32_t drawFrame(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers, uint32_t currentFrame) {
  vkWaitForFences(ctx.device, 1, &ctx.syncresources.inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
  
  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(ctx.device, ctx.swapchaincontext.swapChain, UINT64_MAX, ctx.syncresources.imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
  
  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain(ctx, window);
    //ImGui_ImplVulkan_SetMinImageCount(swapChainImageViews.size());
    // TODO: Do we need to take care of anything related to UI ?
    return currentFrame;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }
  
  //updateUniformBuffer(currentFrame);    
  vkResetFences(ctx.device, 1, &ctx.syncresources.inFlightFences[currentFrame]);
  
  //bool show_demo_window = true;
  //ImVec4 clear_color = ImVec4(0.45f, 0.1f, 0.10f, 1.00f);
  //ImGui_ImplVulkan_NewFrame();
  //ImGui_ImplGlfw_NewFrame();
  //ImGui::NewFrame();
  //setupImgui();
  //ImGui::ShowDemoWindow(&show_demo_window);
  //ImGui::Render();
  
  vkResetCommandBuffer(ctx.commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
  //vkResetCommandBuffer(uiCommandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
  
  recordCommandBuffer(ctx.commandBuffers[currentFrame], imageIndex, ctx, m, currentFrame);
  //recordUICommandBuffer(uiCommandBuffers[currentFrame], imageIndex);
  
  std::array<VkCommandBuffer, 1> submitCommandBuffers = { ctx.commandBuffers[currentFrame]}; // uiCommandBuffers[currentFrame] };
  
  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  
  VkSemaphore waitSemaphores[] = {ctx.syncresources.imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  
  submitInfo.commandBufferCount =1;
  submitInfo.pCommandBuffers = submitCommandBuffers.data(); //commandBuffers[currentFrame];
  //submitInfo.pCommandBuffers = &commandBuffers[currentFrame];
  
  VkSemaphore signalSemaphores[] = {ctx.syncresources.renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;
  
  if (vkQueueSubmit(ctx.graphicsQueue, 1, &submitInfo, ctx.syncresources.inFlightFences[currentFrame]) != VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }
  
  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;
  
  VkSwapchainKHR swapChains[] = {ctx.swapchaincontext.swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  
  presentInfo.pImageIndices = &imageIndex;
  
  vkQueuePresentKHR(ctx.presentQueue, &presentInfo);
  
  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
    //framebufferResized = false;
    recreateSwapChain(ctx, window);
  } else if (result != VK_SUCCESS) {
    throw std::runtime_error("failed to present swap chain image!");
  }
  
  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

  return currentFrame;
}