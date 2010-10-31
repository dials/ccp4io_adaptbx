#include <boost/python.hpp>
#include <mmdb_manager.h>
#include <ssm_align.h>

namespace ccp4io_adaptbx { namespace boost_python {

class PySSMAlign : public CSSMAlign
{
  public:
    PySSMAlign() {}
    ~PySSMAlign() {}

    boost::python::tuple get_t_matrix() const
    {
      return boost::python::make_tuple(
        TMatrix[0][0], TMatrix[0][1], TMatrix[0][2], TMatrix[0][3],
        TMatrix[1][0], TMatrix[1][1], TMatrix[1][2], TMatrix[1][3],
        TMatrix[2][0], TMatrix[2][1], TMatrix[2][2], TMatrix[2][3]
        );
    }
};

class ResidueData
{
  public:
    realtype hydropathy;
    boost::python::str chain_id, resname, inscode;
    int sse_type, resseq;

    ResidueData(
      const realtype& hydropathy_,
      const ChainID& chain_id_,
      const ResName& resname_,
      const InsCode& inscode_,
      int sse_type_,
      int resseq_
      )
      : hydropathy( hydropathy_ ),
        chain_id( boost::python::str( chain_id_, 1 ) ),
        resname( boost::python::str( resname_, 3 ) ),
        inscode(
          inscode_[0] == '\0' ? " " : boost::python::str( inscode_, 1 )
          ),
        sse_type( sse_type_ ),
        resseq( resseq_ )
    {}

    ~ResidueData() {}
};

class PyXAlignText : public CXAlignText
{
  private:
    int length;

  public:
    PyXAlignText() : length( 0 ) {}
    ~PyXAlignText() {}

    void py_x_align(PCMMDBManager m1, PCMMDBManager m2, PySSMAlign& cssm)
    {
      PPCAtom Calpha1,Calpha2;
      int nat1,nat2,nr;

      m1->GetSelIndex ( cssm.selHndCa1,Calpha1,nat1 );
      m2->GetSelIndex ( cssm.selHndCa2,Calpha2,nat2 );

      XAlign(
        cssm.G1, Calpha1, cssm.Ca1, nat1,
        cssm.G2, Calpha2, cssm.Ca2, nat2,
        cssm.dist1, length
        );
    }

    boost::python::list get_blocks()
    {
      boost::python::list l;
      boost::python::tuple equivs;

      PSXTAlign XTA = GetTextRows();

      for( int i = 0; i < length; ++i)
      {
        boost::python::tuple info;

        switch ( XTA[i].alignKey )
        {
        case 0: // KEY_ALIGNED
          equivs = boost::python::make_tuple(
            ResidueData(
              XTA[i].hydropathy1,
              XTA[i].chID1,
              XTA[i].resName1,
              XTA[i].insCode1,
              XTA[i].sseType1,
              XTA[i].seqNum1
              ),
            ResidueData(
              XTA[i].hydropathy2,
              XTA[i].chID2,
              XTA[i].resName2,
              XTA[i].insCode2,
              XTA[i].sseType2,
              XTA[i].seqNum2
              )
            );
          info = boost::python::make_tuple(
            XTA[i].dist,
            XTA[i].loopNo,
            XTA[i].simindex
            );
          break;

        case 2: // KEY_FIRST_GAP
          equivs = boost::python::make_tuple(
            boost::python::object(),
            ResidueData(
              XTA[i].hydropathy2,
              XTA[i].chID2,
              XTA[i].resName2,
              XTA[i].insCode2,
              XTA[i].sseType2,
              XTA[i].seqNum2
              )
            );
          break;

        case 3: // KEY_SECOND_GAP
          equivs = boost::python::make_tuple(
            ResidueData(
              XTA[i].hydropathy1,
              XTA[i].chID1,
              XTA[i].resName1,
              XTA[i].insCode1,
              XTA[i].sseType1,
              XTA[i].seqNum1
              ),
            boost::python::object()
            );
          break;
        }

        l.append( boost::python::make_tuple( equivs, info ) );
      }

      return l;
    }
};

struct Manager_wrappers
{
  typedef CMMDBManager wt;

  static
  boost::python::object
  GetSymOp_wrapper(
    wt& O,
    int Nop)
  {
    cpstr s = O.GetSymOp(Nop);
    if (s == 0) return boost::python::object();
    return boost::python::str(s);
  }

