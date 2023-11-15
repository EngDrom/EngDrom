
/**********************************************************************************/
/* core/api/queue/family.h                                                        */
/*                                                                                */
/* This file contains the details for the VulkanQueueFamily class                 */
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

#include <engdrom/core/struct.h>

class VulkanQueueFamily {
private:
    uint32_t mGraphicsFamily;
    uint32_t mPresentFamily;
    bool mExists;
public:
    VulkanQueueFamily (uint32_t graphicsFamily, uint32_t presentFamily, bool exists);
    uint32_t getGraphicsFamily ();
    uint32_t getPresentFamily ();

    static VulkanQueueFamily* getViewFamily (VkSurfaceKHR surface, VkPhysicalDevice device);

    bool exists();
};
