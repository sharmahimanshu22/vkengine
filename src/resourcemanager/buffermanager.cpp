#pragma once

#include <vulkan/vulkan.hpp>
#include "vk_mem_alloc.h"
#include "resourcemanager/buffermanager.hpp"




BufferHandle BufferManager::create(BufferDesc const& desc) {
    uint32_t index;

    if (!freeIndices.empty()) {
        index = freeIndices.back();
        freeIndices.pop_back();
    } else {
        index = static_cast<uint32_t>(slots.size());
        slots.push_back({});
    }

    BufferSlot& slot = slots[index];

    // --- create buffer using VMA ---
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = desc.size;
    bufferInfo.usage = static_cast<VkBufferUsageFlags>(desc.usage);

    VmaAllocationCreateInfo allocInfo{};
    allocInfo.usage = VMA_MEMORY_USAGE_AUTO;
    allocInfo.requiredFlags = desc.memoryProperties;

    VkBuffer rawBuffer;

    vmaCreateBuffer(
        allocator,
        &bufferInfo,
        &allocInfo,
        &rawBuffer,
        &slot.buffer.allocation,
        nullptr
    );

    slot.buffer.buffer = rawBuffer;
    slot.buffer.size = desc.size;

    slot.alive = true;

    return BufferHandle{ index, slot.generation };
}

GPUBuffer& BufferManager::get(BufferHandle handle) {
    BufferSlot& slot = slots[handle.index];

    if (!slot.alive || slot.generation != handle.generation) {
        throw std::runtime_error("Invalid or stale BufferHandle");
    }

    return slot.buffer;
}

void BufferManager::destroyLater(BufferHandle handle) {
    deletionQueue.push_back(handle);
}


// returns memory to VMA, not necessarily releases it back to GPU
void BufferManager::flush() {
    for (auto& handle : deletionQueue) {
        BufferSlot& slot = slots[handle.index];

        // skip invalid/stale handles safely
        if (!slot.alive || slot.generation != handle.generation)
            continue;

        // destroy via VMA
        vmaDestroyBuffer(
            allocator,
            static_cast<VkBuffer>(slot.buffer.buffer),
            slot.buffer.allocation
        );

        // mark dead
        slot.alive = false;

        // increment generation (KEY STEP)
        slot.generation++;

        // recycle slot
        freeIndices.push_back(handle.index);
    }

    deletionQueue.clear();
}


void* BufferManager::map(BufferHandle h) {
    auto& buf = get(h);

    if (!buf.mapped) {
        vmaMapMemory(allocator, buf.allocation, &buf.mapped);
    }
    return buf.mapped;
}


void BufferManager::unmap(BufferHandle h) {
    auto& buf = get(h);

    if (buf.mapped) {
        vmaUnmapMemory(allocator, buf.allocation);
        buf.mapped = nullptr;
    }
}


