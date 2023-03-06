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

 struct pyActionPrivate;

 typedef struct {
	PyObject_HEAD
	struct pyActionPrivate *pvt;
 } pyAction;

 DLL_PRIVATE void		py3270_action_dealloc(PyObject * self);

 DLL_PRIVATE PyObject * py3270_action_call(PyObject *callable, PyObject *args, PyObject *kwargs);
 DLL_PRIVATE PyObject * py3270_action_describe(PyObject *self, PyObject *obj, PyObject *type);
 DLL_PRIVATE PyObject * py3270_action_activate(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject * py3270_action_wait(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject * py3270_action_get_activatable(PyObject *self, void *dunno);
 DLL_PRIVATE PyObject * py3270_action_str(PyObject *self);

 #ifdef __cplusplus
	}
 #endif // __cplusplus