  static void
  wrap()
  {
    using namespace boost::python;
    class_<wt>( "Manager", init<>() )
      .def( "SetFlag", &wt::SetFlag, ( arg( "flag" ) ) )
      .def("ReadPDBASCII",
        (int (wt::*)(cpstr, byte)) &wt::ReadPDBASCII, (
          arg( "fileName" ), arg( "gzipMode" )))
      .def( "PutPDBString", &wt::PutPDBString, ( arg( "pdbString" ) ) )
      .def( "WritePDBASCII",
        (int (wt::*)(cpstr, byte)) &wt::WritePDBASCII, (
          arg( "fileName" ), arg( "gzipMode" )))
      .def( "NewSelection", &wt::NewSelection )
      .def("Select",
        (int (wt::*)(int, int, cpstr, int)) &wt::Select, (
          arg( "selHnd" ), arg( "selType" ), arg( "cid" ), arg( "selKey")))
      .def( "GetSelLength", &wt::GetSelLength, ( arg( "selHnd" ) ) )
      .def( "isSpaceGroup", &wt::isSpaceGroup )
      .def( "GetNumberOfSymOps", &wt::GetNumberOfSymOps )
      .def( "GetSymOp", GetSymOp_wrapper, ( arg( "Nop" ) ) )
    ;
  }
};

void
init_module()
{
  using namespace boost::python;

  object package = scope();
  package.attr( "__path__" ) = "ccp4io_adaptbx";

  object mmdb_module((
    handle<>( borrowed( PyImport_AddModule( "ccp4io_adaptbx.mmdb" ) ) )
    ));
  object ssm_module((
    handle<>( borrowed( PyImport_AddModule( "ccp4io_adaptbx.ssm" ) ) )
    ));
  scope().attr( "mmdb" ) = mmdb_module;
  scope().attr( "ssm" ) = ssm_module;
  scope mmdb_scope = mmdb_module;
  mmdb_scope.attr( "F_PrintCIFWarnings" ) = MMDBF_PrintCIFWarnings;
  mmdb_scope.attr( "F_IgnoreNonCoorPDBErrors" ) = MMDBF_IgnoreNonCoorPDBErrors;
  mmdb_scope.attr( "F_IgnoreDuplSeqNum" ) = MMDBF_IgnoreDuplSeqNum;
  mmdb_scope.attr( "STYPE_ATOM" ) = STYPE_ATOM;
  mmdb_scope.attr( "SKEY_NEW" ) = SKEY_NEW;
  def( "GetErrorDescription", &GetErrorDescription );

  InitMatType();
  Manager_wrappers::wrap();

  scope ssm_scope = ssm_module;
  ssm_scope.attr( "C_Flexible" ) = CSSC_Flexible;
  ssm_scope.attr( "P_Normal" ) = SSMP_Normal;
  ssm_scope.attr( "RC_Ok" ) = SSM_Ok;
  ssm_scope.attr( "RC_noHits" ) = SSM_noHits;
  ssm_scope.attr( "RC_noSPSN" ) = SSM_noSPSN;
  ssm_scope.attr( "RC_noGraph" ) = SSM_noGraph;
  ssm_scope.attr( "RC_noVertices" ) = SSM_noVertices;
  ssm_scope.attr( "RC_noGraph2" ) = SSM_noGraph2;
  ssm_scope.attr( "RC_noVertices2" ) = SSM_noVertices2;

  InitSSGraph();
  class_< PySSMAlign >( "SSMAlign", init<>() )
    .def(
      "Align",
      &PySSMAlign::Align,
      ( arg( "manager1" ), arg( "manager2" ), arg( "precision" ),
        arg( "connectivity" ), arg( "selHnd1" ), arg( "selHnd2" ) )
      )
    .def_readonly( "rmsd", &PySSMAlign::rmsd )
    .def_readonly( "n_align", &PySSMAlign::nalgn )
    .add_property( "t_matrix", &PySSMAlign::get_t_matrix )
    ;

  class_< ResidueData >( "ResidueData", no_init )
    .def_readonly( "hydropathy", &ResidueData::hydropathy )
    .def_readonly( "chain_id", &ResidueData::chain_id )
    .def_readonly( "resname", &ResidueData::resname )
    .def_readonly( "inscode", &ResidueData::inscode )
    .def_readonly( "sse_type", &ResidueData::sse_type )
    .def_readonly( "resseq", &ResidueData::resseq )
    ;

  class_< PyXAlignText >( "XAlignText", init<>() )
    .def( "XAlign", &PyXAlignText::py_x_align,
      ( arg( "manager1" ), arg( "manager2" ), arg( "ssm_align" ) )
      )
    .def( "get_blocks", &PyXAlignText::get_blocks )
    ;
}

}}  // namespace ccp4io_adaptbx::boost_python

BOOST_PYTHON_MODULE( ccp4io_adaptbx_ext )
{
  ccp4io_adaptbx::boost_python::init_module();
}
