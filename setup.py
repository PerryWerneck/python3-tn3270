from setuptools import setup, Extension
import platform
import os

include_dirs = ['src/include']
library_dirs = []
extra_link_args = []

src_files = [
	'src/module/init.c',
	'src/module/types.c',
	'src/session/type.c',
	'src/action/methods.cc',
	'src/action/new.cc',
	'src/action/tools.cc',
	'src/module/properties.cc',
	'src/session/actions.cc',
	'src/session/attributes.cc',
	'src/session/get.cc',
	'src/session/init.cc',
	'src/session/misc.cc',
	'src/session/network.cc',
	'src/session/set.cc',
	'src/session/tools.cc',
	'src/session/wait.cc',
	'src/objects/action.cc',
	'src/objects/session.cc'
]

library_names = [
]

if platform.system() == 'Windows':
	extra_link_args.append("/delayload:lib3270.dll")
	#extra_link_args.append("/NODEFAULTLIB:LIBCMT")
	
	src_files.append('src/module/windows/init.cc' )
	src_files.append('src/module/windows/tools.cc' )
	library_names.append('ipc3270.static')
	
	if os.path.isdir('ipc3270'):
		include_dirs.append('ipc3270/include')
		library_dirs.append('ipc3270/lib')
	else:
		include_dirs.append(os.getenv('PW3270_SDK_PATH') + '/include')
		library_dirs.append(os.getenv('PW3270_SDK_PATH') + '/lib')
else:
	library_names.append('ipc3270')


tn3270 = Extension(
		'tn3270',
		include_dirs = include_dirs,
		libraries = library_names,
		library_dirs=library_dirs,
		extra_link_args=extra_link_args,
		sources=src_files
)

setup ( name = 'tn3270',
	version = '5.4',
	description = 'Python bindings for lib3270/pw3270.',
	author = 'Perry Werneck',
	author_email = 'perry.werneck@gmail.com',
	url = 'https://github.com/PerryWerneck/python3-tn3270',
	long_description = '''
This is an extension allowing tn3270 acess for python applications
using lib3270 directly or ipc calls to an enabled pw3270 window.
''',
	ext_modules = [ tn3270 ])

