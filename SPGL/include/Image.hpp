#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <array> // std::array
#include <stdexcept> // std::out_of_range

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace SPGL // Definitions
{
  template<Size x, Size y>
  class Image
  {
  public: /* Information */
    Size height() const noexcept;
    Size width()  const noexcept;
    bool empty()  const noexcept;
    Size size()   const noexcept;
    Size bytes()  const noexcept;
    Color* data() noexcept;

  public: /* Constructors */
    // Default Constructor
    Image() noexcept {}

    // Copy Constructors
    Image(const Image &in) = default;
    Image& operator=(const Image &in) = default;

    Image(Image &&in) = default;
    Image& operator=(Image &&in) = default;

    // Custom Constructors
    Image(const void* pixels) noexcept;
    Image(const Color f) noexcept;

  public: /* Functions */
    Color& operator[](const Size i) noexcept;
    Color& getPixel(const Size inX, const Size inY);

  private: /* Raw Data */
    std::array<Color, x*y> arr;
  };
}

namespace SPGL // Implementation
{
  // Information
  template<Size x, Size y>
  Size Image<x, y>::height() const noexcept { return x; }

  template<Size x, Size y>
  Size Image<x, y>::width()  const noexcept { return y; }

  template<Size x, Size y>
  bool Image<x, y>::empty()  const noexcept { return height() && width(); }

  template<Size x, Size y>
  Size Image<x, y>::size()   const noexcept { return width()*height(); }

  template<Size x, Size y>
  Size Image<x, y>::bytes()  const noexcept { return size()*sizeof(Color); }

  template<Size x, Size y>
  Color* Image<x, y>::data() noexcept { return arr.data(); }

  // Custom Constructors
  template<Size x, Size y>
  Image<x, y>::Image(const void* pixels) noexcept
  {
    const Color* ptr = reinterpret_cast<const Color*>(pixels);
    for(Size i = 0; i < size(); ++i) arr[i] = ptr[i];
  }

  template<Size x, Size y>
  Image<x, y>::Image(const Color in) noexcept
  { for(Color& i : arr) i = in; }

  // Getters
  template<Size x, Size y>
  Color& Image<x, y>::operator[](const Size i) noexcept
  { return arr[i]; }

  template<Size x, Size y>
  Color& Image<x, y>::getPixel(const Size inX, const Size inY)
  {
    if(inX > x) throw std::out_of_range("X Too Large!");
    if(inY > y) throw std::out_of_range("Y Too Large!");
    return arr[inY*x + inX];
  }
}

#endif // SPGL_IMAGE_HPP
