#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_mtzlib_fem.hpp"

extern "C" {

typedef unsigned int ccp4_ftn_logical;

void
lwrefl_(
  int const* mindx,
  float const* adata);

void
mtzini_();

void
lrcell_(
  int const* mindx,
  float* cellp);

void
lrclos_(
  int const* mindx);

void
lrinfo_(
  int const* mindx,
  char* versnx,
  int* ncolx,
  int* nreflx,
  /*arr_ref<float, 2>*/ float* ranges,
  int versnx_len);

void
lropen_(
  int const* mindx,
  char const* filnam,
  int const* iprint,
  int* ifail,
  int filnam_len);

void
lrsymi_(
  int const* mindx,
  int* nsympx,
  char* ltypex,
  int* nspgrx,
  char* spgrnx,
  char* pgnamx,
  int ltypex_len,
  int spgrnx_len,
  int pgnamx_len);

void
lrsymm_(
  int const* mindx,
  int* nsymx,
  /*arr_ref<float, 3>*/ float* rsymx);

void
lridx_(
  int const* mindx,
  /*str_arr_ref<>*/ char* pname,
  /*str_arr_ref<>*/ char* xname,
  /*str_arr_ref<>*/ char* dname,
  int* isets,
  /*arr_ref<float, 2>*/ float* datcell,
  float* datwave,
  int* ndatasets,
  int pname_len,
  int xname_len,
  int dname_len);

void
lrassn_(
  int const* mindx,
  /*str_arr_cref<>*/ char const* lsprgi,
  int const* nlprgi,
  int* lookup,
  /*str_arr_ref<>*/ char* ctprgi,
  int lsprgi_len,
  int ctprgi_len);

void
lkyin_(
  int const* mindx,
  /*str_arr_cref<>*/ char const* lsprgi,
  int const* nlprgi,
  int const* ntok,
  char const* line,
  int const* ibeg,
  int const* iend,
  int lsprgi_len,
  int line_len);

void
lrclid_(
  int const* mindx,
  int* csetid,
  int* ncol);

void
lrrefm_(
  int const* mindx,
  ccp4_ftn_logical* logmss);

void
lrrefl_(
  int const* mindx,
  float* resol,
  float const* adata,
  ccp4_ftn_logical* eof);

void
lwclos_(
  int const* mindx,
  int const* iprint);

void
lwcell_(
  int const* mindx,
  float const* cellp);

void
lwclab_(
  int const* mindx,
  /*str_arr_cref<>*/ char const* lsprgo,
  int const* nlprgo,
  /*str_arr_cref<>*/ char const* ctprgo,
  int const* iappnd,
  int lsprgo_len,
  int ctprgo_len);

void
lwhstl_(
  int const* mindx,
  char const* extra,
  int extra_len);

void
lwopen_(
  int const* mindx,
  char const* filnam,
  int filnam_len);

void
lwsymm_(
  int const* mindx,
  int const* nsymx,
  int const* nsympx,
  /*arr_cref<float, 3>*/ float const* rsymx,
  char const* ltypex,
  int const* nspgrx,
  char const* spgrnx,
  char const* pgnamx,
  int ltypex,
  int spgrnx,
  int pgnamx);

void
lwidas_(
  int const* mindx,
  int const* nlprgo,
  /*str_arr_cref<>*/ char const* pname,
  /*str_arr_cref<>*/ char const* dname,
  int const* iappnd,
  int pname_len,
  int dname_len);

void
lwidx_(
  int const* mindx,
  char* project_name,
  char* crystal_name,
  char* dataset_name,
  float const* datcell,
  float const* datwave,
  int project_name_len,
  int crystal_name_len,
  int dataset_name_len);

void
lwtitl_(
  int const* mindx,
  char const* ntitle,
  int const* flag,
  int ntitle_len);

} // extern "C"

namespace ccp4_mtzlib_fem {

using namespace fem::major_types;

void
lwrefl(
  int const& mindx,
  arr_cref<float> adata)
{
  lwrefl_(&mindx, adata.begin());
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

} // namespace ccp4_mtzlib_fem
