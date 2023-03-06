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

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <py3270.h>
 #include <pysession.h>
 #include <workers.h>

 #include <memory>
 #include <lib3270.h>
 #include <lib3270/ipc.h>
 #include <lib3270/ipc/session.h>
 #include <vector>

 using namespace std;

 struct pySessionPrivate {
	std::shared_ptr<TN3270::Session> session;
 };

 void py3270_session_type_init() {

	// Initialize attributes
	{
		// Get available properties.
		vector<const LIB3270_PROPERTY *> properties;
		TN3270::for_each([&properties](const LIB3270_PROPERTY &property){
			properties.push_back(&property);
			return false;
		});

		// Get available actions.
		vector<const LIB3270_ACTION *> actions;
		TN3270::for_each([&actions](const LIB3270_ACTION &action){
			actions.push_back(&action);
			return false;
		});

		// Allocate getset data.
		size_t szData = sizeof(struct PyGetSetDef) * (properties.size() + actions.size() + 1);
		py3270_session_type.tp_getset = (struct PyGetSetDef *) malloc(szData);
		memset(py3270_session_type.tp_getset,0,szData);

		size_t index = 0;

		// Load attributes.
		for(auto property : properties) {

			py3270_session_type.tp_getset[index].name	 = (char *) property->name;
			py3270_session_type.tp_getset[index].doc     = (char *) (property->summary ? property->summary : "");
			py3270_session_type.tp_getset[index].closure = (void *) property;
			py3270_session_type.tp_getset[index].get     = (getter) py3270_session_get_attribute;
			py3270_session_type.tp_getset[index].set     = (setter) py3270_session_set_attribute;

			index++;
		}

		// Load actions.
		for(auto action : actions) {

			py3270_session_type.tp_getset[index].name	 = (char *) action->name;
			py3270_session_type.tp_getset[index].doc     = (char *) (action->summary ? action->summary : "");
			py3270_session_type.tp_getset[index].closure = (void *) action;
			py3270_session_type.tp_getset[index].get	 = (getter) py3270_session_get_action;
			py3270_session_type.tp_getset[index].set	 = (setter) py3270_session_set_action;

			index++;
		}

	}

 }

 int py3270_session_init(PyObject *self, PyObject *args, PyObject *kwds) {

	pySessionPrivate * hSession = ((pySession *) self)->pvt;

	try {

		if(hSession->session) {
			throw runtime_error("Session is already initialized");
		}

		const char *id = "";
		if (!PyArg_ParseTuple(args, "s", &id))
			id = "";

		hSession->session = TN3270::Session::getInstance(id,"UTF-8");

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return -1;
 }

 void py3270_session_finalize(PyObject *self) {
	pySessionPrivate * hSession = ((pySession *) self)->pvt;
	hSession->session.reset();
 }

 PyObject * py3270_session_alloc(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	return type->tp_alloc(type,0);
 }

 void py3270_session_dealloc(PyObject * self) {
	pySessionPrivate * hSession = ((pySession *) self)->pvt;
	hSession->session.reset();
	Py_TYPE(self)->tp_free(self);
 }

 PyObject * py3270_call(PyObject *self, const std::function<std::string (TN3270::Session &session)> &worker) noexcept {

	std::string text;

	try {

		pySessionPrivate * hSession = ((pySession *) self)->pvt;

		if(hSession->session) {
			throw runtime_error("Session is not initialized");
		}

		text = worker(*hSession->session);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());
		return (PyObject *) NULL;

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");
		return (PyObject *) NULL;

	}

	return PyUnicode_FromString(text.c_str());

 }

 PyObject * py3270_call(PyObject *self, const std::function<int (TN3270::Session &session)> &worker) noexcept {

	int value = 0;

	try {

		pySessionPrivate * hSession = ((pySession *) self)->pvt;

		if(hSession->session) {
			throw runtime_error("Session is not initialized");
		}

		value = worker(*hSession->session);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());
		return PyLong_FromLong(0);

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");
		return PyLong_FromLong(0);

	}

	return PyLong_FromLong((long) value);

 }

 PyObject * py3270_call(PyObject *self, const std::function<PyObject * (TN3270::Session &session)> &worker) noexcept {

	try {

		pySessionPrivate * hSession = ((pySession *) self)->pvt;

		if(hSession->session) {
			throw runtime_error("Session is not initialized");
		}

		return worker(*hSession->session);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());
		return PyLong_FromLong(0);

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");
		return PyLong_FromLong(0);

	}

	return NULL;

 }

