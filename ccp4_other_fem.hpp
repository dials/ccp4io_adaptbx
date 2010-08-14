#ifndef CCP4IO_ADAPTBX_CCP4_OTHER_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_OTHER_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

namespace ccp4_other_fem {

using namespace fem::major_types;

inline
bool
vaxvms()
{
  bool return_value = fem::bool0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ugtenv(
  str_cref /* namenv */,
  str_ref valenv)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
imsiz(
  str_cref /* odfile */,
  int& nrec,
  int& iylen)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
readpack_word(
  arr_ref<fem::integer_star_2> datapack,
  str_cref /* filn */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

} // namespace ccp4_other_fem

#endif // GUARD
