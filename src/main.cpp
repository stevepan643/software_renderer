#include "Window.h"

int main() {
    SR::Window win("Hello World!");

    while (!win.shouldClose()) {
        win.pollEvents();
    }

    return 0;
}
