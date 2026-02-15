#include "vulkanobjects.h"
#include "vkinstance.h"
#include "vksurface.h"
#include "physicaldevice.h"
#include "logicaldevice.h"
#include "swapchain.h"
#include "swapchainimageviews.h"
#include "commandpool.h"
#include "uirenderpass.h"
#include "createcommandbuffer.h"
#include "renderpass.h"
#include "descriptorsets.h"
#include "graphicspipeline.h"
#include "createdepthresources.h"
#include "createframebuffer.h"
#include "createtextureimage.h"
#include "createtexturesampler.h"
#include "createdescriptorsets.h"
#include "createuniformbuffers.h"
#include "createsyncobjects.h"
#include "createvertexbuffer.h"
#include "cleanup.h"
#include "initwindow.h"
#include "io/objloader.h"
#include "drawframe.h"

#include <GLFW/glfw3.h>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};
const int MAX_FRAMES_IN_FLIGHT = 2;


// TODO: THIS SHOULD ALSO CHANGE TO FUNCTIONAL STYLE
VulkanContext init_vulkan(GLFWwindow* window) {

    VulkanContext ctx;

    ctx.instance = create_instance(enableValidationLayers, validationLayers);

    if (enableValidationLayers) {
        ctx.debugMessenger = setup_debug_messenger(ctx.instance, enableValidationLayers);
    }

    ctx.surface = create_surface(ctx.instance, window);

    auto selection = pick_physical_device(ctx.instance, ctx.surface);
    ctx.physicalDevice = selection.device;
    ctx.queueFamilies = selection.queueFamilies;

    //printPhysicalDeviceProperties();
    auto deviceSelection = create_logical_device(ctx.physicalDevice, ctx.queueFamilies, enableValidationLayers, validationLayers);
    ctx.device = deviceSelection.device;
    ctx.graphicsQueue = deviceSelection.graphicsQueue;
    ctx.presentQueue = deviceSelection.presentQueue;

    ctx.swapchaincontext = createSwapChain(ctx.physicalDevice, ctx.surface, window, ctx.device, ctx.queueFamilies);

    ctx.swapchainImageViews = createSwapChainImageViews(ctx.device, ctx.swapchaincontext.swapChainImages, ctx.swapchaincontext.swapChainImageFormat);

    ctx.commandPool = createCommandPool(ctx.device, ctx.queueFamilies);
  
      // UI
    ctx.uiRenderPass = createUIRenderPass(ctx.device, ctx.swapchaincontext.swapChainImageFormat);
    ctx.uiCommandBuffers = createCommandBuffer(ctx.device, ctx.commandPool, MAX_FRAMES_IN_FLIGHT);
    
    
    ctx.commandBuffers = createCommandBuffer(ctx.device, ctx.commandPool, MAX_FRAMES_IN_FLIGHT);

    // for each model loaded as it might have model specific parameters to be used in graphiics pipeline
    ctx.renderPass = createRenderPass(ctx.device, ctx.physicalDevice, ctx.swapchaincontext.swapChainImageFormat);

    ctx.descriptorSetLayout = createDescriptorSetLayout(ctx.device); // TODO: this is very very hard coded. i don't like it.
    ctx.descriptorPool  = createDescriptorPool(ctx.device, MAX_FRAMES_IN_FLIGHT);

    ctx.graphicsPipelineContext = createGraphicsPipeline(ctx.device, ctx.descriptorSetLayout, ctx.renderPass);

    ctx.depthImageResources = createDepthResources(ctx.device, ctx.physicalDevice, ctx.swapchaincontext.swapChainExtent);

    ctx.swapChainFramebuffers = createFramebuffers(ctx.device, ctx.swapchainImageViews, ctx.depthImageResources.depthImageView,
                                                    ctx.renderPass, ctx.swapchaincontext.swapChainExtent);

    //ctx.uiFramebuffers = createUIFramebuffers(ctx.device, ctx.swapchainImageViews, ctx.uiRenderPass, 
     //                                               ctx.swapchaincontext.swapChainExtent);

    ImageResources imgresources = createTextureImage(ctx.device,ctx.physicalDevice, ctx.commandPool, ctx.graphicsQueue);
    ctx.textureres.textureImage = imgresources.image;
    ctx.textureres.textureImageMemory = imgresources.imageMemory;
    ctx.textureres.textureImageView = createTextureImageView(ctx.device, ctx.textureres.textureImage);
    ctx.textureres.textureSampler = createTextureSampler(ctx.device, ctx.physicalDevice);
        std::cout << "After vkCreateGraphicsPipelines\n\n\n";

    ctx.uboresources = createUniformBuffers(ctx.device, ctx.physicalDevice, MAX_FRAMES_IN_FLIGHT);

    ctx.descriptorSets =  createDescriptorSets( ctx.device, MAX_FRAMES_IN_FLIGHT,  
                                        ctx.descriptorSetLayout, ctx.descriptorPool, ctx.uboresources.uniformBuffers, ctx.textureres);

    std::cout << "After vkCreateGraphicsPipelines\n";

    
    ctx.syncresources = createSyncObjects(ctx.device, MAX_FRAMES_IN_FLIGHT);


    return ctx;

}

