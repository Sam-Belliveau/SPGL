#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <array> // std::array

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace SPGL
{
  template<std::size_t iwidth, std::size_t iheight>
  class Image
  {
  public: /* Class Info Function */
    constexpr std::size_t size()
    { return iheight*iwidth; }

    constexpr std::size_t bytes()
    { return size()*3; }

    constexpr std::size_t height()
    { return iheight; }

    constexpr std::size_t width()
    { return iwidth; }

  public: /* Constructors */
    // Empty
    Image() {}

    // Other Image
    Image(const Image<iheight, iwidth> &in)
    { pixels = in.pixels; }

    // Color Array
    Image(const std::array<Color, iheight*iwidth> &in) : pixels{in} {}

    // RGB Byte Array
    Image(const std::array<UInt8_t, iheight*iwidth*3> &in)
    {
      for(std::size_t i = 0; i < iheight*iwidth*3; i += 3)
      { pixels[i >> 2] = Color(in[i+0], in[i+1], in[i+2]); }
    }

    // Fill
    Image(const Color &in)
    {
      for(Color& a : pixels)
      { a = in; }
    }

  public: /* Editing Functions */
    constexpr Color& at(const std::size_t &x, const std::size_t &y)
    { return pixels[y*iwidth + x]; }

    constexpr Color& operator[](const Vector2D<std::size_t> &i)
    { return at(i.x, i.y); }

    constexpr Color& at(const std::size_t &i)
    { return pixels[i]; }

    constexpr Color& operator[](const std::size_t &i)
    { return at(i); }

    constexpr UInt32_t* getPixelArray()
    { return reinterpret_cast<UInt32_t*>(&pixels); }

  private: /* Raw Data */
    std::array<Color, iheight*iwidth> pixels;
  };
}

#endif // SPGL_IMAGE_HPP
