import boost.python
ext = boost.python.import_ext("ccp4io_adaptbx_ext")
from ccp4io_adaptbx_ext import *

import libtbx.load_env
import operator
import os

os.putenv("SYMINFO", libtbx.env.under_dist("ccp4io", "lib/data/syminfo.lib"))

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
  "SSM matching with iotbx.pdb.hierarchy objects"

  def __init__(
    self,
    moving,
    reference,
    precision = ssm.P_Normal,
    connectivity = ssm.C_Flexible
    ):

    self.chains = []
    self.managers = []
    self.handles = []

    for chain in [ moving, reference ]:
      manager = to_mmdb( root = chain )
      handle = manager.NewSelection()
      manager.Select(
        selHnd = handle,
        selType = mmdb.STYPE_ATOM,
        cid = "*",
        selKey = mmdb.SKEY_NEW
        )

      if manager.GetSelLength( selHnd = handle ) <= 0:
        raise RuntimeError, (
          "Empty atom selection for structure %s" % ( len( self.managers ) + 1 )
          )

      self.chains.append( chain )
      self.managers.append( manager )
      self.handles.append( handle )

    assert len( self.chains ) == 2
    assert len( self.managers ) == 2
    assert len(self.handles ) == 2

    self.ssm = ssm.SSMAlign()
    rc = self.ssm.Align(
      manager1 = self.managers[0],
      manager2 = self.managers[1],
      precision = precision,
      connectivity = connectivity,
      selHnd1 = self.handles[0],
      selHnd2 = self.handles[1],
      )
    #self.qvalues = self.ssm.GetQvalues()
    #self.nmatches= len(self.qvalues)

    if rc != ssm.RC_Ok:
      raise RuntimeError, ssm.GetErrorDescription( rc = rc )


  def GetQvalues(self):
      return self.ssm.GetQvalues()


  def AlignSelectedMatch(self, nselected):
    if nselected >= self.nmatches:
        print "Not that many matches available"
        return

    rc = self.ssm.AlignSelectedMatch(
      manager1 = self.managers[0],
      manager2 = self.managers[1],
      precision = ssm.P_Normal,
      connectivity = ssm.C_Flexible,
      selHnd1 = self.handles[0],
      selHnd2 = self.handles[1],
      nselected = nselected
      )
    if rc != ssm.RC_Ok:
      raise RuntimeError, ssm.GetErrorDescription( rc = rc )


  def get_matrix(self):

    return self.ssm.t_matrix
      
      
class SSMAlignment(object):
  "SSM alignment from SSM match"
  
  def __init__(self, match, indexer):
      
    align = ssm.XAlignText()
    align.XAlign(
      manager1 = match.managers[0],
      manager2 = match.managers[1],
      ssm_align = match.ssm
      )
    indexer1 = indexer( chain = match.chains[0] )
    indexer2 = indexer( chain = match.chains[1] )
    self.pairs = []
    self.stats = []
    
    for ( ( f, s ), a ) in align.get_blocks():
      def get(rgi, indexer):
        if (rgi is None):
            return None
        
        identifier = ( rgi.chain_id, rgi.resseq, rgi.inscode )
        assert identifier in indexer
        return indexer[ identifier ]
      
      self.pairs.append( ( get( f, indexer1 ), get( s, indexer2 ) ) )
      self.stats.append( a )
      
      
  def residue_groups(cls, match):
      
    indexer = lambda chain: dict(
      [ ( ( chain.id, rg.resseq_as_int(), rg.icode ), rg )
        for rg in chain.residue_groups() ]
      )
      
    return cls( match = match, indexer = indexer )
  
  residue_groups = classmethod( residue_groups )
