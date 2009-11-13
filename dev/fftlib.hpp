#ifndef RESOLVE_FFTLIB_HPP
#define RESOLVE_FFTLIB_HPP

#include <resolve/umbrella.hpp>

namespace resolve {

void
cmplft(
  FArray1A_float x,
  FArray1A_float y,
  int const n,
  int5a d
);

void
hermft(
  FArray1A_float x,
  FArray1A_float y,
  int const n,
  int5a dim
);

void
realft(
  FArray1A_float even,
  FArray1A_float odd,
  int const n,
  int5a dim
);

void
rsymft(
  FArray1A_float x,
  int const n,
  int5a dim
);

void
sdiad(
  FArray1A_float x,
  FArray1A_float y,
  int const n,
  int5a dim
);

void
inv21(
  FArray1A_float x,
  FArray1A_float y,
  int const n,
  int5a d
);

} // namespace resolve

#endif // GUARD
