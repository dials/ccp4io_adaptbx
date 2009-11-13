#include <boost/python.hpp>

#include <resolve/aaa_resolve.hpp>
#include <resolve/ccp4_calls.hpp>
#include <resolve/fftlib.hpp>
#include <resolve/low_level_utils.hpp>

#include <iotbx/pdb/input.h>
#include <scitbx/array_family/versa.h>
#include <scitbx/array_family/shared.h>
#include <scitbx/array_family/accessors/c_grid.h>
#include <boost_adaptbx/python_file_stream.h>
#include <boost/shared_ptr.hpp>
#include <boost/timer.hpp>
#include <vector>

namespace resolve { namespace ext {

  struct exit_info_wrappers
  {
    typedef exit_info wt; // shortcut for "wrapped type"

    static void
    wrap()
    {
      using namespace boost::python;
      class_<wt>("exit_info", no_init)
        .def_readonly("source_file", &wt::source_file)
        .def_readonly("source_line", &wt::source_line)
        .def_readonly("status", &wt::status)
      ;
    }
  };

  struct cmn_data_wrappers
  {
    typedef cmn_data wt; // shortcut for "wrapped type"

    static void
    wrap()
    {
      using namespace boost::python;
      class_<wt, boost::shared_ptr<cmn_data> >("cmn_data", no_init)
        .def_readonly("exit_info", &wt::exit_info)
        .def_readonly("nsym", &wt::nsym) // an abritry example
      ;
    }
  };

  boost::shared_ptr<cmn_data>
  call_with_streams(
    const char* inputs,
    std::ostream & err_stream,
    std::ostream & out_stream,
    int isizeit,
    int n_crystal_map_max)
  {
    RESOLVE_ASSERT(isizeit > 0);
    RESOLVE_ASSERT(n_crystal_map_max > 0);
    boost::shared_ptr<cmn_data> cmn(new
      cmn_data(isizeit, n_crystal_map_max, err_stream, out_stream));
    std::istringstream inp_stream(inputs == 0 ? "" : inputs);
    try {
      aaa_resolve(*cmn, inp_stream);
    }
    catch (exit_info const& ei) {
      cmn->exit_info = ei;
      out_stream
        << "resolve exit_info:\n"
        << "  source_file: " << ei.source_file << '\n'
        << "  source_line: " << ei.source_line << '\n'
        << "  status: " << ei.status << std::endl;
      if (ei.status == 0) {
        out_stream
          << "EndOfResolve" << std::endl;
      }
      return cmn;
    }
    throw std::runtime_error("resolve exit_info undefined.");
  }

  using boost_adaptbx::file_conversion::python_file_buffer;

  boost::shared_ptr<cmn_data>
  call_with_python_file_objects(
    const char* inputs,
    python_file_buffer const& err_file_obj,
    python_file_buffer const& out_file_obj,
    int isizeit,
    int n_crystal_map_max)
  {
    typedef boost_adaptbx::file_conversion::ostream py_ostream;
    py_ostream err_stream(&err_file_obj);
    py_ostream out_stream(&out_file_obj);
    boost::shared_ptr<cmn_data> result = call_with_streams(
      inputs, err_stream, out_stream, isizeit, n_crystal_map_max);
    err_stream.flush();
    out_stream.flush();
    return result;
  }

  boost::shared_ptr<cmn_data>
  call_using_std_cerr_and_std_cout(
    const char* inputs,
    int isizeit,
    int n_crystal_map_max)
  {
    return call_with_streams(
      inputs, std::cerr, std::cout, isizeit, n_crystal_map_max);
  }

  unsigned long
  farray_float_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      FArray1D_float data(array_size);
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  farray_float_initialized_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      FArray1D_float data(array_size, 0.f);
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  af_shared_float_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      af::shared<float> data(array_size, af::init_functor_null<float>());
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  af_shared_float_initialized_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      af::shared<float> data(array_size);
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  std_vector_float_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      std::vector<float> data(array_size);
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  farray_fstring4_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      FArray1D_Fstring data(array_size, Fstring(4));
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  unsigned long
  farray_str4_experiment(
    int n_iterations,
    int array_size)
  {
    unsigned long result = 0;
    for(int i=0;i<n_iterations;i++) {
      FArray1D_str4 data(array_size);
      result += reinterpret_cast<unsigned long>(&data[0]) & 0x1ul;
    }
    return result;
  }

  float
  use_af_ref(
    af::const_ref<float> const & data,
    int n_iterations)
  {
    float result = 0;
    int n_data = static_cast<int>(data.size());
    for(int i=0;i<n_iterations;i++) {
      for(int j=0;j<n_data;j++) {
        result += data[j];
      }
      for(int j=0;j<n_data;j++) {
        result -= data[j];
      }
    }
    return result + 1.0f;
  }

