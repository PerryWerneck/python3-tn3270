from distutils.core import setup, Extension

tn3270 = Extension('tn3270',
		define_macros = [('MAJOR_VERSION', '5'), ('MINOR_VERSION', '2')],
		include_dirs = ['src/include'],
		libraries = ['ipc3270'],
		library_dirs = ['/usr/lib64'],
		sources = [
			'src/action/type.c',
			'src/module/init.c',
			'src/session/type.c',
			'src/action/init.cc',
			'src/action/methods.cc',
			'src/action/new.cc',
			'src/action/tools.cc',
			'src/module/properties.cc',
			'src/session/network.cc',
			'src/session/tools.cc',
			'src/session/get.cc',
			'src/session/init.cc',
			'src/session/wait.cc',
			'src/session/misc.cc',
			'src/session/set.cc',
			'src/session/attributes.cc',
			'src/session/actions.cc'
		])

setup ( name = 'tn3270',
	version = '5.2',
	description = 'TN3270 module.',
	ext_modules = [ tn3270 ])

