import boost.python
ext = boost.python.import_ext("ccp4io_adaptbx_ext")
from ccp4io_adaptbx_ext import *

import operator

def to_mmdb(root, flags = []):
  "Converts iotbx.pdb.hierarchy object to an MMDB Manager"

  manager = mmdb.Manager()

  if flags:
    manager.SetFlag( reduce( operator.or_, flags ) )

  for atom in root.atoms():
    rc = manager.PutPDBString( atom.format_atom_record() )

    if 0 < rc:
      raise RuntimeError, mmdb.GetErrorDescription( rc )

  return manager


ssm.ERROR_DESCRIPTION_FOR = {
  ssm.RC_noHits: "secondary structure does not match",
  ssm.RC_noSPSN: "structures are too remote",
  ssm.RC_noGraph: "can't make graph for first structure",
  ssm.RC_noVertices: "empty graph for first structure",
  ssm.RC_noGraph2: "can't make graph for second structure",
  ssm.RC_noVertices2: "empty graph for second structure",
  }

ssm.GetErrorDescription = lambda rc: (
  ssm.ERROR_DESCRIPTION_FOR.get( rc, "undocumented return code" )
  )

class SecondaryStructureMatching(object):
  "SSM alignment with iotbx.pdb.hierarchy objects"

  def __init__(
    self,
    moving,
    reference,
    precision = ssm.P_Normal,
    connectivity = ssm.C_Flexible
    ):

    self.managers = []
    handles = []

    for ( i, r ) in enumerate( [ moving, reference ] ):
      manager = to_mmdb( root = r )
      handle = manager.NewSelection()
      manager.Select(
        selHnd = handle,
        selType = mmdb.STYPE_ATOM,
        cid = "*",  
        selKey = mmdb.SKEY_NEW
        )

      if manager.GetSelLength( selHnd = handle ) <= 0:
        raise RuntimeError, (
          "Empty atom selection for structure %s" % len( self.managers )
          )
      
      self.managers.append( manager )
      handles.append( handle )

    assert len( self.managers ) == 2
    assert len( handles ) == 2
    
    self.ssm = ssm.SSMAlign()
    rc = self.ssm.Align(
      manager1 = self.managers[0],
      manager2 = self.managers[1],
      precision = precision,
      connectivity = connectivity,
      selHnd1 = handles[0],
      selHnd2 = handles[1],
      )

    if rc != ssm.RC_Ok:
      raise RuntimeError, ssm.GetErrorDescription( rc = rc )

    self.blocks = None


  def get_matrix(self):

    return self.ssm.t_matrix


  def get_alignment(self):

    if not self.blocks:
      self.calculate_alignment_blocks()

    alignment = []

    for ( ( f, s ), a ) in self.blocks:
      alignment.append(
        (
          ( f.chain_id, f.resseq, f.inscode ) if f else None,
          ( s.chain_id, s.resseq, s.inscode ) if s else None,
          )
        )

    return alignment

  
  def calculate_alignment_blocks(self):

    align = ssm.XAlignText()
    align.XAlign(
      manager1 = self.managers[0],
      manager2 = self.managers[1], 
      ssm_align = self.ssm
      )
    self.blocks = align.get_blocks()
