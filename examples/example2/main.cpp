//#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <io/glbloader.h>
#include <iostream>


int main() {
    auto img = load_GLB("./resources/DiffuseTransmissionPlant.glb");
    //auto img = loadPng("foo.png");

    if (!img) {
        std::cerr << "PNG load error: " << img.error() << "\n";
        return -1;
    }
    tinygltf::Model& model = *img;

    //std::cout << "Loaded " << img->width << "x" << img->height << "\n";
    //GLFWwindow* window = init_window();
    //VulkanContext ctx = init_vulkan(window);
    //MeshObject m = loadScene(ctx);
    //run(ctx, MAX_FRAMES_IN_FLIGHT, m, window, enableValidationLayers);
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