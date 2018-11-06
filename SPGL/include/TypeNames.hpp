#ifndef SPGL_TYPENAMES_HPP
#define SPGL_TYPENAMES_HPP 1

#include <cstdint>

namespace SPGL
{
  /* Floats */
  using Float80 = long double;
  using Float64 = double;
  using Float32 = float;

  /* Integers */
  using Size = std::size_t;

  using UInt64 = uint64_t;
  using Int64 = int64_t;

  using UInt32 = uint32_t;
  using Int32 = int32_t;

  using UInt16 = uint16_t;
  using Int16 = int16_t;

  using UInt8 = uint8_t;
  using Int8 = int8_t;
}

#endif //SPGL_TYPENAMES_HPP