MeshObject loadScene(VulkanContext ctx) {
    DataForGPU dfg = loadModel("viking_room.obj");
    MeshObject m;

    /*
    std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f},{0.0f, 0.0f},},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f},{1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f},{1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f},{0.0f, 1.0f}},    
    };
    std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0,
    };
    */

    m.vertices = dfg.vertices;
    m.indices = dfg.indices;

    BufferResources br = createVertexBuffer(ctx.device, ctx.physicalDevice, ctx.commandPool, ctx.graphicsQueue, m.vertices);
    m.vertexBuffer = br.buffer;
    m.vertexBufferMemory = br.bufferMemory;
    br = createIndexBuffer(ctx.device, ctx.physicalDevice, ctx.commandPool, ctx.graphicsQueue, m.indices);
    m.indexBuffer = br.buffer;
    m.indexBufferMemory = br.bufferMemory;
    return m;
}

 
void mainLoop(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers) {
    uint32_t currentFrame = 0;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        currentFrame = drawFrame(ctx, MAX_FRAMES_IN_FLIGHT, m, window,enableValidationLayers, currentFrame );
    }
    vkDeviceWaitIdle(ctx.device);
}




void run(VulkanContext ctx, int MAX_FRAMES_IN_FLIGHT, MeshObject m, GLFWwindow* window,
             bool enableValidationLayers ) {
    mainLoop(ctx, MAX_FRAMES_IN_FLIGHT, m , window, enableValidationLayers);
    cleanup(ctx, MAX_FRAMES_IN_FLIGHT, m, window, enableValidationLayers);
}

int main() {
    GLFWwindow* window = init_window();
    VulkanContext ctx = init_vulkan(window);
    MeshObject m = loadScene(ctx);
    run(ctx, MAX_FRAMES_IN_FLIGHT, m, window, enableValidationLayers);
    return 0;
}

/*
void HelloTriangleApplication::init_imgui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();
  
  
  //this initializes imgui for SDL
  ImGui_ImplGlfw_InitForVulkan(window, true);
  
  //this initializes imgui for Vulkan
  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = instance;
  init_info.PhysicalDevice = physicalDevice;
  init_info.Device = device;
  init_info.QueueFamily = _queueFamilyIndices.graphicsFamily.value();
  init_info.Queue = graphicsQueue;
  init_info.DescriptorPool = descriptorPool;
  init_info.PipelineCache = VK_NULL_HANDLE;
  init_info.Allocator = NULL;
  init_info.CheckVkResultFn = check_vk_result;
  init_info.RenderPass = uiRenderPass;
  init_info.Subpass = 0;
  init_info.MinImageCount = 2;
  init_info.ImageCount = swapChainImages.size();
  //init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  
  ImGui_ImplVulkan_Init(&init_info);
  
}




GLFWwindow* initWindow() {
    const uint32_t WIDTH = 1028;
    const uint32_t HEIGHT = 660;
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    return window;
    
    //glfwSetWindowUserPointer(window, this);
    //glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    
    //set_cursor_position_callback();
    //set_mouse_button_callback();
    //set_cursor_enter_callback();
    //set_scroll_callback();
}



int main() {
    void initialize() {
    initWindow();
    initVulkan();
    init_imgui();
}

*/