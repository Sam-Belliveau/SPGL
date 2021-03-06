#ifndef SPGL_COLOR_HPP
#define SPGL_COLOR_HPP 1

#include <algorithm> // std::max

#include "TypeNames.hpp"

namespace SPGL // Definitions
{
    struct Color
    {
    private: /* Helper Functions */
        constexpr static UInt8 clamp(IntMax i) noexcept 
        {
            if(255 < i) return 255;
            if(i < 0) return 0;
            return UInt8(i);
        }

    public: /* HSV Class */
        struct HSV
        {
        public: // Methods
            // Default Constructor
            constexpr HSV() noexcept : v{0}, s{0}, h{0} {}

            // Copy Constructors
            HSV(const HSV &in) = default;
            HSV& operator=(const HSV &in) = default;

            // Custom Constructors
            constexpr HSV(const IntMax ih, const IntMax is = 255, const IntMax iv = 255) noexcept
                : v{clamp(iv)}, s{clamp(is)}, h{clamp(ih)} {}

            constexpr HSV(const Color in) noexcept
                : v{0}, s{0}, h{0}
            {
                /*** ALGORITHM BY: Leszek Szary (Stack Overflow User) ***/

                const UInt8 min = std::min({in.r, in.g, in.b});
                v = std::max({in.r, in.g, in.b});

                if (v == 0) { h = 0; s = 0; }
                else
                {
                    s = (255 * UInt16(v - min)) / v;
                    if (s == 0)         h = 0;
                    else if (v == in.r) h = 0   + 43 * (in.g - in.b) / (v - min);
                    else if (v == in.g) h = 85  + 43 * (in.b - in.r) / (v - min);
                    else                h = 171 + 43 * (in.r - in.g) / (v - min);
                }

                v = UInt16(v * 255) / UInt16(in.a);
            }

        public: // Setter Functions
            constexpr HSV& setH(IntMax ih) noexcept { h = clamp(ih); return *this; }
            constexpr HSV& setS(IntMax is) noexcept { s = clamp(is); return *this; }
            constexpr HSV& setV(IntMax iv) noexcept { v = clamp(iv); return *this; }

        public: // Variables
            UInt8 v;
            UInt8 s;
            UInt8 h;
        };

    public: /* Enum */
        /* HOW BYTEORDER WORKS:
         * It is stored as an 8 bit number,  *
         * MSB - 0 1   2 3   4 5   6 7 - LSB *
         *       [R]   [G]   [B]   [A]       *
         * Every 2 bits store the index      *
         * of a color channel, you can       *
         * order it any way that you want.   */
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
        constexpr Color() noexcept : a{0xff}, b{0}, g{0}, r{0} {}

        // Copy Constructor
        Color(const Color &in) = default;
        Color& operator=(const Color &in) = default;

        // RGBA Constructor
        constexpr Color(const IntMax ir, const IntMax ig,
                        const IntMax ib, const IntMax ia = 0xff) noexcept
                        : a{clamp(ia)}, b{clamp(ib)}, g{clamp(ig)}, r{clamp(ir)} {}

        // HSV Constructor
        constexpr Color(const HSV in) noexcept : a{0xff}, b{in.s}, g{in.s}, r{in.s}
        {
            /*** ALGORITHM BY: Leszek Szary (Stack Overflow User) ***/
            if (in.s != 0)
            {
                const UInt16 rem = (in.h % 43) * 6;

                const UInt8 p = (UInt16(in.v) * (255 - in.s)) >> 8;
                const UInt8 q = (UInt16(in.v) * (255 - ((in.s *  rem) >> 8))) >> 8;
                const UInt8 t = (UInt16(in.v) * (255 - ((in.s * (255 - rem)) >> 8))) >> 8;

                switch (in.h / 43)
                {
                    case 0:  r = in.v; g = t; b = p; break;
                    case 1:  r = q; g = in.v; b = p; break;
                    case 2:  r = p; g = in.v; b = t; break;
                    case 3:  r = p; g = q; b = in.v; break;
                    case 4:  r = t; g = p; b = in.v; break;
                    default: r = in.v; g = p; b = q; break;
                }
            }
        }

        // Grayscale Constructor
        constexpr Color(const UInt8 in) noexcept : a{0xff}, b{in}, g{in}, r{in} {}

        // 32 bit int output
        template<ByteOrder order = ByteOrder::RGBA>
        constexpr UInt32 toInt() const noexcept
        {
            return  (r << ((order >> 5) & 6)) | (g << ((order >> 3) & 6)) |
                    (b << ((order >> 1) & 6)) | (a << ((order << 1) & 6));
        }

    public: /* Variables */
        UInt8 a; // Variables are initalized
        UInt8 b; // Backwards inorder to keep
        UInt8 g; // RGBA order when used by
        UInt8 r; // SDL2

    public: /* Setter Functions */
        constexpr Color& setA(IntMax ia) noexcept { a = clamp(ia); return *this; }
        constexpr Color& setB(IntMax ib) noexcept { b = clamp(ib); return *this; }
        constexpr Color& setG(IntMax ig) noexcept { g = clamp(ig); return *this; }
        constexpr Color& setR(IntMax ir) noexcept { r = clamp(ir); return *this; }

    public: /* Math Operators */
        constexpr Color& operator+=(const Color& rhs) noexcept
        {
            setA(IntMax(a) + IntMax(rhs.a));
            setB(IntMax(b) + IntMax(rhs.b));
            setG(IntMax(g) + IntMax(rhs.g));
            setR(IntMax(r) + IntMax(rhs.r));
            return *this;
        }

        constexpr Color& operator-=(const Color& rhs) noexcept
        {
            setA(IntMax(a) - IntMax(rhs.a));
            setB(IntMax(b) - IntMax(rhs.b));
            setG(IntMax(g) - IntMax(rhs.g));
            setR(IntMax(r) - IntMax(rhs.r));
            return *this;
        }

        template<typename T>
        constexpr Color& operator*=(const T& rhs) noexcept
        {
            setA(IntMax(T(a) * rhs));
            setB(IntMax(T(b) * rhs));
            setG(IntMax(T(g) * rhs));
            setR(IntMax(T(r) * rhs));
            return *this;
        }

        template<typename T>
        constexpr Color& operator/=(const T& rhs) noexcept
        {
            setA(IntMax(T(a) / rhs));
            setB(IntMax(T(b) / rhs));
            setG(IntMax(T(g) / rhs));
            setR(IntMax(T(r) / rhs));
            return *this;
        }

    public: /* Static Colors */
        static const Color Black, White;
        static const Color Red, Green, Blue;
        static const Color Orange, Yellow, Cyan, Purple;
    };
}

namespace SPGL // Implementation
{
    // Operators
    constexpr bool operator==(const Color a, const Color b)
    { return (a.r == b.r) && (a.g == b.g) && (a.b == b.b) && (a.a == b.a); }

    constexpr bool operator!=(const Color a, const Color b)
    { return !(a == b); }

    // Math Operators
    constexpr Color operator+(Color lhs, const Color& rhs) 
    { return lhs += rhs; }

    constexpr Color operator-(Color lhs, const Color& rhs) 
    { return lhs -= rhs; }

    template<typename T>
    constexpr Color operator*(Color lhs, const T& rhs) 
    { return lhs *= rhs; }

    template<typename T>
    constexpr Color operator*(const T& lhs, Color rhs) 
    { return rhs *= lhs; }

    template<typename T>
    constexpr Color operator/(Color lhs, const T& rhs) 
    { return lhs /= rhs; }

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
