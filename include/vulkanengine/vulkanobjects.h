#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex.h"

struct WindowContext {
    GLFWwindow* window;
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

struct UniformBufferResources {
    std::vector<VkBuffer> uniformBuffers{};
    std::vector<VkDeviceMemory> uniformBuffersMemory{};
    std::vector<void*> uniformBuffersMapped{};
};

struct MeshObject {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct PhysicalDeviceSelection {
    VkPhysicalDevice device{};
    QueueFamilyIndices queueFamilies{};
};

struct SyncResources {
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct SwapChainContext {

    VkSwapchainKHR swapChain{};
    std::vector<VkImage> swapChainImages{};
    VkFormat swapChainImageFormat{};
    VkExtent2D swapChainExtent{};

};

struct GraphicsPipelineContext {
    VkPipeline graphicsPipeline{};
    VkPipelineLayout pipelineLayout{};
};

struct TextureResources {
    //uint32_t index;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;
};

struct DepthImageResources {
    VkImage depthImage{};
    VkDeviceMemory depthImageMemory{};
    VkImageView depthImageView{};
};

struct VulkanInstance {
    // Core Vulkan handles
    VkInstance instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};
    VkSurfaceKHR surface{};
};

struct VulkanDeviceAndQueueContext {
    

    VkPhysicalDevice physicalDevice{};
    QueueFamilyIndices queueFamilies{};
    VkDevice device{};
    VkQueue graphicsQueue{};
    VkQueue presentQueue{};

    VkCommandPool commandPool{};
};

// NOT USED YET
struct SwapchainContext {
    VkSwapchainKHR swapchain{};

    std::vector<VkImage> images;
    std::vector<VkImageView> imageViews;

    DepthImageResources depth;

    VkRenderPass renderPass{};
    VkRenderPass uiRenderPass{};

    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkCommandBuffer> uiCommandBuffers;
};

struct VulkanContext {

    // Surface + Swapchain
    SwapChainContext swapchaincontext{};

    // should we move this inside swapchain context ? 
    std::vector<VkImageView> swapchainImageViews{};

    // Command system
    

    VkRenderPass uiRenderPass{};
    VkRenderPass renderPass{};

    std::vector<VkCommandBuffer> uiCommandBuffers{};
    std::vector<VkCommandBuffer> commandBuffers{};

    VkDescriptorSetLayout descriptorSetLayout{};
    VkDescriptorPool descriptorPool{};

    GraphicsPipelineContext graphicsPipelineContext{};

    TextureResources textureres{};

    DepthImageResources depthImageResources{};    // Don't feel good about this field belonging to Vulkan Context. Maybe we need another struct
                                                    // by name of Rendering Context or something

    std::vector<VkFramebuffer> swapChainFramebuffers;
    std::vector<VkFramebuffer> uiFramebuffers;

    std::vector<VkDescriptorSet> descriptorSets;

    UniformBufferResources uboresources{};

    SyncResources syncresources{};
};