import libtbx.config
import sys, os

Import("env_base","env_etc")

env_etc.ccp4io_dist = env_etc.libtbx_env.dist_path("ccp4io")
libtbx_config_path = os.path.join(env_etc.ccp4io_dist, "libtbx_config")
if (os.path.isfile(libtbx_config_path)):
  config = libtbx.config.read_libtbx_config(path=libtbx_config_path)
  redirection = config.get("redirection", None)
  if (redirection is not None):
    redirection = os.path.expandvars(redirection)
    if (os.path.isabs(redirection)):
      env_etc.ccp4io_dist = os.path.normpath(redirection)
    else:
      env_etc.ccp4io_dist = env_etc.norm_join(
        env_etc.libtbx_env.dist_path("ccp4io"), redirection)
if (not os.path.isdir(env_etc.ccp4io_dist)):
  print "Fatal error: not a directory: %s" % env_etc.ccp4io_dist
  Exit(1)
Repository(os.path.dirname(env_etc.ccp4io_dist))

env_etc.ccp4io_include = env_etc.norm_join(env_etc.ccp4io_dist, "lib", "src")

if (sys.platform == "win32"):
  env_etc.ccp4io_defines = ['-D_MVS', '-Di386']
else:
  env_etc.ccp4io_defines = []

ccflags = env_etc.ccflags_base[:]
ccflags.extend(env_etc.ccp4io_defines)

env = env_base.Copy(
  CCFLAGS=ccflags,
  SHCCFLAGS=ccflags,
)
env.Append(LIBS=env_etc.libm)
if (env_etc.static_libraries): builder = env.StaticLibrary
else:                          builder = env.SharedLibrary
lib_src = env_etc.norm_join(
  os.path.basename(env_etc.ccp4io_dist), "lib", "src")
builder(target='#lib/cmtz',
  source = ["#" + env_etc.norm_join(lib_src, file_name) for file_name in [
    "library_err.c",
    "library_file.c",
    "library_utils.c",
    "ccp4_array.c",
    "ccp4_parser.c",
    "ccp4_unitcell.c",
    "cvecmat.c",
    "cmtzlib.c",
    "csymlib.c",
    ]])
