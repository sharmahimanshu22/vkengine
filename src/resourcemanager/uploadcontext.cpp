#include "resourcemanager/buffermanager.hpp"


class UploadContext {
public:
    vk::Device device;
    vk::Queue transferQueue;
    vk::CommandPool commandPool;

    // High-level: write CPU data into device-local buffer
    void uploadToDevice(BufferHandle dst,
                        const void* data,
                        vk::DeviceSize size,
                        BufferManager& bufferManager)
    {
        // 1. create temporary staging buffer
        BufferHandle staging = bufferManager.create(BufferDesc{
            .size = size,
            .usage = vk::BufferUsageFlagBits::eTransferSrc,
            .memoryProperties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        });

        // 2. map + copy CPU data into staging
        void* mapped = bufferManager.map(staging);
        memcpy(mapped, data, size);
        bufferManager.unmap(staging);

        // 3. copy to device-local buffer
        copyBuffer(staging, dst, size, bufferManager);

        // 4. schedule destruction of staging
        bufferManager.destroyLater(staging);
    }

private:
    void copyBuffer(BufferHandle src,
                    BufferHandle dst,
                    vk::DeviceSize size,
                    BufferManager& buffers)
    {
        vk::CommandBuffer cmd = beginSingleTimeCommands();

        vk::BufferCopy region{};
        region.size = size;
        cmd.copyBuffer(buffers.getVkBuffer(src),
                       buffers.getVkBuffer(dst),
                       1, &region);

        endSingleTimeCommands(cmd);
    }

    vk::CommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(vk::CommandBuffer cmd);
};