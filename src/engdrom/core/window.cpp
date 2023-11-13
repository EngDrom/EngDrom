
/**********************************************************************************/
/* core/window.cpp                                                                */
/*                                                                                */
/* This file implements the methods and functions of the VulkanWindow class       */
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

#include <engdrom/core/core.h>
#include <engdrom/core/window.h>

/**
 * Create a vulkan window from a vulkan core
 */
VulkanWindow::VulkanWindow (VulkanCore* core) {
    this->mCore = core;
}

/**
 * Initialize a vulkan window
 */
void VulkanWindow::create(int width, int height, const char* name) {
    if (this->mIsCreated) return ;
    this->mIsCreated = true;

    this->mWindow = glfwCreateWindow(width, height, name, NULL, NULL);
}

/**
 * Cleanup the vulkan window
 */
void VulkanWindow::destroy () {
    if (!this->mIsCreated) return ;
    this->mIsCreated = false;

    this->mCore->destroyWindow(this);

    glfwDestroyWindow(this->mWindow);
    this->mWindow = nullptr;

    delete this;
}

/**
 * @return whether the window has been created 
 */
bool VulkanWindow::isCreated () {
    return this->mIsCreated;
}

/**
 * @return whether the window should close, returns true if the window is not created
*/
bool VulkanWindow::shouldClose () {
    return !this->mIsCreated
         || glfwWindowShouldClose(this->mWindow);
}

/**
 * Poll the GLFW events
 */
void VulkanWindow::pollEvents () {
    glfwPollEvents();
}
