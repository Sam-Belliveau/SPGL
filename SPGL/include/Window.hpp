#ifndef SPGL_WINDOW_HPP
#define SPGL_WINDOW_HPP 1

#include <SDL.h> // Graphics

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"
#include "Image.hpp"

namespace spgl
{
  // Main window should be made first and destroyed last
  template<bool main_window = true>
  class Window
  {
  public: /* Functions */
    /* Initalization */
    Window();
    ~Window();
    Window(const Size &w, const Size &h, const char* name = "");

    void close();
    bool isRunning() const;

    /* Events */
    void updateWindow();

    /* Rendering */
    void renderImage(Image &in);

  private: /* Functions */
    void resizeTexture(const int &x, const int &y);

  private: /* Variables */
    bool running = false;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
  };
}

namespace spgl // Definitions
{
  template<bool mw> Window<mw>::Window() {}

  template<bool mw> Window<mw>::~Window()
  {
    if(running) close();
    if(mw) SDL_Quit();
  }

  template<bool mw> Window<mw>::Window( const Size &w,
                                        const Size &h,
                                        const char* name)
  {
    if(mw)
    { SDL_Init(SDL_INIT_VIDEO); }

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, w, h, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, w, h);

    running = true;
  }

  template<bool mw>
  void Window<mw>::close()
  {
    running = false;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  template<bool mw>
  bool Window<mw>::isRunning() const
  { return running; }

  template<bool mw>
  void Window<mw>::updateWindow()
  {
    if(!running) { return; }

    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
      close();
      break;
    }
  }

  template<bool mw>
  void Window<mw>::renderImage(Image &in)
  {
    if(!running || in.empty()) { return; }

    SDL_Texture* texture = SDL_CreateTexture(renderer,
      SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
      in.width(), in.height());

    SDL_UpdateTexture(texture, NULL, in.data(),
                      in.width()*sizeof(Color));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
  }
}

#endif // SPGL_WINDOW_HPP
