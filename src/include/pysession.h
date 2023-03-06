/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2023 Perry Werneck <perry.werneck@gmail.com>
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
 #include <py3270.h>

 #ifdef __cplusplus
	extern "C" {
 #endif // __cplusplus

 struct pySessionPrivate;

 typedef struct {
	PyObject_HEAD
	struct pySessionPrivate *pvt;
 } pySession;

 DLL_PRIVATE PyObject	* py3270_session_alloc(PyTypeObject *type, PyObject *args, PyObject *kwds);
 DLL_PRIVATE void		  py3270_session_dealloc(PyObject * self);
 DLL_PRIVATE int		  py3270_session_init(PyObject *self, PyObject *args, PyObject *kwds);
 DLL_PRIVATE void		  py3270_session_finalize(PyObject *self);

 DLL_PRIVATE PyObject	* py3270_session_getter(PyObject *self, void *name);
 DLL_PRIVATE int		  py3270_session_setter(PyObject *self, PyObject *value, void *name);

 DLL_PRIVATE PyObject	* py3270_session_get_timeout(PyObject *self, void *dunno);
 DLL_PRIVATE int		  py3270_session_set_timeout(PyObject *self, PyObject *value, void *dunno);

 DLL_PRIVATE PyObject	* py3270_session_connect(PyObject *self, PyObject *args);

 DLL_PRIVATE PyObject	* py3270_session_get(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject	* py3270_session_set(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject 	* py3270_session_str(PyObject *self);
 DLL_PRIVATE PyObject	* py3270_session_wait(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject	* py3270_session_find(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject	* py3270_session_count(PyObject *self, PyObject *args);

 DLL_PRIVATE PyObject	* py3270_session_pfkey(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject	* py3270_session_pakey(PyObject *self, PyObject *args);

 DLL_PRIVATE PyObject	* py3270_session_set_cursor_position(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject	* py3270_session_get_cursor_position(PyObject *self, void *dunno);

 #ifdef __cplusplus
	}
 #endif // __cplusplus
