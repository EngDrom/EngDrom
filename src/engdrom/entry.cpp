
#include <iostream>
#include <engdrom/core/core.h>
#include <engdrom/core/window.h>

int main () {
    VulkanCore* core = new VulkanCore();
    core->init("EngDromEditor", 1, 0, 0);

    //VulkanWindow* window = core->createWindow(800, 600, "Vulkan");

    //while (!window->shouldClose()) {
    //    window->pollEvents();
    //}

    delete core;
}
