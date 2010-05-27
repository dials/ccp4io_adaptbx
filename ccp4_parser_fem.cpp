#include <fem.hpp> // Fortran EMulation library of fable module

#include "ccp4_parser_fem.hpp"
#include "ccp4_calls_extern_c.hpp"

namespace ccp4_parser_fem {

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

} // namespace ccp4_parser_fem
