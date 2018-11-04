#ifndef SPGL_COLOR_HPP
#define SPGL_COLOR_HPP 1

#include "TypeNames.hpp"

namespace spgl // Definitions
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
    constexpr Color();

    // Copy Constructor
    constexpr Color(const Color &in);

    // RGBA Constructor
    constexpr Color(const UInt8 ir, const UInt8 ig,
                    const UInt8 ib, const UInt8 ia = 0xff);

    // Grayscale Constructor
    constexpr Color(const UInt8 in);

    // 32 bit int output
    template<ByteOrder order = ByteOrder::RGBA>
    constexpr UInt32 toInt() const;

    // HSV
    void setHSV(UInt8 h, UInt8 s, UInt8 v);

    // Operators
    friend bool operator==(const Color a, const Color b);

  public: /* Variables */
    UInt8 a;
    UInt8 b;
    UInt8 g;
    UInt8 r;

  public: /* Static Colors */
    static const Color Black;
    static const Color White;

    static const Color Red;
    static const Color Green;
    static const Color Blue;

    static const Color Orange;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Purple;
  };
}

namespace spgl // Implementation
{
  // Default Constructor
  constexpr Color::Color() :
    a{0xff}, b{0}, g{0}, r{0} {}

  // Copy Constructor
  constexpr Color::Color(const Color &in) :
    a{in.a}, b{in.b}, g{in.g}, r{in.r} {}

  // RGBA Constructor
  constexpr Color::Color(const UInt8 ir, const UInt8 ig,
                         const UInt8 ib, const UInt8 ia)
                         : a{ia}, b{ib} , g{ig}, r{ir} {}

  // Grayscale Constructor
  constexpr Color::Color(const UInt8 in) : a{0xff}, b{in} , g{in}, r{in} {}

  // 32 bit int output
  template<Color::ByteOrder order>
  constexpr UInt32 Color::toInt() const
  {
    return  (r << ((order >> 5) & 6)) | (g << ((order >> 3) & 6)) |
            (b << ((order >> 1) & 6)) | (a << ((order << 1) & 6));
  }

  // HSV
  void Color::setHSV(UInt8 h, UInt8 s = 0xff, UInt8 v = 0xff)
  {
    if (s == 0)
    {
        r = v;
        g = v;
        b = v;
    }

    UInt8 region, remainder, p, q, t;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (0xff - s)) >> 8;
    q = (v * (0xff - ((s * remainder) >> 8))) >> 8;
    t = (v * (0xff - ((s * (0xff - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:  r = v; g = t; b = p; break;
        case 1:  r = q; g = v; b = p; break;
        case 2:  r = p; g = v; b = t; break;
        case 3:  r = p; g = q; b = v; break;
        case 4:  r = t; g = p; b = v; break;
        default: r = v; g = p; b = q; break;
    }
  }

  // Operators
  bool operator==(const Color a, const Color b)
  { return (a.r == b.r) && (a.g == b.g) && (a.b == b.b) && (a.a == b.a); }

  // Static Variables
  const Color Color::Black = Color(0x00);
  const Color Color::White = Color(0xff);

  const Color Color::Red   = Color(0xff, 0x00, 0x00);
  const Color Color::Green = Color(0x00, 0xff, 0x00);
  const Color Color::Blue  = Color(0x00, 0x00, 0xff);

  const Color Color::Orange = Color(0xff, 0x7f, 0x00);
  const Color Color::Yellow = Color(0xff, 0xff, 0x00);
  const Color Color::Cyan   = Color(0x00, 0xff, 0xff);
  const Color Color::Purple = Color(0xff, 0x00, 0xff);
}

#endif // SPGL_COLOR_HPP
