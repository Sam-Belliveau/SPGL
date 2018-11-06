# SPGL
Simple Pixel Graphics Library is a library made for drawing pixel images.

It makes this really simple. Here is an example of a Mandelbrot Renderer made with this library.

```cpp
#include <iostream>
#include <complex>

#include "SPGL/SPGL.hpp"

int main()
{
  const SPGL::Size width = 640;
  const SPGL::Size height = 480;

  SPGL::Window<width, height, 1> win("COPRIMES");
  SPGL::Image<width, height> img = SPGL::Color::Black;

  for(SPGL::Size y = 0; y < height; ++y)
    for(SPGL::Size x = 0; x < width; ++x)
    {
      const std::complex<double> C((x - width*0.75) / (width/4.0),
                                   (y - height*0.5) / (height/3.0));
      std::complex<double> Z(C);
      SPGL::UInt8 iter = 0;

      while(++iter < 255 && Z.real()*Z.real() + Z.imag()*Z.imag() < 4)
        Z = Z*Z + C;

      if(iter != 255) img.getPixel(x, y) = SPGL::Color::HSV(iter);
    }

  while(win.isRunning()) { win.renderImage(img); win.update(); }
}
```
