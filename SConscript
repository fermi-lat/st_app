# -*- python -*-
# $Id: SConscript,v 1.6 2009/04/03 15:37:25 glastrm Exp $
# Authors: James Peachey <peachey@lheamail.gsfc.nasa.gov>
# Version: st_app-02-00-02
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('st_appLib', depsOnly = 1)
st_appLib = libEnv.StaticLibrary('st_app', listFiles(['src/*.cxx']))

progEnv.Tool('st_appLib')
st_app_mainBin = progEnv.Program('st_app_main', listFiles(['src/st_app_main/*.cxx']))
test_st_appBin = progEnv.Program('test_st_app', listFiles(['src/test/*.cxx']))

#progEnv.Tool('registerObjects', package = 'st_app', libraries = [st_appLib], binaries = [st_app_mainBin], testApps = [test_st_appBin], includes = listFiles(['st_app/*.h']), pfiles = listFiles(['pfiles/*.par']))

progEnv.Tool('registerTargets', package = 'st_app',
             staticLibraryCxts = [[st_appLib, libEnv]],
             binaryCxts = [[st_app_mainBin, progEnv]],
             testAppCxts = [[test_st_appBin, progEnv]],
             includes = listFiles(['st_app/*.h']),
             pfiles = listFiles(['pfiles/*.par']))
