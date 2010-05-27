#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_library_fem.hpp"
#include "ccp4_calls_extern_c.hpp"

namespace ccp4_library_fem {

using namespace fem::major_types;

void
qnan(
  float& value)
{
  qnan_(&value);
}

} // namespace ccp4_library_fem
