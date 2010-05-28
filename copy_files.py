import sys, os
op = os.path

def run(args):
  assert len(args) == 1
  source_root = args[0]
  relative_paths = """\
lib/data/symop.lib
lib/src/binsort.h
lib/src/binsortint.c
lib/src/ccp4_array.c
lib/src/ccp4_array.h
lib/src/ccp4_diskio_f.c
lib/src/ccp4_errno.h
lib/src/ccp4_file_err.h
lib/src/ccp4_fortran.h
lib/src/ccp4_general.c
lib/src/ccp4_general.h
lib/src/ccp4_general_f.c
lib/src/ccp4_parser.c
lib/src/ccp4_parser.h
lib/src/ccp4_parser_f.c
lib/src/ccp4_program.c
lib/src/ccp4_program.h
lib/src/ccp4_spg.h
lib/src/ccp4_sysdep.h
lib/src/ccp4_types.h
lib/src/ccp4_unitcell.c
lib/src/ccp4_unitcell.h
lib/src/ccp4_unitcell_f.c
lib/src/ccp4_utils.h
lib/src/ccp4_vars.h
lib/src/cmap_accessor.c
lib/src/cmap_close.c
lib/src/cmap_data.c
lib/src/cmap_data.h
lib/src/cmap_errno.h
lib/src/cmap_header.c
lib/src/cmap_header.h
lib/src/cmap_labels.c
lib/src/cmap_labels.h
lib/src/cmap_open.c
lib/src/cmap_skew.c
lib/src/cmap_skew.h
lib/src/cmap_stats.c
lib/src/cmap_stats.h
lib/src/cmap_symop.c
lib/src/cmaplib.h
lib/src/cmaplib_f.c
lib/src/cmaplib_f.h
lib/src/cmtzlib.c
lib/src/cmtzlib.h
lib/src/cmtzlib_f.c
lib/src/csymlib.c
lib/src/csymlib.h
lib/src/csymlib_f.c
lib/src/cvecmat.c
lib/src/cvecmat.h
lib/src/fftlib.f
lib/src/library_err.c
lib/src/library_f.c
lib/src/library_f.h
lib/src/library_file.c
lib/src/library_file.h
lib/src/library_utils.c
lib/src/mtzdata.h
lib/src/overview.h
lib/src/pack_c.c
lib/src/pack_c.h
""".splitlines()
  for path in relative_paths:
    print path
    dir = op.split(path)[0]
    if (dir != "" and not op.isdir(dir)):
      os.makedirs(dir)
    open(path, "wb").write(open(op.join(source_root, path), "rb").read())

if (__name__ == "__main__"):
  run(args=sys.argv[1:])
