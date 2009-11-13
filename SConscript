from libtbx.utils import Sorry
from libtbx.str_utils import show_string
import libtbx.load_env
import re
import sys, os
op = os.path

Import("env_base", "env_etc")

env_etc.ccp4io_dist = libtbx.env.dist_path("ccp4io")
env_etc.ccp4io_include = libtbx.env.under_dist("ccp4io", "lib/src")

if (sys.platform == "win32"):
  env_etc.ccp4io_defines = ["-Di386"]
else:
  env_etc.ccp4io_defines = []

path_lib_src = op.join(env_etc.ccp4io_dist, "lib", "src")

build_ccp4io_adaptbx = libtbx.env.under_build("ccp4io_adaptbx")
if (not op.isdir(build_ccp4io_adaptbx)):
  os.mkdir(build_ccp4io_adaptbx)
  assert op.isdir(build_ccp4io_adaptbx)

def replace_printf(file_name):
  file_name = op.join(path_lib_src, file_name)
  result = ["#include <ccp4io_adaptbx/printf_wrappers.h>"]
  for line in open(file_name).read().splitlines():
    for key in ["printf", "fprintf"]:
      matches = list(re.finditer(
        pattern="[^A-Za-z0-9_]printf[^A-Za-z0-9_]", string=line))
      if (len(matches) != 0):
        for m in reversed(matches):
          s,e = m.start(), m.end()
          line = line[:s] \
               + line[s:e].replace("printf", "ccp4io_printf") \
               + line[e:]
    result.append(line)
  return "\n".join(result)

env = env_base.Clone(
  SHLINKFLAGS=env_etc.shlinkflags)
env.Append(CCFLAGS=env_etc.ccp4io_defines)
env.Append(SHCCFLAGS=env_etc.ccp4io_defines)
env_etc.include_registry.append(
    env=env,
    paths=["#", env_etc.ccp4io_include])
env.Append(LIBS=env_etc.libm)
if (env_etc.static_libraries): builder = env.StaticLibrary
else:                          builder = env.SharedLibrary
if (   op.normcase(op.dirname(env_etc.ccp4io_dist))
    != op.normcase("ccp4io")):
  env.Repository(op.dirname(env_etc.ccp4io_dist))
source = []

c_files = [
  "library_err.c",
  "library_file.c",
  "library_utils.c",
  "ccp4_array.c",
  "ccp4_parser.c",
  "ccp4_unitcell.c",
  "cvecmat.c",
  "cmtzlib.c",
]
open(op.join(build_ccp4io_adaptbx, "csymlib.c"), "w").write(
  open(op.join(path_lib_src, "csymlib.c")).read()
    .replace(
      "static int reported_syminfo = 0",
      "static int reported_syminfo = 1"))
source.append(op.join("#ccp4io_adaptbx", "csymlib.c"))

probe_file_name = op.join(path_lib_src, "cmaplib.h")
env_etc.ccp4io_has_cmaplib = op.isfile(probe_file_name)
if (env_etc.ccp4io_has_cmaplib):
  c_files.extend([
    "cmap_accessor.c",
    "cmap_close.c",
    "cmap_data.c",
    "cmap_header.c",
    "cmap_labels.c",
    "cmap_open.c",
    "cmap_skew.c",
    "cmap_stats.c",
    "cmap_symop.c",
])

need_f_c = libtbx.env.has_module("solve_resolve")
if (need_f_c):
  for probe_file_name in [
        "lib/src/ccp4_fortran.h",
        "lib/src/mmdb/mmdb_rwbrook.h"]:
    probe_file_name = op.join(env_etc.ccp4io_dist, probe_file_name)
    if (not op.isfile(probe_file_name)):
      raise Sorry("""\
Required source file not found: %s
  Please update the ccp4io sources or re-run libtbx/configure.py
  without requesting solve_resolve.""" % show_string(probe_file_name))
  #
  c_files.extend("""\
mmdb/bfgs_min.cpp
mmdb/file_.cpp
mmdb/hybrid_36.cpp
mmdb/linalg_.cpp
mmdb/machine_.cpp
mmdb/math_.cpp
mmdb/mattype_.cpp
mmdb/mmdb_align.cpp
mmdb/mmdb_atom.cpp
mmdb/mmdb_bondmngr.cpp
mmdb/mmdb_chain.cpp
mmdb/mmdb_cifdefs.cpp
mmdb/mmdb_coormngr.cpp
mmdb/mmdb_cryst.cpp
mmdb/mmdb_ficif.cpp
mmdb/mmdb_file.cpp
mmdb/mmdb_graph.cpp
mmdb/mmdb_manager.cpp
mmdb/mmdb_mask.cpp
mmdb/mmdb_mmcif.cpp
mmdb/mmdb_model.cpp
mmdb/mmdb_rwbrook.cpp
mmdb/mmdb_sbase.cpp
mmdb/mmdb_sbase0.cpp
mmdb/mmdb_selmngr.cpp
mmdb/mmdb_symop.cpp
mmdb/mmdb_tables.cpp
mmdb/mmdb_title.cpp
mmdb/mmdb_uddata.cpp
mmdb/mmdb_utils.cpp
mmdb/mmdb_xml.cpp
mmdb/random_n.cpp
mmdb/stream_.cpp
""".splitlines())

prefix = "#"+op.join(op.basename(env_etc.ccp4io_dist), "lib", "src")
for file_name in c_files:
  source.append(op.join(prefix, file_name))

if (need_f_c):
  source.append(op.join("#ccp4io_adaptbx", "fortran_call_stubs.c"))
  for file_name in """\
ccp4_diskio_f.c
ccp4_general.c
ccp4_general_f.c
ccp4_parser_f.c
ccp4_program.c
ccp4_unitcell_f.c
cmaplib_f.c
cmtzlib_f.c
csymlib_f.c
library_f.c
""".splitlines():
    open(op.join(build_ccp4io_adaptbx, file_name), "w").write(
      replace_printf(file_name=file_name))
    source.append(op.join("#ccp4io_adaptbx", file_name))
  source.append(op.join("#ccp4io_adaptbx", "printf_wrappers.c"))

builder(target='#lib/ccp4io', source=source)
env_etc.ccp4io_lib = "ccp4io"
