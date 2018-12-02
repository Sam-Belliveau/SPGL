#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <array>

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace SPGL // Definitions
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
    // Default Constructor
    Image() {}

    // Copy Constructors
    Image(const Image &in) = default;
    Image& operator=(const Image &in) = default;

    Image(Image &&in) = default;
    Image& operator=(Image &&in) = default;

    // Custom Constructors
    Image(const void* pixels);
    Image(const Color f);

  public: /* Functions */
    Color& operator[](const Size &i);
    Color& getPixel(const Size &inX, const Size &inY);

  private: /* Raw Data */
    std::array<Color, x*y> arr;
  };
}

namespace SPGL // Implementation
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

  // Custom Constructors
  template<Size x, Size y>
  Image<x, y>::Image(const void* pixels)
  {
    const Color* ptr = reinterpret_cast<const Color*>(pixels);
    for(Size i = 0; i < size(); ++i) arr[i] = ptr[i];
  }

  template<Size x, Size y>
  Image<x, y>::Image(const Color in)
  { for(Color& i : arr) i = in; }

  // Getters
  template<Size x, Size y>
  Color& Image<x, y>::operator[](const Size &i)
  { return arr[i]; }

  template<Size x, Size y>
  Color& Image<x, y>::getPixel(const Size &inX, const Size &inY)
  { return arr[inY*x + inX]; }
}

#endif // SPGL_IMAGE_HPP
