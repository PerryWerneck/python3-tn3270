/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright 1995, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006 by Paul Mattes.
 * Copyright (C) 2008 Banco do Brasil S.A.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #else
	#define PACKAGE_DESCRIPTION "Python bindings for lib3270/pw3270"
	#define PACKAGE_NAME "python3-tn3270"
	#define HAVE_GNUC_VISIBILITY 1
 #endif // HAVE_CONFIG_H

 #if defined(_WIN32)

	#include <WinSock2.h>
	#include <windows.h>

	#define DLL_PRIVATE	extern
	#define DLL_PUBLIC	extern __declspec (dllexport)

 #elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)

	#define DLL_PRIVATE		__hidden extern
	#define DLL_PUBLIC		extern

 #else

	#define DLL_PRIVATE		__attribute__((visibility("hidden"))) extern
	#define DLL_PUBLIC		__attribute__((visibility("default"))) extern

 #endif

 #define PY_SSIZE_T_CLEAN
 #include <Python.h>

 #ifdef __cplusplus
	extern "C" {
 #endif // __cplusplus

 DLL_PRIVATE PyTypeObject py3270_session_type;
 DLL_PRIVATE PyTypeObject py3270_action_type;

 DLL_PRIVATE void py3270_session_type_init();
 DLL_PRIVATE void py3270_action_type_init();

 DLL_PRIVATE const char * py3270_check_requires();

 DLL_PRIVATE PyObject * py3270_get_module_version(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject * py3270_get_module_revision(PyObject *self, PyObject *args);

 DLL_PRIVATE PyObject * py3270_new_object(const char *classname);

 #ifdef __cplusplus
	}
 #endif // __cplusplus

