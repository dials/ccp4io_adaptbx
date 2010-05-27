#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_calls_fem.hpp"
#include "ccp4_calls_extern_c.hpp"

namespace ccp4_calls_fem {

using namespace fem::major_types;

void
lerror(
  int const& errflg,
  int const& ifail,
  str_cref errmsg)
{
  throw BOOST_ADAPTBX_NOT_IMPLEMENTED();
}

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
mwrhdl(
  int const& iunit,
  str_cref mapnam,
  str_cref title,
  int const& nsec,
  arr_cref<int> iuvw,
  arr_cref<int> mxyz,
  int const& nw1,
  int const& nu1,
  int const& nu2,
  int const& nv1,
  int const& nv2,
  arr_cref<float> cell,
  int const& lspgrp,
  int& lmode)
{
  mwrhdl_(
    &iunit,
    mapnam.elems(),
    title.elems(),
    &nsec,
    iuvw.begin(),
    mxyz.begin(),
    &nw1,
    &nu1,
    &nu2,
    &nv1,
    &nv2,
    cell.begin(),
    &lspgrp,
    &lmode,
    mapnam.len(),
    title.len());
}

void
mwrsec(
  int const& iunit,
  arr_cref<float, 2> x,
  int const& mu,
  int const& mv,
  int const& iu1,
  int const& iu2,
  int const& iv1,
  int const& iv2)
{
  mwrsec_(&iunit, x.begin(), &mu, &mv, &iu1, &iu2, &iv1, &iv2);
}

void
mwclose(
  int const& iunit)
{
  mwclose_(&iunit);
}

void
msywrt(
  int const& iunit,
  int const& nsym,
  arr_cref<float, 3> rot)
{
  msywrt_(&iunit, &nsym, rot.begin());
}

void
lwrefl(
  int const& mindx,
  arr_cref<float> adata)
{
  lwrefl_(&mindx, adata.begin());
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
mtzini()
{
  mtzini_();
}

void
lrcell(
  int const& mindx,
  arr_ref<float> cellp)
{
  lrcell_(&mindx, cellp.begin());
}

void
lrclos(
  int const& mindx)
{
  lrclos_(&mindx);
}

void
lrinfo(
  int const& mindx,
  str_ref versnx,
  int& ncolx,
  int& nreflx,
  arr_ref<float, 2> ranges)
{
  lrinfo_(&mindx, versnx.elems(), &ncolx, &nreflx, ranges.begin(),
    versnx.len());
}

void
qnan(
  float& value)
{
  qnan_(&value);
}

void
parser(
  str_ref key,
  str_ref line,
  arr_ref<int> ibeg,
  arr_ref<int> iend,
  arr_ref<int> ityp,
  arr_ref<float> fvalue,
  str_arr_ref<> cvalue,
  arr_ref<int> idec,
  int& ntok,
  bool& lend,
  bool const& print)
{
  ccp4_ftn_logical lend_ = lend;
  ccp4_ftn_logical print_ = print;
  parser_(
    key.elems(),
    line.elems(),
    ibeg.begin(),
    iend.begin(),
    ityp.begin(),
    fvalue.begin(),
    cvalue.begin(),
    idec.begin(),
    &ntok,
    &lend_,
    &print_,
    key.len(),
    line.len(),
    cvalue.len());
  lend = static_cast<bool>(lend_);
}

void
lropen(
  int const& mindx,
  str_cref filnam,
  int const& iprint,
  int& ifail)
{
  lropen_(&mindx, filnam.elems(), &iprint, &ifail, filnam.len());
}

void
lrsymi(
  int const& mindx,
  int& nsympx,
  str_ref ltypex,
  int& nspgrx,
  str_ref spgrnx,
  str_ref pgnamx)
{
  lrsymi_(
    &mindx, &nsympx, ltypex.elems(), &nspgrx, spgrnx.elems(), pgnamx.elems(),
    ltypex.len(), spgrnx.len(), pgnamx.len());
}

void
lrsymm(
  int const& mindx,
  int& nsymx,
  arr_ref<float, 3> rsymx)
{
  lrsymm_(&mindx, &nsymx, rsymx.begin());
}

void
lridx(
  int const& mindx,
  str_arr_ref<> pname,
  str_arr_ref<> xname,
  str_arr_ref<> dname,
  arr_ref<int> isets,
  arr_ref<float, 2> datcell,
  arr_ref<float> datwave,
  int& ndatasets)
{
  lridx_(
    &mindx,
    pname.begin(),
    xname.begin(),
    dname.begin(),
    isets.begin(),
    datcell.begin(),
    datwave.begin(),
    &ndatasets,
    pname.len(),
    xname.len(),
    dname.len());
}

void
lrassn(
  int const& mindx,
  str_arr_cref<> lsprgi,
  int const& nlprgi,
  arr_ref<int> lookup,
  str_arr_ref<> ctprgi)
{
  lrassn_(
    &mindx, lsprgi.begin(), &nlprgi, lookup.begin(), ctprgi.begin(),
    lsprgi.len(), ctprgi.len());
}

void
lkyin(
  int const& mindx,
  str_arr_cref<> lsprgi,
  int const& nlprgi,
  int const& ntok,
  str_cref line,
  arr_cref<int> ibeg,
  arr_cref<int> iend)
{
  lkyin_(
    &mindx,
    lsprgi.begin(),
    &nlprgi,
    &ntok,
    line.elems(),
    ibeg.begin(),
    iend.begin(),
    lsprgi.len(),
    line.len());
}

void
lrclid(
  int const& mindx,
  arr_ref<int> csetid,
  int& ncol)
{
  lrclid_(&mindx, csetid.begin(), &ncol);
}

void
lrrefm(
  int const& mindx,
  arr_ref<bool> logmss)
{
  size_t n = logmss.size_1d();
  std::vector<ccp4_ftn_logical> logmss_;
  logmss_.reserve(n);
  bool* logmss_begin = logmss.begin();
  for(size_t i=0;i<n;i++) {
    logmss_.push_back(logmss_begin[i]);
  }
  lrrefm_(&mindx, &*logmss_.begin());
  for(size_t i=0;i<n;i++) {
    logmss_begin[i] = logmss_[i];
  }
}

void
lrrefl(
  int const& mindx,
  float& resol,
  arr_cref<float> adata,
  bool& eof)
{
  ccp4_ftn_logical eof_ = eof;
  lrrefl_(&mindx, &resol, adata.begin(), &eof_);
  eof = static_cast<bool>(eof_);
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
lwclos(
  int const& mindx,
  int const& iprint)
{
  lwclos_(&mindx, &iprint);
}

void
lwcell(
  int const& mindx,
  arr_cref<float> cellp)
{
  lwcell_(&mindx, cellp.begin());
}

void
lwclab(
  int const& mindx,
  str_arr_cref<> lsprgo,
  int const& nlprgo,
  str_arr_cref<> ctprgo,
  int const& iappnd)
{
  lwclab_(
    &mindx, lsprgo.begin(), &nlprgo, ctprgo.begin(), &iappnd,
    lsprgo.len(), ctprgo.len());
}

void
lwhstl(
  int const& mindx,
  str_cref extra)
{
  lwhstl_(&mindx, extra.elems(), extra.len());
}

void
lwopen(
  int const& mindx,
  str_cref filnam)
{
  lwopen_(&mindx, filnam.elems(), filnam.len());
}

void
lwsymm(
  int const& mindx,
  int const& nsymx,
  int const& nsympx,
  arr_cref<float, 3> rsymx,
  str_cref ltypex,
  int const& nspgrx,
  str_cref spgrnx,
  str_cref pgnamx)
{
  lwsymm_(
    &mindx,
    &nsymx,
    &nsympx,
    rsymx.begin(),
    ltypex.elems(),
    &nspgrx,
    spgrnx.elems(),
    pgnamx.elems(),
    ltypex.len(),
    spgrnx.len(),
    pgnamx.len());
}

void
lwidas(
  int const& mindx,
  int const& nlprgo,
  str_arr_cref<> pname,
  str_arr_cref<> dname,
  int const& iappnd)
{
  lwidas_(
    &mindx,
    &nlprgo,
    pname.begin(),
    dname.begin(),
    &iappnd,
    pname.len(),
    dname.len());
}

void
lwidx(
  int const& mindx,
  str_ref project_name,
  str_ref crystal_name,
  str_ref dataset_name,
  arr_cref<float> datcell,
  float const& datwave)
{
  lwidx_(
    &mindx,
    project_name.elems(),
    crystal_name.elems(),
    dataset_name.elems(),
    datcell.begin(),
    &datwave,
    project_name.len(),
    crystal_name.len(),
    dataset_name.len());
}

void
lwtitl(
  int const& mindx,
  str_cref ntitle,
  int const& flag)
{
  lwtitl_(&mindx, ntitle.elems(), &flag, ntitle.len());
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

} // namespace ccp4_calls_fem
