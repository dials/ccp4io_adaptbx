#ifndef CCP4IO_CCP4_EXTERN_C_HPP
#define CCP4IO_CCP4_EXTERN_C_HPP

extern "C" {

typedef unsigned int ccp4_ftn_logical;

void
symfr2_(
  const char* icol,
  int const* i1,
  int* ns,
  float* rot, // [][4][4]
  int icol_len);

void
msymlb_(
  int const* ist,
  int* lspgrp,
  char* namspg,
  char* nampg,
  int* nsymp,
  int* nsym,
  float* rot, // [][4][4]
  int namspg_len,
  int nampg_len);

void
symtr3_(
  int const* nsm,
  /*arr_cref<float, 3>*/ float const* rsm,
  /*str_arr_ref<>*/ char* symchs,
  int const* iprint,
  int symchs_len);

void
asuset_(
  const char* spgnam,
  int const* numsgp,
  char* pgname,
  int const* msym,
  float* rrsym, // [][4][4]
  int* msymp,
  int* mlaue,
  ccp4_ftn_logical const* lprint,
  int spgnam_len,
  int pgname_len);

void
mwrhdl_(
  int const* iunit,
  char const* mapnam,
  char const* title,
  int const* nsec,
  int const* iuvw,
  int const* mxyz,
  int const* nw1,
  int const* nu1,
  int const* nu2,
  int const* nv1,
  int const* nv2,
  float const* cell,
  int const* lspgrp,
  int* lmode,
  int mapnam_len,
  int title_len);

void
mwrsec_(
  int const* iunit,
  /*arr_cref<float, 2>*/ float const* x,
  int const* mu,
  int const* mv,
  int const* iu1,
  int const* iu2,
  int const* iv1,
  int const* iv2);

void
mwclose_(
  int const* iunit);

void
msywrt_(
  int const* iunit,
  int const* nsym,
  /*arr_cref<float, 3>*/ float const* rot);

void
lwrefl_(
  int const* mindx,
  float const* adata);

void
asuput_(
  int const* ihkl,
  int* jhkl,
  int* isym);

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
qnan_(
  float* value);

void
parser_(
  char* key,
  char* line,
  int* ibeg,
  int* iend,
  int* ityp,
  float* fvalue,
  /*str_arr_ref<>*/ char* cvalue,
  int* idec,
  int* ntok,
  ccp4_ftn_logical* lend,
  ccp4_ftn_logical const* print,
  int key_len,
  int line_len,
  int cvalue_len);

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
asuget_(
  int const* ihkl,
  int* jhkl,
  int const* isym);

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

void
centric_(
  int const* nsm,
  /*arr_cref<float, 3>*/ float const* rsm,
  int const* iprint);

void
centr_(
  int const* hkl,
  int* ic);

void
setrsl_(
  float const* a,
  float const* b,
  float const* c,
  float const* alpha,
  float const* beta,
  float const* gamma);

void
sthlsq1_(
  float* reso,
  int const* ih,
  int const* ik,
  int const* il);

} // extern "C"

#endif // GUARD
