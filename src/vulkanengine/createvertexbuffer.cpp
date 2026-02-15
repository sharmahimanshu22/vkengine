#include "createvertexbuffer.h"

#include "vulkanobjects.h"
#include "bufferutils.h"




BufferResources createIndexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, 
                        const std::vector<uint32_t> indices) {
  if (indices.size() == 0) {
    return BufferResources();
  }
  VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
  

  BufferResources stagingbufferresources = createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  
  void* data;
  vkMapMemory(device, stagingbufferresources.bufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), (size_t) bufferSize);
  vkUnmapMemory(device, stagingbufferresources.bufferMemory);
  
  BufferResources indexBufferResources = createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  
  copyBuffer(device, stagingbufferresources.buffer, indexBufferResources.buffer, bufferSize, commandPool, graphicsQueue);
  
  vkDestroyBuffer(device, stagingbufferresources.buffer, nullptr);
  vkFreeMemory(device, stagingbufferresources.bufferMemory, nullptr);

  return indexBufferResources;
}



BufferResources createVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue, 
                        const std::vector<Vertex> vertices) {
  if (vertices.size() == 0) {
    return BufferResources();
  }
  
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
  
  
  BufferResources stagingbufferresources = createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  
  void* data;
  vkMapMemory(device, stagingbufferresources.bufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), (size_t) bufferSize);
  vkUnmapMemory(device, stagingbufferresources.bufferMemory);
  
  BufferResources vertexBufferResources = createBuffer(device, physicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  
  copyBuffer(device, stagingbufferresources.buffer, vertexBufferResources.buffer, bufferSize, commandPool, graphicsQueue);
  
  vkDestroyBuffer(device, stagingbufferresources.buffer, nullptr);
  vkFreeMemory(device, stagingbufferresources.bufferMemory, nullptr);

  return vertexBufferResources;
}