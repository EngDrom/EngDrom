
/**********************************************************************************/
/* core/instance.h                                                                */
/*                                                                                */
/* This file contains the details for the VulkanInstance class                    */
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

#include <stdexcept>

#include <engdrom/core/api/instance.h>
#include <engdrom/core/debug.h>

VulkanInstance::VulkanInstance (VkInstance instance) {
    mInstance = instance;
}

VkInstance VulkanInstance::getInstance () {
    return mInstance;
}

VulkanInstance* VulkanInstance::createInstance (const char* title, int major, int minor, int patch) {
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName   = title;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(major, minor, patch);

    applicationInfo.pEngineName        = "EngDrom";
    applicationInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.apiVersion         = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    applyValidationLayers(createInfo);

    VkInstance instance;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        throw std::runtime_error("core.cpp: failed to create vulkan instance.");

    return new VulkanInstance(instance);
}

VulkanInstance::~VulkanInstance () {
    vkDestroyInstance(mInstance, nullptr);

    if (mInstance != nullptr)
        throw std::runtime_error("core.cpp: failed to create vulkan instance.");
}
