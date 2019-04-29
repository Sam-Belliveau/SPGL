#ifndef SPGL_WINDOW_HPP
#define SPGL_WINDOW_HPP 1

#include <SDL2/SDL.h> // Graphics

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"
#include "Image.hpp"

namespace SPGL // Definitions
{
  // Main window should be made first and destroyed last
  template<Size x, Size y, Size xs = 1, Size ys = xs, bool main_window = true>
  class Window
  {
  private: // non-copyable
     Window(const Window&) = delete;
     Window& operator=(const Window&) = delete;
     Window(Window&&) = delete;
     Window& operator=(Window&&) = delete;

  public: /* Functions */
    /* Initalization */
    Window(const char* name = "SPGL Window");
    ~Window();

    /* Running Stuff */
    void close();
    bool isRunning() const;

    /* Events */
    void update();

    /* Information */
    bool isMouseDown() const;
    Vector2s getMousePixel() const;

    /* Rendering */
    void renderImage(Image<x, y> &in);

  private: /* Variables */
    bool running = false;
    bool mouseDown = false;
    Vector2s mousePixel;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
  };
}

namespace SPGL // Implementations
{
  /* Initalization */
  template<Size x, Size y, Size xs, Size ys, bool main_window>
  Window<x,y,xs,ys,main_window>::Window(const char* name)
  {
    if(main_window)
    { SDL_Init(SDL_INIT_VIDEO); }

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, x*xs, y*ys, 0);

    SDL_SetWindowResizable(window, SDL_TRUE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetScale(renderer, (float)xs, (float)ys);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STATIC, x, y);

    running = true;
  }

  template<Size x, Size y, Size xs, Size ys, bool main_window>
  Window<x,y,xs,ys,main_window>::~Window()
  { close(); }

  /* Running Stuff */
  template<Size x, Size y, Size xs, Size ys, bool main_window>
  void Window<x,y,xs,ys,main_window>::close()
  {
    if(running)
    {
      running = false;
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);

      if(main_window)
      { SDL_Quit(); }
    }
  }

  template<Size x, Size y, Size xs, Size ys, bool main_window>
  bool Window<x,y,xs,ys,main_window>::isRunning() const
  { return running; }

  /* Events */
  template<Size x, Size y, Size xs, Size ys, bool main_window>
  void Window<x,y,xs,ys,main_window>::update()
  {
    if(!running) { return; }

    while(SDL_PollEvent(&event))
    {
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
        int xsize, ysize;
        SDL_GetWindowSize(window, &xsize, &ysize);
        mousePixel.x = (x*event.motion.x)/(xs*xsize);
        mousePixel.y = (y*event.motion.y)/(ys*ysize);
        break;
      }
    }
  }

  /* Information */
  template<Size x, Size y, Size xs, Size ys, bool main_window>
  bool Window<x,y,xs,ys,main_window>::isMouseDown() const
  { return mouseDown; }

  template<Size x, Size y, Size xs, Size ys, bool main_window>
  Vector2s Window<x,y,xs,ys,main_window>::getMousePixel() const
  { return mousePixel; }

  /* Rendering */
  template<Size x, Size y, Size xs, Size ys, bool main_window>
  void Window<x,y,xs,ys,main_window>::renderImage(Image<x, y> &in)
  {
    if(!running) { return; }

    //SDL_RenderClear(renderer);
    SDL_UpdateTexture(texture, NULL, in.data(), x*4);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

#endif // SPGL_WINDOW_HPP
