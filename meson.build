# Maintainer: Perry Werneck <perry.werneck@gmail.com>

# SPDX-License-Identifier: LGPL-3.0-or-later 

# Copyright (C) 2025 Perry Werneck <perry.werneck@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

project(
	'pytn3270', 
	['c', 'cpp'],
	version: '5.5.0',
	default_options : ['cpp_std=c++17', 'buildtype=release' ],
	license: 'GPL-3.0-or-later',
)

project_description = 'Python bindings for lib3270/pw3270.'

#
# Versioning
#
pkg_version = meson.project_version()
version_array = pkg_version.split('.')
pkg_major_version = version_array[0].to_int()
pkg_minor_version = version_array[1].to_int()
pkg_micro_version = version_array[2].to_int()

#
# Compiler flags
#
cxx = meson.get_compiler('cpp')
cc = meson.get_compiler('c')
enable_debug = get_option('debug') or get_option('buildtype').contains('debug')

compiler_flags_common = [
  '-fvisibility=hidden',
  '-DHAVE_CONFIG_H=1',
  '-ggdb3',
  '-fPIC',
	]

if enable_debug
  compiler_flags_common += [
	  '-DDEBUG=1'
  ]
else
  compiler_flags_common += [
	'-DNDEBUG=1'
  ]
endif

add_project_arguments(cxx.get_supported_arguments(compiler_flags_common), language: 'cpp')
add_project_arguments(cc.get_supported_arguments(compiler_flags_common), language: 'c')

#
# Dependencies
#
ipc3270 = dependency(
    'libipc3270', 
    required: true,
    version: '>= 5.5.0',
    fallback: [ 
      'libipc3270', 
      'static_library'
    ]
  )

#
# Configuration
#
app_conf = configuration_data()
app_conf.set_quoted('PACKAGE_NAME', meson.project_name())
app_conf.set_quoted('PACKAGE_VERSION', meson.project_version())
app_conf.set_quoted('PACKAGE_DESCRIPTION', project_description)
app_conf.set('PACKAGE_VERSION_MAJOR', pkg_major_version)
app_conf.set('PACKAGE_VERSION_MINOR', pkg_minor_version)
app_conf.set('PACKAGE_VERSION_MICRO', pkg_micro_version)

app_conf.set('PRODUCT_ID',ipc3270.get_variable('product_id'))
app_conf.set('PRODUCT_NAME', ipc3270.get_variable('product_name'))
app_conf.set('PRODUCT_VERSION', meson.project_version())

if cxx.compiles('#include <unistd.h>', name : 'unistd.h')
  app_conf.set('HAVE_UNISTD_H', 1)
endif

config_src = [
  configure_file(
      output : 'config.h', 
      configuration : app_conf
  )
]

#
# Dependencies
#
sources = [
  'src/module/init.c',
  'src/module/types.c',
  'src/module/properties.cc',
  'src/module/windows/init.cc',
  'src/module/tools.cc',
  'src/objects/action.cc',
  'src/objects/session.cc',
  'src/session/actions.cc',
  'src/session/attributes.cc',
  'src/session/get.cc',
  'src/session/network.cc',
  'src/session/set.cc',
  'src/session/tools.cc',
  'src/session/wait.cc',
  'src/session/misc.cc',
]

includes_dir = include_directories('src/include')

if host_machine.system() == 'windows'

  # https://mesonbuild.com/Windows-module.html
  windows = import('windows')
  resources = windows.compile_resources(
    configure_file(
      input : 'src/module/windows/resources.rc.in',
      output : 'resources.rc',
      configuration : app_conf
    )
  )

  sources += resources
 
endif

import('python').find_installation().extension_module(
  meson.project_name(),
  sources,
  install: true,
  install_tag: 'python', 
  dependencies: [
    ipc3270,
    dependency('python3', required:true, method : 'pkg-config'),
  ],
  include_directories: includes_dir
)

configure_file(
  input : 'branding/metainfo.xml.in',
  output : ipc3270.get_variable('product_id') + '.python.metainfo.xml',
  install_dir: get_option('datadir') / 'metainfo',
  configuration : app_conf
)

