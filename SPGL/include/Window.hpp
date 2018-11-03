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
  template<Size x, Size y, Size s = 1, bool main_window = true>
  class Window
  {
  public: /* Functions */
    /* Initalization */
    Window(const char* name = "");
    ~Window();

    /* Running Stuff */
    void close();
    bool isRunning() const;

    /* Events */
    void updateWindow();

    /* Information */
    bool isMouseDown() const;
    Vector2D<Size> getMousePixel() const;

    /* Rendering */
    void renderImage(Image<x, y> &in);

  private: /* Variables */
    bool running = false;
    bool mouseDown = false;
    Vector2D<Size> mousePixel;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
  };
}

namespace spgl
{
  /* Initalization */
  template<Size x, Size y, Size s, bool main_window>
  Window<x,y,s,main_window>::Window(const char* name = "")
  {
    if(main_window)
    { SDL_Init(SDL_INIT_VIDEO); }

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, x*s, y*s, 0);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetScale(renderer, (float)s, (float)s);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
      SDL_TEXTUREACCESS_STATIC, x, y);

    running = true;
  }

  template<Size x, Size y, Size s, bool main_window>
  Window<x,y,s,main_window>::~Window()
  {
    if(running)
    { close(); }

    if(main_window)
    { SDL_Quit(); }
  }

  /* Running Stuff */
  template<Size x, Size y, Size s, bool main_window>
  void Window<x,y,s,main_window>::close()
  {
    running = false;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  template<Size x, Size y, Size s, bool main_window>
  bool Window<x,y,s,main_window>::isRunning() const
  { return running; }

  /* Events */
  template<Size x, Size y, Size s, bool main_window>
  void Window<x,y,s,main_window>::updateWindow()
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
  template<Size x, Size y, Size s, bool main_window>
  bool Window<x,y,s,main_window>::isMouseDown() const
  { return mouseDown; }

  template<Size x, Size y, Size s, bool main_window>
  Vector2D<Size> Window<x,y,s,main_window>::getMousePixel() const
  { return mousePixel; }

  /* Rendering */
  template<Size x, Size y, Size s, bool main_window>
  void Window<x,y,s,main_window>::renderImage(Image<x, y> &in)
  {
    if(!running) { return; }

    SDL_UpdateTexture(texture, NULL, in.getPixelArray(), width*4);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

#endif // SPGL_WINDOW_HPP
