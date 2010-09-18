#ifndef CCP4IO_ADAPTBX_CCP4_MOSFLM_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_MOSFLM_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

extern "C" {

int
fileaccess_(
  const char* odfile,
  const int *odfile_len);

}

namespace ccp4_mosflm_fem {

using namespace fem::major_types;

inline
int
fileaccess(
  str_cref odfile,
  int const& len_odfile)
{
  return fileaccess_(odfile.elems(), &len_odfile);
}

} // namespace ccp4_mosflm_fem

#endif // GUARD
