#include "cleanup.h"
#include <GLFW/glfw3.h>
#include "vulkanobjects.h"


void cleanupSwapChain(VulkanContext ctx) {
    vkDestroyImageView(ctx.device, ctx.depthImageResources.depthImageView, nullptr);
    vkDestroyImage(ctx.device, ctx.depthImageResources.depthImage, nullptr);
    vkFreeMemory(ctx.device, ctx.depthImageResources.depthImageMemory, nullptr);

    for (size_t i = 0; i < ctx.swapChainFramebuffers.size(); i++) {
    vkDestroyFramebuffer(ctx.device, ctx.swapChainFramebuffers[i], nullptr);
    //vkDestroyFramebuffer(ctx.device, ctx.uiFramebuffers[i], nullptr);
    }

    for (size_t i = 0; i < ctx.swapchainImageViews.size(); i++) {
    vkDestroyImageView(ctx.device, ctx.swapchainImageViews[i], nullptr);
    }

    vkDestroySwapchainKHR(ctx.device, ctx.swapchaincontext.swapChain, nullptr);
}


void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void cleanup(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers  ) 
{
    cleanupSwapChain(ctx);

    vkDestroySampler(ctx.device, ctx.textureres.textureSampler, nullptr);
    vkDestroyImageView(ctx.device, ctx.textureres.textureImageView, nullptr);
    vkDestroyImage(ctx.device, ctx.textureres.textureImage, nullptr);
    vkFreeMemory(ctx.device, ctx.textureres.textureImageMemory, nullptr);

    vkDestroyPipeline(ctx.device, ctx.graphicsPipelineContext.graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(ctx.device, ctx.graphicsPipelineContext.pipelineLayout, nullptr);
    vkDestroyRenderPass(ctx.device, ctx.renderPass, nullptr);
    //vkDestroyRenderPass(ctx.device, uiRenderPass, nullptr);
        
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(ctx.device, ctx.uboresources.uniformBuffers[i], nullptr);
        vkFreeMemory(ctx.device, ctx.uboresources.uniformBuffersMemory[i], nullptr);
    }

    //ImGui_ImplVulkan_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    //ImGui_ImplVulkanH_DestroyWindow(instance, device, &g_MainWindowData, NULL);

    vkDestroyDescriptorPool(ctx.device, ctx.descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(ctx.device, ctx.descriptorSetLayout, nullptr);

    vkDestroyBuffer(ctx.device, m.indexBuffer, nullptr);
    vkFreeMemory(ctx.device, m.indexBufferMemory, nullptr);

    vkDestroyBuffer(ctx.device, m.vertexBuffer, nullptr);
    vkFreeMemory(ctx.device, m.vertexBufferMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(ctx.device, ctx.syncresources.renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(ctx.device, ctx.syncresources.imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(ctx.device, ctx.syncresources.inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(ctx.device, ctx.commandPool, nullptr);

    vkDestroyDevice(ctx.device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(ctx.instance, ctx.debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(ctx.instance, ctx.surface, nullptr);
    vkDestroyInstance(ctx.instance, nullptr);


    glfwDestroyWindow(window);

    glfwTerminate();
  }