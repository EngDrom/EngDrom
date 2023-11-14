
/**********************************************************************************/
/* core/api/device.cpp                                                            */
/*                                                                                */
/* This file implements the details for the VulkanDevice class                    */
/**********************************************************************************/
/*                          This file is part of EngDrom                          */
/*                           github.com/EngDrom/EngDrom                           */
/**********************************************************************************/
/* Copyright (c) 2023 EngDrom                                                     */
/*                                                                                */
/* Permission is hereby granted, free of charge, to any person obtaining a copy   */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights   */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/* copies of the Software, and to permit persons to whom the Software is          */
/* furnished to do so, subject to the following conditions:                       */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.                                */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/**********************************************************************************/

#include <vector>
#include <stdexcept>
#include <engdrom/core/api/device.h>
#include <engdrom/core/api/queue/family.h>
#include <engdrom/core/api/instance.h>

VulkanDevice::VulkanDevice (VkPhysicalDevice physicalDevice, VulkanQueueFamily* family) {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = family->getGraphicsFamily();
    queueCreateInfo.queueCount       = 1;

    float priority = 1.0f;
    queueCreateInfo.pQueuePriorities = &priority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;
    createInfo.enabledLayerCount = 0;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &mDevice) != VK_SUCCESS)
        throw std::runtime_error("failed to create logical device!");
    
    vkGetDeviceQueue(mDevice, family->getGraphicsFamily(), 0, &mDeviceQueue);
}

bool isDeviceSuitable (VkPhysicalDevice device) {
    VulkanQueueFamily* family = VulkanQueueFamily::getViewFamily(device);
    bool hasValidQueueFamily  = family->exists();

    delete family;
    return hasValidQueueFamily;
}

VkPhysicalDevice VulkanDevice::pickPhysicalDevice (VulkanInstance* instance) {
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance->getInstance(), &deviceCount, nullptr);

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance->getInstance(), &deviceCount, devices.data());

    if (deviceCount == 0)
        throw std::runtime_error("device.cpp: failed to find GPUs with Vulkan support.");
    
    for (const auto &device : devices) {
        if (!isDeviceSuitable(device)) continue ;

        physicalDevice = device;
        break ;
    }

    if (physicalDevice == VK_NULL_HANDLE)
        throw std::runtime_error("device.cpp: failed to find a GPU supporting the correct properties.");
    return physicalDevice;
}

VulkanDevice::~VulkanDevice () {
    vkDestroyDevice(mDevice, nullptr);
}
