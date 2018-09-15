#ifndef SPGL_IMAGE_HPP
#define SPGL_IMAGE_HPP 1

#include <vector>

#include "TypeNames.hpp"
#include "Vector2D.hpp"
#include "Color.hpp"

namespace spgl // Initalization
{
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
    ~Image();

    Image(const Image &in);
    Image(const Size &x, const Size &y, const Color &f = Color());
    Image(const Size &x, const Size &y, const Color* p);

    void create(const Size &x,
                const Size &y,
                const Color &f = Color());

    void create(const Size &x,
                const Size &y,
                const Color* p);

  public: /* Functions */
    Color& operator[](const Size &i);
    Color& getPixel(const Size &x, const Size &y);

  private: /* Raw Data */
    std::vector<Color> pixels;
    Vector2D<Size> i_size;
  };
}

namespace spgl // Definitions
{
  // Information
  Size Image::height() const { return i_size.y; }
  Size Image::width()  const { return i_size.x; }
  bool Image::empty()  const { return height() && width(); }
  Size Image::size()   const { return width()*height(); }
  Size Image::bytes()  const { return size()*sizeof(Color); }
  Color* Image::data() { return pixels.data(); }

  // Constructors
  Image::Image() { }
  Image::~Image(){ }

  Image::Image(const Image &in)
    : pixels{in.pixels}, i_size{in.i_size} {}

  Image::Image(const Size &x, const Size &y, const Color &f)
  { create(x, y, f); }

  Image::Image(const Size &x, const Size &y, const Color* p)
  { create(x, y, p); }

  void Image::create( const Size &x,
                      const Size &y,
                      const Color &f)
  {
    if(x && y)
    {
      i_size.x = x; i_size.y = y;
      std::vector<Color> temp(x*y);
      for(Color &i : temp) i = f;
      temp.swap(pixels);
    }
    else
    {
      std::vector<Color>().swap(pixels);
      i_size.x = 0; i_size.y = 0;
    }
  }

  void Image::create( const Size &x,
                      const Size &y,
                      const Color* p)
  {
    if(x && y)
    {
      i_size.x = x; i_size.y = y;
      std::vector<Color> temp(p, p + x * y * sizeof(Color));
      temp.swap(temp);
    }
    else
    {
      std::vector<Color>().swap(pixels);
      i_size.x = 0; i_size.y = 0;
    }
  }

  Color& Image::operator[](const Size &i)
  { return pixels[i]; }

  Color& Image::getPixel(const Size &x, const Size &y)
  { return pixels[y*i_size.x + x]; }
}

#endif // SPGL_IMAGE_HPP
