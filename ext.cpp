#include <boost/python.hpp>
#include <mmdb_manager.h>

namespace ccp4io_adaptbx { namespace boost_python {

void
init_module()
{
  using namespace boost::python;
  InitMatType();
  class_< CMMDBManager >( "MMDBManager", init<>() );
}

}}  // namespace ssmtbx::boost_python

BOOST_PYTHON_MODULE( ccp4io_adaptbx_ext )
{
  ccp4io_adaptbx::boost_python::init_module();
}
