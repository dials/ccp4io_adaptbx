#ifndef CCP4IO_ADAPTBX_CCP4_CCPLIB_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_CCPLIB_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

namespace ccp4_ccplib_fem {

using namespace fem::major_types;

inline
void
ccpupc(
  str_ref string)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
int
lenstr(
  str_cref string)
{
  int return_value = fem::int0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccperr(
  int const& istat,
  str_cref errstr)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccpdpn(
  int& iun,
  str_cref lognam,
  str_cref status,
  str_cref type,
  int const& lrec,
  int& ifail)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccpdat(
  str_ref caldat)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccplwc(
  str_ref string)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
bool
litend(
  int const& /* idum */)
{
  bool return_value = fem::bool0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
bool
ccponl(
  int const& /* idum */)
{
  bool return_value = fem::bool0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
int
ccpe2i(
  str_cref name,
  int const& defval)
{
  int return_value = fem::int0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccp4_version(
  str_ref version)
{
  throw TBXX_NOT_IMPLEMENTED();
}

inline
void
ccpfyp()
{
  throw TBXX_NOT_IMPLEMENTED();
}

} // namespace ccp4_ccplib_fem

#endif // GUARD
