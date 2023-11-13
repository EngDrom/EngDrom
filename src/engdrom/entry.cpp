
#include <iostream>
#include <engdrom/core/core.h>
#include <engdrom/core/window.h>

int main () {
    VulkanCore* core = new VulkanCore();
    core->init();

    VulkanWindow* window = core->createWindow(800, 600, "Vulkan");
    VulkanWindow* window2 = core->createWindow(800, 600, "Vulkan 2");

    while (!window->shouldClose()) {
        window->pollEvents();
    }

    core->cleanup();
}
