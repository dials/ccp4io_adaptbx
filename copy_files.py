from __future__ import division
import sys, os
op = os.path

def run(args):
  assert len(args) == 1
  source_root = args[0]
  relative_paths = """\
lib/libccp4/data/syminfo.lib
lib/libccp4/data/symop.lib
lib/libccp4/config.h.in
lib/libccp4/ccp4/ccp4_array.c
lib/libccp4/ccp4/ccp4_array.h
lib/libccp4/fortran/ccp4_diskio_f.c
lib/libccp4/ccp4/ccp4_errno.h
lib/libccp4/ccp4/ccp4_file_err.h
lib/libccp4/ccp4/ccp4_fortran.h
lib/libccp4/ccp4/ccp4_general.c
lib/libccp4/ccp4/ccp4_general.h
lib/libccp4/fortran/ccp4_general_f.c
lib/libccp4/ccp4/ccp4_parser.c
lib/libccp4/ccp4/ccp4_parser.h
lib/libccp4/fortran/ccp4_parser_f.c
lib/libccp4/ccp4/ccp4_program.c
lib/libccp4/ccp4/ccp4_program.h
lib/libccp4/ccp4/ccp4_spg.h
lib/libccp4/ccp4/ccp4_sysdep.h
lib/libccp4/ccp4/ccp4_types.h
lib/libccp4/ccp4/ccp4_unitcell.c
lib/libccp4/ccp4/ccp4_unitcell.h
lib/libccp4/fortran/ccp4_unitcell_f.c
lib/libccp4/ccp4/ccp4_utils.h
lib/libccp4/ccp4/ccp4_vars.h
lib/libccp4/ccp4/cmap_accessor.c
lib/libccp4/ccp4/cmap_close.c
lib/libccp4/ccp4/cmap_data.c
lib/libccp4/ccp4/cmap_data.h
lib/libccp4/ccp4/cmap_errno.h
lib/libccp4/ccp4/cmap_header.c
lib/libccp4/ccp4/cmap_header.h
lib/libccp4/ccp4/cmap_labels.c
lib/libccp4/ccp4/cmap_labels.h
lib/libccp4/ccp4/cmap_open.c
lib/libccp4/ccp4/cmap_skew.c
lib/libccp4/ccp4/cmap_skew.h
lib/libccp4/ccp4/cmap_stats.c
lib/libccp4/ccp4/cmap_stats.h
lib/libccp4/ccp4/cmap_symop.c
lib/libccp4/ccp4/cmaplib.h
lib/libccp4/fortran/cmaplib_f.c
lib/libccp4/ccp4/cmaplib_f.h
lib/libccp4/ccp4/cmtzlib.c
lib/libccp4/ccp4/cmtzlib.h
lib/libccp4/fortran/cmtzlib_f.c
lib/libccp4/ccp4/csymlib.c
lib/libccp4/ccp4/csymlib.h
lib/libccp4/fortran/csymlib_f.c
lib/libccp4/ccp4/cvecmat.c
lib/libccp4/ccp4/cvecmat.h
lib/libccp4/fortran/fftlib.f
lib/libccp4/ccp4/library_err.c
lib/libccp4/fortran/library_f.c
lib/libccp4/ccp4/library_file.c
lib/libccp4/ccp4/library_file.h
lib/libccp4/ccp4/library_utils.c
lib/libccp4/ccp4/mtzdata.h
lib/libccp4/ccp4/overview.h
lib/libccp4/ccp4/pack_c.c
lib/libccp4/ccp4/pack_c.h
lib/mmdb/mmdb/bfgs_min.cpp
lib/mmdb/mmdb/bfgs_min.h
lib/mmdb/mmdb/file_.cpp
lib/mmdb/mmdb/file_.h
lib/mmdb/mmdb/hybrid_36.cpp
lib/mmdb/mmdb/hybrid_36.h
lib/mmdb/mmdb/linalg_.cpp
lib/mmdb/mmdb/linalg_.h
lib/mmdb/mmdb/machine_.cpp
lib/mmdb/mmdb/machine_.h
lib/mmdb/mmdb/math_.cpp
lib/mmdb/mmdb/math_.h
lib/mmdb/mmdb/mattype_.cpp
lib/mmdb/mmdb/mattype_.h
lib/mmdb/mmdb/mmdb_align.cpp
lib/mmdb/mmdb/mmdb_align.h
lib/mmdb/mmdb/mmdb_atom.cpp
lib/mmdb/mmdb/mmdb_atom.h
lib/mmdb/mmdb/mmdb_bondmngr.cpp
lib/mmdb/mmdb/mmdb_bondmngr.h
lib/mmdb/mmdb/mmdb_chain.cpp
lib/mmdb/mmdb/mmdb_chain.h
lib/mmdb/mmdb/mmdb_cifdefs.cpp
lib/mmdb/mmdb/mmdb_cifdefs.h
lib/mmdb/mmdb/mmdb_coormngr.cpp
lib/mmdb/mmdb/mmdb_coormngr.h
lib/mmdb/mmdb/mmdb_cryst.cpp
lib/mmdb/mmdb/mmdb_cryst.h
lib/mmdb/mmdb/mmdb_defs.h
lib/mmdb/mmdb/mmdb_ficif.cpp
lib/mmdb/mmdb/mmdb_ficif.h
lib/mmdb/mmdb/mmdb_file.cpp
lib/mmdb/mmdb/mmdb_file.h
lib/mmdb/mmdb/mmdb_graph.cpp
lib/mmdb/mmdb/mmdb_graph.h
lib/mmdb/mmdb/mmdb_manager.cpp
lib/mmdb/mmdb/mmdb_manager.h
lib/mmdb/mmdb/mmdb_mask.cpp
lib/mmdb/mmdb/mmdb_mask.h
lib/mmdb/mmdb/mmdb_mmcif.cpp
lib/mmdb/mmdb/mmdb_mmcif.h
lib/mmdb/mmdb/mmdb_model.cpp
lib/mmdb/mmdb/mmdb_model.h
lib/mmdb/mmdb/mmdb_rwbrook.cpp
lib/mmdb/mmdb/mmdb_rwbrook.h
lib/mmdb/mmdb/mmdb_sbase.cpp
lib/mmdb/mmdb/mmdb_sbase.h
lib/mmdb/mmdb/mmdb_sbase0.cpp
lib/mmdb/mmdb/mmdb_sbase0.h
lib/mmdb/mmdb/mmdb_selmngr.cpp
lib/mmdb/mmdb/mmdb_selmngr.h
lib/mmdb/mmdb/mmdb_symop.cpp
lib/mmdb/mmdb/mmdb_symop.h
lib/mmdb/mmdb/mmdb_tables.cpp
lib/mmdb/mmdb/mmdb_tables.h
lib/mmdb/mmdb/mmdb_title.cpp
lib/mmdb/mmdb/mmdb_title.h
lib/mmdb/mmdb/mmdb_uddata.cpp
lib/mmdb/mmdb/mmdb_uddata.h
lib/mmdb/mmdb/mmdb_utils.cpp
lib/mmdb/mmdb/mmdb_utils.h
lib/mmdb/mmdb/mmdb_xml.cpp
lib/mmdb/mmdb/mmdb_xml.h
lib/mmdb/mmdb/random_n.cpp
lib/mmdb/mmdb/random_n.h
lib/mmdb/mmdb/stream_.cpp
lib/mmdb/mmdb/stream_.h
lib/ssm/ssm_defs.h
lib/ssm/ssm_csia.cpp
lib/ssm/ssm_csia.h
lib/ssm/ssm_graph.cpp
lib/ssm/ssm_graph.h
lib/ssm/ssm_vxedge.cpp
lib/ssm/ssm_vxedge.h
lib/ssm/ssm_align.cpp
lib/ssm/ssm_align.h
lib/ssm/ssm_superpose.cpp
lib/ssm/ssm_superpose.h
""".splitlines()
  n_makedirs = 0
  n_copied = 0
  n_updated = 0
  n_already_up_to_date = 0
  for path in relative_paths:
    dir = op.split(path)[0]
    if (dir != "" and not op.isdir(dir)):
      os.makedirs(dir)
      n_makedirs += 1
    source = open(op.join(source_root, path), "rb").read() \
      .replace(
        "#undef PACKAGE_ROOT",
        "#define PACKAGE_ROOT NULL")
    tpath = path
    if (tpath.endswith(".in")):
        tpath = tpath[:-3]
    if (not op.isfile(tpath)):
      n_copied += 1
    else:
      target = open(tpath, "rb").read()
      if (target == source):
        n_already_up_to_date += 1
        source = None
      else:
        n_updated += 1
    if (source is not None):
      open(tpath, "wb").write(source)
  print "Directories created:", n_makedirs
  print "Files copied:", n_copied
  print "Files updated:", n_updated
  print "Files already up-to-date:", n_already_up_to_date
  print "Done."

if (__name__ == "__main__"):
  run(args=sys.argv[1:])
