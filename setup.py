from distutils.core import setup, Extension, os
import platform

include_dirs = ['src/include']
library_dirs = []
extra_link_args = []

if platform.system() == 'Windows':
	include_dirs.append(os.getenv('PW3270_SDK_PATH') + '/include')
	library_dirs.append(os.getenv('PW3270_SDK_PATH') + '/lib')

	with open(os.getenv('PW3270_SDK_PATH') + "\\lib3270.mak") as file:
		text = file.readlines()

		for line in text:
			if line.startswith("LIB3270_NAME="):
				extra_link_args.append("/delayload:" + line.split("=")[1].rstrip("\r").rstrip("\n") + ".dll")

tn3270 = Extension(
		'tn3270',
		include_dirs = include_dirs,
		libraries = ['ipc3270'],
		library_dirs=library_dirs,
		extra_link_args=extra_link_args,
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
			'src/session/actions.cc',
			'src/module/windows/init.cc',
			'src/module/windows/tools.cc'
		])

setup ( name = 'tn3270',
	version = '5.2',
	description = 'Python bindings for lib3270/pw3270.',
	author = 'Perry Werneck',
	author_email = 'perry.werneck@gmail.com',
	url = 'https://github.com/PerryWerneck/python3-tn3270',
	long_description = '''
This is an extension allowing tn3270 acess for python applications
using lib3270 directly or ipc calls to an enabled pw3270 window.
''',
	ext_modules = [ tn3270 ])

