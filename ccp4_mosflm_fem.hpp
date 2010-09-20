#ifndef CCP4IO_ADAPTBX_CCP4_MOSFLM_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_MOSFLM_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

extern "C" {

int
fileaccess_(
  const char* odfile,
  const int *odfile_len);

void
openfile_(
  /* arr_cref<int> */ int const* ifilenam,
  /* arr_ref<fem::integer_star_2> */ short int* image);

void
pilatus_c_(
  int* ierr,
  int const* mode,
  int const* nrec,
  int const* iylen,
  /*arr_ref<fem::integer_star_2>*/ short* image,
  /*str_arr_cref<>*/ char const* odfile);

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

inline
void
openfile(
  arr_cref<int> ifilenam,
  arr_ref<fem::integer_star_2> image)
{
  openfile_(ifilenam.begin(), image.begin());
}

inline
void
pilatus_c(
  int& ierr,
  int const& mode,
  int const& nrec,
  int const& iylen,
  arr_ref<fem::integer_star_2> image,
  str_arr_cref<> odfile)
{
  pilatus_c_(&ierr, &mode, &nrec, &iylen, image.begin(), odfile.begin());
}

} // namespace ccp4_mosflm_fem

#endif // GUARD
