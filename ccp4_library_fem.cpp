#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_library_fem.hpp"

extern "C" {

void
qnan_(
  float* value);

} // extern "C"

namespace ccp4_library_fem {

using namespace fem::major_types;

void
qnan(
  float& value)
{
  qnan_(&value);
}

} // namespace ccp4_library_fem
