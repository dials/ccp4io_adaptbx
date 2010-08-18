#ifndef CCP4IO_ADAPTBX_CCP4_DISKIO_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_DISKIO_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

namespace ccp4_diskio_fem {

using namespace fem::major_types;

inline
void
qopen(
  int const& iunit,
  str_cref lognam,
  str_cref atbuta)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qwrite(
  int const& /* iunit */,
  arr_cref<int> /* buffer */,
  int const& /* nitems */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qwrite(
  int const& /* iunit */,
  fem::integer_star_2 const& /* buffer */,
  int const& /* nitems */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qwrite(
  int const& /* iunit */,
  arr_ref<fem::integer_star_2> /* buffer */,
  int const& /* nitems */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qwrite(
  int const& /* iunit */,
  arr_cref<fem::integer_star_8> /* buffer */,
  int const& /* nitems */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
bool
qisnan(
  float const& value)
{
  bool return_value = fem::bool0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qclose(
  int const& /* iunit */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qseek(
  int const& /* iunit */,
  int const& /* irec */,
  int const& /* iel */,
  int const& /* lrecl */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qmode(
  int const& /* iunit */,
  int const& /* mode */,
  int& size)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qread(
  int const& /* iunit */,
  arr_ref<float> buffer,
  int const& /* nitems */,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qread(
  int const& /* iunit */,
  arr_ref<fem::integer_star_1> buffer,
  int const& /* nitems */,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qread(
  int const& /* iunit */,
  arr_ref<fem::integer_star_2> buffer,
  int const& /* nitems */,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qread(
  int const& /* iunit */,
  arr_ref<int> buffer,
  int const& /* nitems */,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qqinq(
  int const& iunit,
  str_cref lfn,
  str_ref filnam,
  int const& length)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qback(
  int const& /* iunit */,
  int const& /* lrecl */)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qreadi(
  int const& iunit,
  arr_ref<int> buffer,
  int const& nitems,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
qreadi2(
  int const& /* iunit */,
  arr_ref<fem::integer_star_2> buffer,
  int const& /* nitems */,
  int& result)
{
  throw TBXX_NOT_IMPLEMENTED();
}

} // namespace ccp4_diskio_fem

#endif // GUARD
