#ifndef SPGL_VECTOR2D_HPP
#define SPGL_VECTOR2D_HPP 1

#include "TypeNames.hpp"

namespace spgl
{
  template<class T = Int32>
  struct Vector2D
  {
  public: /* Functions */
    Vector2D() : x{0}, y{0} {}

    Vector2D(const Vector2D &in) :
      x{in.x}, y{in.y} {}

    Vector2D(const T &ix, const T &iy):
      x{ix}, y{iy} {}

    template<class iT>
    operator Vector2D<iT>()
    { return Vector2D<iT>(static_cast<iT>(x), static_cast<iT>(y)); }

  public: /* Variables */
    T x, y;
  };
}

#endif // SPGL_VECTOR2D_HPP
