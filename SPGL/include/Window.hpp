#ifndef SPGL_WINDOW_HPP
#define SPGL_WINDOW_HPP 1

#include <SDL.h> // Graphics

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"
#include "Image.hpp"

namespace SPGL
{
  // Main window should be made first and destroyed last
  template<std::size_t width, std::size_t height, std::size_t scale = 1, bool main_window = true>
  class Window
  {
  public: /* Functions */
    /* Initalization */
    Window(const char* name = "")
    {
      if(main_window)
      { SDL_Init(SDL_INIT_VIDEO); }

      window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width*scale, height*scale, 0);

      renderer = SDL_CreateRenderer(window, -1, 0);
      SDL_RenderSetScale(renderer, (float)scale, (float)scale);

      texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
        SDL_TEXTUREACCESS_STATIC, width, height);

      running = true;
    }

    ~Window()
    {
      if(running)
      { close(); }

      if(main_window)
      { SDL_Quit(); }
    }

    void close()
    {
      running = false;
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
    }

    bool isRunning() const
    { return running; }

    /* Events */
    void updateWindow()
    {
      if(!running) { return; }

      SDL_PollEvent(&event);
      switch (event.type)
      {
      case SDL_QUIT:
        close();
        break;

      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
          mouseDown = false;
        break;

      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
          mouseDown = true;
        break;

      case SDL_MOUSEMOTION:
        mousePixel.x = event.motion.x/scale;
        mousePixel.y = event.motion.y/scale;
        break;
      }
    }

    /* Information */
    bool isMouseDown() const
    { return mouseDown; }

    Vector2D<std::size_t> getMousePixel() const
    { return mousePixel; }

    /* Rendering */
    void renderImage(Image<width, height> &in)
    {
      if(!running) { return; }

      SDL_UpdateTexture(texture, NULL, in.getPixelArray(), width*4);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }

  private: /* Variables */
    bool running = false;
    bool mouseDown = false;
    Vector2D<std::size_t> mousePixel;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
  };
}

#endif // SPGL_WINDOW_HPP
