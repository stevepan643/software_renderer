#ifndef SR_WINDOW_H
#define SR_WINDOW_H
#include <SDL3/SDL.h>

namespace SR {
    class Window {
        SDL_Window *window = nullptr;
        bool windowShouldClose = false;

    public:
        explicit Window(const char *title = "Window",
                        int width = 800, int height = 600,
                        SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE);

        bool shouldClose() const;
        void pollEvents();

        ~Window();
    };
} // SR

#endif //SR_WINDOW_H
