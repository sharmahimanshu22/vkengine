#include "cleanup.h"
#include <GLFW/glfw3.h>
#include "vulkanobjects.h"


void cleanupSwapChain(VulkanContext ctx, VulkanDeviceAndQueueContext dqcontext) {
    vkDestroyImageView(dqcontext.device, ctx.depthImageResources.depthImageView, nullptr);
    vkDestroyImage(dqcontext.device, ctx.depthImageResources.depthImage, nullptr);
    vkFreeMemory(dqcontext.device, ctx.depthImageResources.depthImageMemory, nullptr);

    for (size_t i = 0; i < ctx.swapChainFramebuffers.size(); i++) {
    vkDestroyFramebuffer(dqcontext.device, ctx.swapChainFramebuffers[i], nullptr);
    //vkDestroyFramebuffer(ctx.device, ctx.uiFramebuffers[i], nullptr);
    }

    for (size_t i = 0; i < ctx.swapchainImageViews.size(); i++) {
    vkDestroyImageView(dqcontext.device, ctx.swapchainImageViews[i], nullptr);
    }

    vkDestroySwapchainKHR(dqcontext.device, ctx.swapchaincontext.swapChain, nullptr);
}


void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void cleanup(VulkanContext ctx, VulkanDeviceAndQueueContext dqcontext, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers  ) 
{
    cleanupSwapChain(ctx, dqcontext);

    vkDestroySampler(dqcontext.device, ctx.textureres.textureSampler, nullptr);
    vkDestroyImageView(dqcontext.device, ctx.textureres.textureImageView, nullptr);
    vkDestroyImage(dqcontext.device, ctx.textureres.textureImage, nullptr);
    vkFreeMemory(dqcontext.device, ctx.textureres.textureImageMemory, nullptr);

    vkDestroyPipeline(dqcontext.device, ctx.graphicsPipelineContext.graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(dqcontext.device, ctx.graphicsPipelineContext.pipelineLayout, nullptr);
    vkDestroyRenderPass(dqcontext.device, ctx.renderPass, nullptr);
    //vkDestroyRenderPass(ctx.device, uiRenderPass, nullptr);
        
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(dqcontext.device, ctx.uboresources.uniformBuffers[i], nullptr);
        vkFreeMemory(dqcontext.device, ctx.uboresources.uniformBuffersMemory[i], nullptr);
    }

    //ImGui_ImplVulkan_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    //ImGui_ImplVulkanH_DestroyWindow(instance, device, &g_MainWindowData, NULL);

    vkDestroyDescriptorPool(dqcontext.device, ctx.descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(dqcontext.device, ctx.descriptorSetLayout, nullptr);

    vkDestroyBuffer(dqcontext.device, m.indexBuffer, nullptr);
    vkFreeMemory(dqcontext.device, m.indexBufferMemory, nullptr);

    vkDestroyBuffer(dqcontext.device, m.vertexBuffer, nullptr);
    vkFreeMemory(dqcontext.device, m.vertexBufferMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(dqcontext.device, ctx.syncresources.renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(dqcontext.device, ctx.syncresources.imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(dqcontext.device, ctx.syncresources.inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(dqcontext.device, ctx.commandPool, nullptr);

    vkDestroyDevice(dqcontext.device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(dqcontext.instance, dqcontext.debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(dqcontext.instance, dqcontext.surface, nullptr);
    vkDestroyInstance(dqcontext.instance, nullptr);


    glfwDestroyWindow(window);

    glfwTerminate();
  }