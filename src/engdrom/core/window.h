
/**********************************************************************************/
/* core/window.h                                                                  */
/*                                                                                */
/* This file contains the details for the VulkanWindow object and the different   */
/* methods associated to it.                                                      */
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

#pragma once

#include <engdrom/core/struct.h>

class VulkanWindow {
private:
    GLFWwindow*        mWindow              = nullptr;
    VulkanCore*        mCore                = nullptr;
    VulkanDevice*      mDevice              = nullptr;
    VulkanQueueFamily* mQueueFamily = nullptr;

    VkSurfaceKHR mSurface = nullptr;

    bool mIsCreated = false;
public:
    VulkanWindow (VulkanCore* core);

    void create (int width, int height, const char* name);
    void destroy ();

    bool isCreated ();
    bool shouldClose ();

    void pollEvents ();
};