  float
  use_farray1a(
    FArray1A_float data,
    int n_iterations)
  {
    float result = 0;
    int n_data = static_cast<int>(data.size());
    for(int i=0;i<n_iterations;i++) {
      for(int j=0;j<n_data;j++) {
        result += data[j];
      }
      for(int j=0;j<n_data;j++) {
        result -= data[j];
      }
    }
    return result + 2.0f;
  }

  float
  use_af_ref_or_farray1a(
    int which,
    af::const_ref<float> const & data,
    int n_iterations)
  {
    if (which == 0) {
      return use_af_ref(data, n_iterations);
    }
    return use_farray1a(FArray1A_float(data[0], data.size()), n_iterations);
  }

  int
  sizeof_af_ref_or_farray1a(
    int which)
  {
    if (which == 0) return sizeof(af::const_ref<float>);
    return sizeof(FArray1A_float);
  }

  double
  pdb_read_experiment(
    const char* file_name)
  {
    boost::timer timer;
    iotbx::pdb::input pdb_inp(file_name);
    using iotbx::pdb::hierarchy::atom_with_labels;
    af::shared<atom_with_labels> atoms = pdb_inp.atoms_with_labels();
    int n_atoms = atoms.size();
    FArray2D_float xyz_db(3, n_atoms);
    FArray2D_float occb_db(2, n_atoms);
    FArray1D_int iresd_db(n_atoms);
    FArray1D_str4 htype_db(n_atoms);
    FArray1D_str4 irestype_db(n_atoms);
    for(int i=0;i<n_atoms;i++) {
      atom_with_labels const & atom = atoms[i];
      for(int j=0;j<3;j++) {
        xyz_db(j+1,i+1) = atom.data->xyz[j];
      }
      occb_db(1,i+1) = atom.data->occ;
      occb_db(2,i+1) = atom.data->b;
      iresd_db(i+1) = atom.resseq_as_int();
      for(int j=0;j<4;j++) {
        htype_db(i+1)(j+1) = atom.data->name.elems[j];
      }
      for(int j=0;j<3;j++) {
        irestype_db(i+1)(j+1) = atom.resname.elems[j];
      }
      irestype_db(i+1)(4) = ' ';
    }
    return timer.elapsed();
  }

  void
  fftlib_cmplft(
    af::ref<float> const & xy,
    int const n,
    af::ref<int> const & d)
  {
    ASSERTBX(n > 0);
    ASSERTBX(xy.size() >= 2 * n);
    ASSERTBX(d.size() == 5);
    cmplft(xy[0], xy[1], n, d[0]);
  }

  void
  fftlib_realft(
    af::ref<float> const & xy,
    int const n,
    af::ref<int> const & d)
  {
    ASSERTBX(n > 0);
    ASSERTBX(xy.size() >= 2 * n + 2);
    ASSERTBX(d.size() == 5);
    realft(xy[0], xy[1], n, d[0]);
  }

  void
  fftlib_hermft(
    af::ref<float> const & xy,
    int const n,
    af::ref<int> const & d)
  {
    ASSERTBX(n > 0);
    ASSERTBX(xy.size() >= 2 * n);
    ASSERTBX(d.size() == 5);
    hermft(xy[0], xy[1], n, d[0]);
  }

  void
  fftlib_real_to_complex_3d_real_imag_w(
    af::ref<float> const & x,
    int const nu,
    int const nv,
    int const nw,
    bool complete)
  {
    ASSERTBX(nu > 0);
    ASSERTBX(nv > 0);
    ASSERTBX(nw > 0);
    ASSERTBX(nw % 2 == 0);
    ASSERTBX(x.size() >= nu*nv*(nw+2)); // memory required also if not complete
    int nuv = nu*nv;
    int nuvw2 = (complete ? nuv*(nw+2) : nuv*nw);
    // transform along w
    int5d d;
    d(1)=nuvw2;
    d(2)=2*nuv;
    d(3)=nuvw2;
    d(4)=nuv;
    d(5)=1;
    realft(x[0],x[nuv],nw/2,d);
      // realft always does a complete transform, but
      // if !complete, the layer at nw/2 is ignored below
    // transform along v
    d(1)=nuvw2;
    d(2)=nu;
    d(3)=2*nuv;
    d(4)=nu;
    d(5)=1;
    cmplft(x[0],x[nuv],nv,d);
    // transform along u
    d(1)=nuvw2;
    d(2)=1;
    d(3)=2*nuv;
    d(4)=nuv;
    d(5)=nu;
    cmplft(x[0],x[nuv],nu,d);
  }

