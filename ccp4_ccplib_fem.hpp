#ifndef CCP4IO_ADAPTBX_CCP4_CCPLIB_FEM_HPP
#define CCP4IO_ADAPTBX_CCP4_CCPLIB_FEM_HPP

#include <fem.hpp> // Fortran EMulation library of fable module

extern "C" {

void
ccp4_version_(
  char* version,
  int version_len);

void
ccpfyp_();

}

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
ccpdpn(
  int const& iun,
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
litend()
{
  bool return_value = fem::bool0;
  throw TBXX_NOT_IMPLEMENTED();
}

inline
bool
ccponl(
  int const& /* idum */)
{
  return false;
}

inline
int
ccpe2i(
  str_cref name,
  int const& defval)
{
  std::string k = fem::utils::strip_leading_and_trailing_blank_padding(name);
  char* v = std::getenv(k.c_str());
  if (v == 0) return defval;
  int result;
  int n = std::sscanf(v, "%d", result);
  if (n != 1) {
    std::ostringstream o;
    o << "Environment variable \""
      << std::string(k)
      << "\" is not an integer: \""
      << v << "\"";
    throw std::runtime_error(o.str());
  }
  return result;
}

inline
void
ccp4_version(
  str_ref version)
{
  ccp4_version_(version.elems(),version.len());
}

inline
void
ccpfyp()
{
  ccpfyp_();
}

} // namespace ccp4_ccplib_fem

#endif // GUARD
