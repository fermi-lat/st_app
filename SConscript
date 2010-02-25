# -*- python -*-
# $Id: SConscript,v 1.10 2010/02/22 23:13:36 jrb Exp $
# Authors: James Peachey <peachey@lheamail.gsfc.nasa.gov>
# Version: st_app-02-00-04
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()
if baseEnv['PLATFORM'] == 'posix':
    libEnv.Append(CPPDEFINES = 'TRAP_FPE')

st_appLib = libEnv.StaticLibrary('st_app', listFiles(['src/*.cxx']))

progEnv.Tool('st_appLib')
if baseEnv['PLATFORM'] == 'posix':
    progEnv.Append(CPPDEFINES = 'TRAP_FPE')

st_app_mainBin = progEnv.Program('st_app_main', listFiles(['src/st_app_main/*.cxx']))
test_st_appBin = progEnv.Program('test_st_app', listFiles(['src/test/*.cxx']))


progEnv.Tool('registerTargets', package = 'st_app',
             staticLibraryCxts = [[st_appLib, libEnv]],
             binaryCxts = [[st_app_mainBin, progEnv]],
             testAppCxts = [[test_st_appBin, progEnv]],
             includes = listFiles(['st_app/*.h']),
             pfiles = listFiles(['pfiles/*.par']))
