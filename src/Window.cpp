#include "Window.h"

namespace SR {
    Window::Window(const char *title, const int width, const int height, const SDL_WindowFlags flags) {
        window = SDL_CreateWindow(title, width, height, flags);
    }

    Window::~Window() {
        if (window) SDL_DestroyWindow(window);
    }

    bool Window::shouldClose() const {
        return windowShouldClose;
    }

    void Window::pollEvents() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)  windowShouldClose = true;
        }
    }
} // SR