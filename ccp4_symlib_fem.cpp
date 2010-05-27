#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_symlib_fem.hpp"
#include "ccp4_calls_extern_c.hpp"

namespace ccp4_symlib_fem {

using namespace fem::major_types;

void
symfr2(
  str_cref icol,
  int const& i1,
  int& ns,
  arr_ref<float, 3> rot)
{
  symfr2_(
    icol.elems(),
    &i1,
    &ns,
    rot.begin(),
    icol.len());
}

void
msymlb(
  int const& ist,
  int& lspgrp,
  str_ref namspg,
  str_ref nampg,
  int& nsymp,
  int& nsym,
  arr_ref<float, 3> rot)
{
  msymlb_(
    &ist, &lspgrp, namspg.elems(), nampg.elems(), &nsymp, &nsym, rot.begin(),
    namspg.len(), nampg.len());
}

void
symtr3(
  int const& nsm,
  arr_cref<float, 3> rsm,
  str_arr_ref<> symchs,
  int const& iprint)
{
  symtr3_(&nsm, rsm.begin(), symchs.begin(), &iprint, symchs.len());
}

void
asuset(
  str_cref spgnam,
  int const& numsgp,
  str_ref pgname,
  int const& msym,
  arr_ref<float, 3> rrsym,
  int& msymp,
  int& mlaue,
  bool const& lprint)
{
  ccp4_ftn_logical lprint_ = lprint;
  asuset_(
    spgnam.elems(),
    &numsgp,
    pgname.elems(),
    &msym,
    rrsym.begin(),
    &msymp,
    &mlaue,
    &lprint_,
    spgnam.len(),
    pgname.len());
}

void
asuput(
  arr_cref<int> ihkl,
  arr_ref<int> jhkl,
  int& isym)
{
  asuput_(ihkl.begin(), jhkl.begin(), &isym);
}

void
asuget(
  arr_cref<int> ihkl,
  arr_ref<int> jhkl,
  int const& isym)
{
  asuget_(ihkl.begin(), jhkl.begin(), &isym);
}

void
centric(
  int const& nsm,
  arr_cref<float, 3> rsm,
  int const& iprint)
{
  centric_(&nsm, rsm.begin(), &iprint);
}

void
centr(
  arr_cref<int> hkl,
  int& ic)
{
  centr_(hkl.begin(), &ic);
}

void
setrsl(
  float const& a,
  float const& b,
  float const& c,
  float const& alpha,
  float const& beta,
  float const& gamma)
{
  setrsl_(&a, &b, &c, &alpha, &beta, &gamma);
}

float
sthlsq(
  int const& ih,
  int const& ik,
  int const& il)
{
  float reso;
  sthlsq1_(&reso, &ih, &ik, &il);
  return reso;
}

} // namespace ccp4_symlib_fem
