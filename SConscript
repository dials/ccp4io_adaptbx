import sys

Import("env_base","env_etc")

env_etc.ccp4io_dist = env_etc.libtbx_env.dist_path("ccp4io")
env_etc.ccp4io_include = env_etc.norm_join(env_etc.ccp4io_dist, "lib", "src")

if (sys.platform == "win32"):
  env_etc.ccp4io_defines = ['-D_MVS', '-Di386']
else:
  env_etc.ccp4io_defines = []

myccflags_base = env_etc.ccflags_base[:]
myccflags_base.extend(env_etc.ccp4io_defines)
mycxxflags_base = env_etc.cxxflags_base[:]
mycxxflags_base.extend(env_etc.ccp4io_defines)

env = env_base.Copy(
  CXXFLAGS=mycxxflags_base,
  CCFLAGS=myccflags_base,
)
env.Append(LIBS=env_etc.libm)
if (env_etc.static_libraries): builder = env.StaticLibrary
else:                          builder = env.SharedLibrary
builder(target='#libtbx/cmtz',
  source = ["../ccp4io/lib/src/library_err.c",
            "../ccp4io/lib/src/library_file.c",
            "../ccp4io/lib/src/library_utils.c",
            "../ccp4io/lib/src/ccp4_array.c",
            "../ccp4io/lib/src/ccp4_parser.c",
            "../ccp4io/lib/src/ccp4_unitcell.c",
            "../ccp4io/lib/src/cvecmat.c",
            "../ccp4io/lib/src/cmtzlib.c",
            "../ccp4io/lib/src/csymlib.c",
           ])