  void
  fftlib_complex_to_real_3d_real_imag_w(
    af::ref<float> const & x,
    int const nu,
    int const nv,
    int const nw,
    bool complete)
  {
    ASSERTBX(nu > 0);
    ASSERTBX(nv > 0);
    ASSERTBX(nw > 0);
    ASSERTBX(nw % 2 == 0);
    ASSERTBX(x.size() >= nu*nv*(nw+2)); // memory required also if not complete
    int nuv=nu*nv;
    int nuvw2 = (complete ? nuv*(nw+2) : nuv*nw);
    // transform along u
    int5d d;
    d(1)=nuvw2;
    d(2)=1;
    d(3)=2*nuv;
    d(4)=nuv;
    d(5)=nu;
    cmplft(x[0],x[nuv],nu,d);
    // transform along v
    d(1)=nuvw2;
    d(2)=nu;
    d(3)=2*nuv;
    d(4)=nu;
    d(5)=1;
    cmplft(x[0],x[nuv],nv,d);
    if (complete) {
      // copy real part of last value along w to imag part of first
      for(int v=0;v<nv;v++) {
        for(int u=0;u<nu;u++) {
          int uv1  = ((1 *nv)+v)*nu+u;
          int uvnw = ((nw*nv)+v)*nu+u;
          x[uv1] = x[uvnw];
        }
      }
    }
    // transform along w
    d(1)=nuvw2;
    d(2)=2*nuv;
    d(3)=nuvw2;
    d(4)=nuv;
    d(5)=1;
    hermft(x[0],x[nuv],nw/2,d);
  }

  void
  hermitian_conjugate_3d_real_imag_w(
    af::ref<float> const & x,
    int const nu,
    int const nv,
    int const nw)
  {
    ASSERTBX(nu > 0);
    ASSERTBX(nv > 0);
    ASSERTBX(nw > 0);
    ASSERTBX(nw % 2 == 0);
    ASSERTBX(x.size() >= nu*nv*(nw+2));
    for(int w=0;w<nw+2;w+=2) {
      for(int v=0;v<nv;v++) {
        for(int u=0;u<nu;u++) {
          int uvw_imag = (((w+1)*nv)+v)*nu+u;
          x[uvw_imag] *= -1.0f;
        }
      }
    }
  }

  void
  wrap()
  {
    using namespace boost::python;
    ccp4io_printf_mode = 0; // to suppress output
    ccp4_liberr_verbosity(0);
    exit_info_wrappers::wrap();
    cmn_data_wrappers::wrap();
    def("call", call_with_python_file_objects, (
      arg("inputs"),
      arg("err_file_obj"),
      arg("out_file_obj"),
      arg("isizeit"),
      arg("n_crystal_map_max")),
        with_custodian_and_ward_postcall<0,2>(),
        with_custodian_and_ward_postcall<0,3>());
    def("call", call_using_std_cerr_and_std_cout, (
      arg("inputs"),
      arg("isizeit"),
      arg("n_crystal_map_max")));
#define RESOLVE_LOC(experiment) \
    def(#experiment, experiment, (arg("n_iterations"), arg("array_size")));
    RESOLVE_LOC(farray_float_experiment)
    RESOLVE_LOC(farray_float_initialized_experiment)
    RESOLVE_LOC(af_shared_float_experiment)
    RESOLVE_LOC(af_shared_float_initialized_experiment)
    RESOLVE_LOC(std_vector_float_experiment)
    RESOLVE_LOC(farray_fstring4_experiment)
    RESOLVE_LOC(farray_str4_experiment)
#undef RESOLVE_LOC
    def("use_af_ref_or_farray1a", use_af_ref_or_farray1a, (
      arg("which"),
      arg("data"),
      arg("n_iterations")));
    def("sizeof_af_ref_or_farray1a", sizeof_af_ref_or_farray1a, (
      arg("which")));
    def("pdb_read_experiment", pdb_read_experiment, (
      arg("file_name")));
    def("fftlib_cmplft", fftlib_cmplft, (arg("xy"), arg("n"), arg("d")));
    def("fftlib_realft", fftlib_realft, (arg("xy"), arg("n"), arg("d")));
    def("fftlib_hermft", fftlib_hermft, (arg("xy"), arg("n"), arg("d")));
    def("fftlib_real_to_complex_3d_real_imag_w",
         fftlib_real_to_complex_3d_real_imag_w, (
      arg("x"), arg("nu"), arg("nv"), arg("nw"), arg("complete")));
    def("fftlib_complex_to_real_3d_real_imag_w",
         fftlib_complex_to_real_3d_real_imag_w, (
      arg("x"), arg("nu"), arg("nv"), arg("nw"), arg("complete")));
    def("hermitian_conjugate_3d_real_imag_w",
         hermitian_conjugate_3d_real_imag_w, (
      arg("x"), arg("nu"), arg("nv"), arg("nw")));
  }

}} // namespace resolve::ext

BOOST_PYTHON_MODULE(solve_resolve_resolve_ext)
{
  resolve::ext::wrap();
}
