
/**********************************************************************************/
/* core/core.cpp                                                                  */
/*                                                                                */
/* This file implements the methods and functions for the VulkanCore class        */
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
#include <iostream>
#include <engdrom/core/core.h>
#include <engdrom/core/window.h>

#include <engdrom/core/api/instance.h>

/**
 * Init the vulkan API and create the necessary backend data
 */
void VulkanCore::init (const char* applicationName, int major, int minor, int patch) {
    if (this->mIsLaunched) return ;
    this->mIsLaunched = true;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mInstance = VulkanInstance::createInstance(applicationName, major, minor, patch);
}

/**
 * Cleanup the vulkan API and destroy any object that is no longer needed
 */
void VulkanCore::cleanup () {
    if (!this->mIsLaunched) return ;
    this->mIsLaunched = false;

    while (this->mWindowsCreated.size() != 0)
        destroyWindow(this->mWindowsCreated[0]);

    glfwTerminate();

    delete mInstance;
}

/**
 * @return whether the vulkan API is started
 */
bool VulkanCore::isLaunched () {
    return this->mIsLaunched;
}

/**
 * Create a vulkan window
 * 
 * @param width the window width
 * @param height the window height
 * @param name the name of the window
 * @return a pointer to the vulkan window
 */
VulkanWindow* VulkanCore::createWindow (int width, int height, const char* name) {
    VulkanWindow* window = new VulkanWindow(this);
    window->create(width, height, name);

    this->mWindowsCreated.push_back(window);

    return window;
}

/**
 * Destroy a vulkan window, the pointer is no longer valid after this function call
 */
void VulkanCore::destroyWindow (VulkanWindow* window) {
    if (window->isCreated())
        window->destroy();

    for (int windowId = 0; windowId < this->mWindowsCreated.size(); windowId ++) {
        if (this->mWindowsCreated[windowId] != window) continue ;

        this->mWindowsCreated.erase(this->mWindowsCreated.begin() + windowId);
        break ;
    }
}

/**
 * Destroy a vulkan core object, will cleanup for the user if it hasn't been done
 */
VulkanCore::~VulkanCore () {
    cleanup();
}

VulkanInstance* VulkanCore::getInstance () {
    return mInstance;
}
