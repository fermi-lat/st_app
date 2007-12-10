import glob,os,platform

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

if platform.system() == 'Linux':
        progEnv.Append(CPPDEFINES = 'TRAP_FPE')

st_appLib = libEnv.StaticLibrary('st_app', listFiles(['src/*.cxx']))

progEnv.Tool('st_appLib')
st_app_mainBin = progEnv.Program('st_app_main', listFiles(['src/st_app_main/*.cxx']))

progEnv.Tool('registerObjects', package = 'st_app', libraries = [st_appLib], binaries = [st_app_mainBin], includes = listFiles(['st_app/*.h']), pfiles = listFiles(['pfiles/*.par']))