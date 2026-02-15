#include "createuniformbuffers.h"
#include <vector>
#include "vulkanobjects.h"
#include "bufferutils.h"


// This method currently creates the view matrix and also does the vulkan api calls. both should be separated.
UniformBufferResources createUniformBuffers(VkDevice device, VkPhysicalDevice physicalDevice ,int MAX_FRAMES_IN_FLIGHT)
{
    UniformBufferObject ubo;

    UniformBufferResources uboresources;

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uboresources.uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    uboresources.uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    uboresources.uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
    glm::vec3 cameraDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    ubo.model = glm::mat4(1.0f);
    // ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.view = glm::lookAt(glm::vec3(-100.0f, -100.0f, 15.0f), glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.view = glm::lookAt(glm::vec3(-10.0f, -10.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(cameraPosition, cameraDirection, cameraUp);
    ubo.proj = glm::perspective(glm::radians(45.0f), 1.0f , 1.0f, 100.0f);
    //ubo.proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -10.0f, 10.0f);
    ubo.proj[1][1] *= -1;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        BufferResources br = createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        uboresources.uniformBuffers[i] = br.buffer;
        uboresources.uniformBuffersMemory[i] = br.bufferMemory;

        vkMapMemory(device, uboresources.uniformBuffersMemory[i], 0, bufferSize, 0, &uboresources.uniformBuffersMapped[i]);
        memcpy(uboresources.uniformBuffersMapped[i], &ubo, sizeof(ubo));
    }

    return uboresources;
}