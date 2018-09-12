#ifndef SPGL_COLOR_HPP
#define SPGL_COLOR_HPP 1

#include "TypeNames.hpp"
#include "Vector2D.hpp"

#define LITTLE_E 1

namespace SPGL
{
  struct Color
  {
  public: /* Functions */
    Color(){ setRGB(0, 0, 0); }

    // Copy
    Color(const Color &in)
    { setColor(in); }

    // RGB input
    Color(const UInt8_t &ir, const UInt8_t &ig, const UInt8_t &ib)
    { setRGB(ir, ig, ib); }

    // Gray Scale Input
    Color(const UInt8_t &in)
    { setRGB(in, in, in); }

    constexpr void setRGB(const UInt8_t &ir, const UInt8_t &ig, const UInt8_t &ib)
    { r = ir; g = ig; b = ib; }

    constexpr void setColor(const Color &in)
    { r = in.r; g = in.g; b = in.b; }

  public: /* Variables */
    #ifndef LITTLE_E
      UInt8_t UNUSED_BUFFER;
      UInt8_t r = 0, g = 0, b = 0;
    #else
      UInt8_t b = 0, g = 0, r = 0;
      UInt8_t UNUSED_BUFFER;
    #endif
  };
}

#endif // SPGL_COLOR_HPP
