import libtbx.load_env
import sys, os

Import("env_base", "env_etc")

env_etc.ccp4io_dist = libtbx.env.dist_path("ccp4io")
env_etc.ccp4io_include = libtbx.env.under_dist("ccp4io", "lib/src")

if (sys.platform == "win32"):
  env_etc.ccp4io_defines = ["-Di386"]
else:
  env_etc.ccp4io_defines = []

env = env_base.Clone(
  SHLINKFLAGS=env_etc.shlinkflags)
env.Append(SHCCFLAGS=env_etc.ccp4io_defines)
env_etc.include_registry.append(
    env=env,
    paths=[env_etc.ccp4io_include])
env.Append(LIBS=env_etc.libm)
if (env_etc.static_libraries): builder = env.StaticLibrary
else:                          builder = env.SharedLibrary
if (   os.path.normcase(os.path.dirname(env_etc.ccp4io_dist))
    != os.path.normcase("ccp4io")):
  env.Repository(os.path.dirname(env_etc.ccp4io_dist))
c_files = [
  "library_err.c",
  "library_file.c",
  "library_utils.c",
  "ccp4_array.c",
  "ccp4_parser.c",
  "ccp4_unitcell.c",
  "cvecmat.c",
  "cmtzlib.c",
  "csymlib.c",
]
probe_file_name = os.path.join(env_etc.ccp4io_dist,
  "lib", "src", "cmaplib.h")
env_etc.ccp4io_has_cmaplib = os.path.isfile(probe_file_name)
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
probe_file_name = os.path.join(env_etc.ccp4io_dist,
  "lib", "src", "ccp4_fortran.h")
env_etc.ccp4io_has_f_c = os.path.isfile(probe_file_name)
if (env_etc.ccp4io_has_f_c):
  c_files.extend([
    "ccp4_diskio_f.c",
    "ccp4_general.c",
    "ccp4_general_f.c",
    "ccp4_parser_f.c",
    "ccp4_program.c",
    "ccp4_unitcell_f.c",
    "cmaplib_f.c",
    "cmtzlib_f.c",
    "csymlib_f.c",
    "library_f.c"])
prefix = "#"+os.path.join(os.path.basename(env_etc.ccp4io_dist), "lib", "src")
source = [os.path.join(prefix, file_name) for file_name in c_files]
if (env_etc.ccp4io_has_f_c):
  source.append(os.path.join("#ccp4io_adaptbx", "fortran_call_stubs.c"))
builder(target='#lib/ccp4io', source=source)
env_etc.ccp4io_lib = "ccp4io"
