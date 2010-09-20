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

void
cbfwrap_(
  int* ierr,
  /*arr_ref<int>*/ int* cbf_int,
  /*arr_ref<fem::integer_star_4>*/ int* cbf_int4,
  /*arr_ref<double>*/ double* cbf_double,
  /*str_arr_ref<>*/ char* cbf_char,
  char const* odfile,
  /*arr_ref<fem::integer_star_2>*/ short* image,
  int const* mode);
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

inline
void
cbfwrap(
  int& ierr,
  arr_ref<int> cbf_int,
  arr_ref<fem::integer_star_4> cbf_int4,
  arr_ref<double> cbf_double,
  str_arr_ref<> cbf_char,
  str_cref odfile,
  arr_ref<fem::integer_star_2> image,
  int const& mode)
{
  cbfwrap_(&ierr, cbf_int.begin(), cbf_int4.begin(), cbf_double.begin(),
           cbf_char.begin(), odfile.elems(), image.begin(), &mode);
}

} // namespace ccp4_mosflm_fem

#endif // GUARD
