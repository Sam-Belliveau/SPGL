#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <array> // std::array
#include <algorithm> // std::copy
#include <stdexcept> // std::out_of_range
#include <iterator> // std::reverse_iterator

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace SPGL // Definitions
{
  template<Size x, Size y, class ColorType = Color>
  class Image
  {
  public: /* Container Information */
    using value_type = ColorType;

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using reference = value_type&;
    using const_reference = const value_type&;

    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = pointer;
    using const_iterator = const_pointer;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  public: /* Information */
    Size height() const noexcept;
    Size width()  const noexcept;
    bool empty()  const noexcept;
    Size size()   const noexcept;
    Size bytes()  const noexcept;
    ColorType* data() noexcept;

  public: /* Constructors */
    // Default Constructor
    Image() noexcept {}

    // Copy Constructors
    Image(const Image &in) noexcept;
    Image& operator=(const Image &in) noexcept;

    // Custom Constructors
    Image(const void* pixels);
    Image& operator=(const void* pixels);
    Image(const ColorType f) noexcept;

  public: /* Iterators */
    iterator begin() noexcept { return std::begin(arr); }
    const_iterator begin() const noexcept { return std::cbegin(arr); }
    const_iterator cbegin() const noexcept { return std::cbegin(arr); }

    iterator end() noexcept { return std::end(arr); }
    const_iterator end() const noexcept { return std::cend(arr); }
    const_iterator cend() const noexcept { return std::cend(arr); }

    reverse_iterator rbegin() noexcept { return std::end(arr); }
    const_reverse_iterator rbegin() const noexcept { return std::cend(arr); }
    const_reverse_iterator crbegin() const noexcept { return std::cend(arr); }

    reverse_iterator rend() noexcept { return std::begin(arr); }
    const_reverse_iterator rend() const noexcept { return std::cbegin(arr); }
    const_reverse_iterator crend() const noexcept { return std::cbegin(arr); }

  public: /* Functions */
    ColorType& operator[](const Size i) noexcept;
    ColorType& getPixel(const Size inX, const Size inY);

  private: /* Raw Data */
    ColorType arr[x*y];
  };
}

namespace SPGL // Implementation
{
  // Information
  template<Size x, Size y, class C>
  Size Image<x, y, C>::height() const noexcept { return x; }

  template<Size x, Size y, class C>
  Size Image<x, y, C>::width()  const noexcept { return y; }

  template<Size x, Size y, class C>
  bool Image<x, y, C>::empty()  const noexcept { return height() && width(); }

  template<Size x, Size y, class C>
  Size Image<x, y, C>::size()   const noexcept { return width()*height(); }

  template<Size x, Size y, class C>
  Size Image<x, y, C>::bytes()  const noexcept { return size()*sizeof(C); }

  template<Size x, Size y, class C>
  C* Image<x, y, C>::data() noexcept { return arr; }

  // Copy Constructors
  template<Size x, Size y, class C>
  Image<x, y, C>::Image(const Image &in) noexcept 
  {
    // Copy array information into internal array
    std::copy(in.begin(), in.end(), begin());
  }

  template<Size x, Size y, class C>
  Image<x, y, C>& Image<x, y, C>::operator=(const Image &in) noexcept
  {
    // Copy array information into internal array
    std::copy(in.begin(), in.end(), begin());
    return *this; 
  }

  // Custom Constructors
  template<Size x, Size y, class C>
  Image<x, y, C>::Image(const void* pixels)
  {
    const C* ptr = reinterpret_cast<const C*>(pixels);
    for(Size i = 0; i < size(); ++i) arr[i] = ptr[i];
  }

  template<Size x, Size y, class C>
  Image<x, y, C>& Image<x, y, C>::operator=(const void* pixels)
  {
    const C* ptr = reinterpret_cast<const C*>(pixels);
    for(Size i = 0; i < size(); ++i) arr[i] = ptr[i];
    return *this; 
  }

  template<Size x, Size y, class C>
  Image<x, y, C>::Image(const C in) noexcept
  { for(C& i : arr) i = in; }

  // Getters
  template<Size x, Size y, class C>
  C& Image<x, y, C>::operator[](const Size i) noexcept
  { return arr[i]; }

  template<Size x, Size y, class C>
  C& Image<x, y, C>::getPixel(const Size inX, const Size inY)
  {
    if(inX > x) throw std::out_of_range("X Too Large!");
    if(inY > y) throw std::out_of_range("Y Too Large!");
    return arr[inY*x + inX];
  }
}

#endif // SPGL_IMAGE_HPP
