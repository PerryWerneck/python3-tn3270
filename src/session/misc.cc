/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) <2008> Banco do Brasil S.A.
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

/*
 * Authors:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 * Reference:
 *
 * <https://docs.python.org/2/extending/newtypes.html>
 * <https://docs.python.org/2.7/extending/extending.html#a-simple-example>
 *
 */

 #include <py3270.h>
 #include <workers.h>
 #include <pysession.h>
 #include <lib3270/ipc/session.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

 PyObject * py3270_session_find(PyObject *self, PyObject *args) {

 	return py3270_call(self, [self, args](TN3270::Session &session){

		const char *text;

		if(!PyArg_ParseTuple(args, "s", &text))
			throw std::system_error(EINVAL, std::system_category());

		return session.find(text);

 	});

 }

 PyObject * py3270_session_count(PyObject *self, PyObject *args) {

 	return py3270_call(self, [self, args](TN3270::Session &session){

		const char *text;

		if(!PyArg_ParseTuple(args, "s", &text))
			throw std::system_error(EINVAL, std::system_category());

		return session.count(text);

 	});

 }
