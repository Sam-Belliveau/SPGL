#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <array>

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace spgl // Initalization
{
  template<Size x, Size y>
  class Image
  {
  public: /* Information */
    Size height() const;
    Size width()  const;
    bool empty()  const;
    Size size()   const;
    Size bytes()  const;
    Color* data();

  public: /* Constructors */
    Image();

    Image(const Image<x, y> &in);
    Image(const Color &f = Color(0x00));

  public: /* Functions */
    Color& operator[](const Size &i);
    Color& getPixel(const Size &inX, const Size &inY);

  private: /* Raw Data */
    std::array<Color, x*y> arr;
  };
}

namespace spgl // Definitions
{
  // Information
  template<Size x, Size y>
  Size Image<x, y>::height() const { return x; }

  template<Size x, Size y>
  Size Image<x, y>::width()  const { return y; }

  template<Size x, Size y>
  bool Image<x, y>::empty()  const { return height() && width(); }

  template<Size x, Size y>
  Size Image<x, y>::size()   const { return width()*height(); }

  template<Size x, Size y>
  Size Image<x, y>::bytes()  const { return size()*sizeof(Color); }

  template<Size x, Size y>
  Color* Image<x, y>::data() { return arr.data(); }

  // Constructors
  template<Size x, Size y>
  Image<x, y>::Image() { }

  template<Size x, Size y>
  Image<x, y>::Image(const Image<x, y> &in) : arr{in.arr} {}

  template<Size x, Size y>
  Image<x, y>::Image(const Color &in) : arr{in} {}

  // Getters
  template<Size x, Size y>
  Color& Image<x, y>::operator[](const Size &i)
  { return arr[i]; }

  template<Size x, Size y>
  Color& Image<x, y>::getPixel(const Size &inX, const Size &inY)
  { return arr[inY*x + inX]; }
}

#endif // SPGL_IMAGE_HPP
