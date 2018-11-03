#ifndef SPGL_COLOR_HPP
#define SPGL_COLOR_HPP 1

#include "TypeNames.hpp"

namespace spgl // Initalization
{
  struct Color
  {
  public: /* Enum */
    /* HOW BYTEORDER WORKS:
     * It is stored as an 8 bit number,
     * MSB - 0 1   2 3   4 5   6 7 - LSB
     *       [R]   [G]   [B]   [A]
     * Every 2 bits store the index
     * of a color channel, you can
     * order it any way that you want. */
    enum ByteOrder : UInt8
    {
      RGBA = 0x1b, RGAB = 0x1e, RBGA = 0x27,
      RBAG = 0x36, RAGB = 0x2d, RABG = 0x39,
      GRBA = 0x4b, GRAB = 0x4e, GBRA = 0x87,
      GBAR = 0xc6, GARB = 0x8d, GABR = 0xc9,
      BRGA = 0x63, BRAG = 0x72, BGRA = 0x93,
      BGAR = 0xd2, BARG = 0xb1, BAGR = 0xe1,
      ARGB = 0x6c, ARBG = 0x78, AGRB = 0x9c,
      AGBR = 0xd8, ABRG = 0xb4, ABGR = 0xe4
    };

  public: /* Functions */
    // Default Constructor
    constexpr Color() :
      a{0xff}, b{0}, g{0}, r{0} {}

    // Copy Constructor
    constexpr Color(const Color &in) :
      a{in.a}, b{in.b}, g{in.g}, r{in.r} {}

    // RGBA Constructor
    constexpr Color(const UInt8& ir, const UInt8& ig,
                    const UInt8& ib, const UInt8& ia = 0xff)
                    : a{ia}, b{ib} , g{ig}, r{ir} {}

    // Grayscale Constructor
    constexpr Color(const UInt8& in) : a{0xff}, b{in} , g{in}, r{in} {}

    // 32 bit int output
    template<ByteOrder order = ByteOrder::RGBA>
    constexpr UInt32 toInt() const
    {
      return  (r << ((order >> 5) & 6)) | (g << ((order >> 3) & 6)) |
              (b << ((order >> 1) & 6)) | (a << ((order << 1) & 6));
    }

  public: /* Variables */
    UInt8 a;
    UInt8 b;
    UInt8 g;
    UInt8 r;

  public: /* Static Colors */
    /*
    static const Color  Black (0x00, 0x00, 0x00),
                        White (0xff, 0xff, 0xff);
    static const Color  Red   (0xff, 0x00, 0x00),
                        Green (0x00, 0xff, 0x00),
                        Blue  (0x00, 0x00, 0xff);
    static const Color  Orange(0xff, 0x7f, 0x00),
                        Yellow(0xff, 0xff, 0x00),
                        Cyan  (0x00, 0xff, 0xff),
                        Purple(0xff, 0x00, 0xff);
    */
  };
}

#endif // SPGL_COLOR_HPP
