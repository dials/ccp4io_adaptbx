#include <boost/python.hpp>
#include <mmdb_manager.h>
#include <ssm_align.h>

namespace ccp4io_adaptbx { namespace boost_python {

using namespace ssm;

class PySSMAlign : public Align
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

    boost::python::list get_q_values() const
    {
        boost::python::list l;
        realtype* pqvalues = GetQvalues();

        for ( int i = 0; i < GetNMatches(); ++i )
        {
            l.append( pqvalues[ i ] );
        }

        return l;
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
        chain_id(
          chain_id_[0] == '\0' ? " " : boost::python::str( chain_id_, 1 )
          ),
        resname( boost::python::str( resname_, 3 ) ),
        inscode(
          inscode_[0] == '\0' ? " " : boost::python::str( inscode_, 1 )
          ),
        sse_type( sse_type_ ),
        resseq( resseq_ )
    {}

    ~ResidueData() {}
};

class PyXAlignText : public XAlignText
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

      align(
        cssm.G1, Calpha1, cssm.Ca1, nat1,
        cssm.G2, Calpha2, cssm.Ca2, nat2,
        cssm.dist1, length
        );
    }

    boost::python::list get_blocks()
    {
      boost::python::list l;

      PXTAlign XTA = GetTextRows();

      for( int i = 0; i < length; ++i)
      {
        boost::python::tuple equivs;
        boost::python::tuple info;

        switch ( XTA[i].alignKey )
        {
        case 0: // KEY_ALIGNED
          info = boost::python::make_tuple(
            XTA[i].dist,
            XTA[i].loopNo,
            XTA[i].simindex
            );
            // no break!

        case 1: // KEY_NOT_ALIGNED
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
  using namespace ssm;

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

  enum_<SUPERPOSITION_RESULT>("SUPERPOSITION_RESULT")
    .value("Ok", SPOSE_Ok)
    .value("BadData", SPOSE_BadData)
    .value("NoCalphas1", SPOSE_NoCalphas1)
    .value("NoCalphas2", SPOSE_NoCalphas2)
    .value("RemoteStruct", SPOSE_RemoteStruct)
    .value("SVDFail", SPOSE_SVDFail);
  enum_<RETURN_CODE>("RETURN_CODE")
    .value("Ok", RC_Ok)
    .value("NoHits", RC_NoHits)
    .value("NoSuperposition", RC_NoSuperposition)
    .value("NoGraph", RC_NoGraph)
    .value("NoVertices", RC_NoVertices)
    .value("NoGraph2", RC_NoGraph2)
    .value("NoVertices2", RC_NoVertices2)
    .value("TooFewMatches", RC_TooFewMatches);
  enum_<PRECISION>("PRECISION")
    .value("Highest", PREC_Highest)
    .value("High", PREC_High)
    .value("Normal", PREC_Normal)
    .value("Low", PREC_Low)
    .value("Lowest", PREC_Lowest);
  enum_<CONNECTIVITY>("CONNECTIVITY")
    .value("Flexible", CONNECT_Flexible)
    .value("None_", CONNECT_None)
    .value("Strict", CONNECT_Strict);
  enum_<VERTEX_TYPE>("VERTEX_TYPE")
    .value("UNKNOWN", V_UNKNOWN)
    .value("HELIX", V_HELIX)
    .value("STRAND", V_STRAND);

  InitGraph();
  class_< PySSMAlign >( "SSMAlign", init<>() )
    .def(
      "Align",
      &PySSMAlign::align,
      ( arg( "manager1" ), arg( "manager2" ), arg( "precision" ),
        arg( "connectivity" ), arg( "selHnd1" ), arg( "selHnd2" ) )
      )
    .def( "GetQvalues", &PySSMAlign::get_q_values )
    .def(
      "AlignSelectedMatch",
      &PySSMAlign::AlignSelectedMatch,
      ( arg( "manager1" ), arg( "manager2" ), arg( "precision" ),
        arg( "connectivity" ), arg( "selHnd1" ), arg( "selHnd2" ), arg( "nselected" ) )
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
