#$Id: st_appLib.py,v 1.3 2008/02/26 05:45:34 glastrm Exp $
def generate(env, **kw):
	if not kw.get('depsOnly',0):
		env.Tool('addLibrary', library = ['st_app'])
	env.Tool('hoopsLib')
	env.Tool('st_graphLib')
	env.Tool('st_streamLib')
	env.Tool('facilitiesLib')
	env.Tool('addLibrary', library = env['f2cLibs'])

def exists(env):
	return 1
