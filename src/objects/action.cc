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
 #include <pyaction.h>
 #include <workers.h>

 #include <memory>
 #include <lib3270/ipc/action.h>

 using namespace std;

 struct pyActionPrivate {
	shared_ptr<TN3270::Action> action;
 };

 void py3270_action_type_init() {

		size_t szData = sizeof(struct PyGetSetDef) * 2;

		py3270_action_type.tp_getset = (struct PyGetSetDef *) malloc(szData);
		memset(py3270_action_type.tp_getset,0,szData);

		py3270_action_type.tp_getset[0].name = (char *) "activatable";
		py3270_action_type.tp_getset[0].doc = (char *) "True if the action can be activated; read-only attribute";
		py3270_action_type.tp_getset[0].get = (getter) py3270_action_get_activatable;

 }

 int py3270_action_init(PyObject *self, PyObject *args, PyObject *kwds) {

	pyActionPrivate * hAction = ((pyAction *) self)->pvt;
	if(!hAction) {
		((pyAction *) self)->pvt = hAction = new pyActionPrivate{};
	}

	return 0;
 }

 void py3270_action_finalize(PyObject *self) {

	pyActionPrivate * hAction = ((pyAction *) self)->pvt;
	if(hAction) {
		hAction->action.reset();
	}
 }

 PyObject * py3270_action_alloc(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	return type->tp_alloc(type,0);
 }

 void py3270_action_dealloc(PyObject * self) {
	pyActionPrivate * hAction = ((pyAction *) self)->pvt;
	if(hAction) {
		delete hAction;
		((pyAction *) self)->pvt = nullptr;
	}
	Py_TYPE(self)->tp_free(self);
 }

 PyObject * py3270_action_new(std::shared_ptr<TN3270::Action> action) {

	PyObject * object = py3270_new_object("Action");

	pyActionPrivate * hAction = ((pyAction *) object)->pvt;
	hAction->action = action;

	return object;

 }

 PyObject * py3270_call(PyObject *self, const std::function<PyObject * (TN3270::Action &action)> &worker) noexcept {

	try {

		pyActionPrivate * hAction = ((pyAction *) self)->pvt;

		if(!hAction->action) {
			throw runtime_error("Invalid action handler");
		}

		return worker(*hAction->action);

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in action handler");

	}

	return NULL;

 }

 PyObject * py3270_action_call(PyObject *self, PyObject *args, PyObject *kwargs) {

	return py3270_call(self, [self,args](TN3270::Action &action) {

		switch(PyTuple_Size(args)) {
		case 0:	// No time defined, use the default one.
			action.activate();
			break;

		case 1:	// Only one argument, its the time.
			{
				unsigned int seconds;

				if(!PyArg_ParseTuple(args, "I", &seconds))
					throw std::system_error(EINVAL, std::system_category());

				action.activate();
				action.wait(seconds);
			}
			break;

		default:
			throw std::system_error(EINVAL, std::system_category());

		}

		Py_INCREF(self);
		return self;

	});

 }

 PyObject * py3270_action_get_activatable(PyObject *self, void *dunno) {

	return py3270_call(self, [](TN3270::Action &action) {
		return PyBool_FromLong(action.activatable());
	});

 }

 PyObject * py3270_action_describe(PyObject *self, PyObject *obj, PyObject *type) {
	return py3270_call(self, [](TN3270::Action &action) {
		return (PyObject *) PyUnicode_FromString(action.description());
	});
 }

 PyObject * py3270_action_try_activate(PyObject *self, PyObject *args) {
	return py3270_call(self, [args, self](TN3270::Action &action) {

		if(!action.activatable()) {
			return PyBool_FromLong(0);
		}

		if(PyTuple_Size(args) == 1) {

			unsigned int seconds;

			if (!PyArg_ParseTuple(args, "I", &seconds))
				return (PyObject *) NULL;

			action.activate();
			action.wait(seconds);

		} else {

			action.activate();

		}

		return PyBool_FromLong(1);

	});
 }

 PyObject * py3270_action_activate(PyObject *self, PyObject *args) {

	return py3270_call(self, [args, self](TN3270::Action &action) {

		if(PyTuple_Size(args) == 1) {

			unsigned int seconds;

			if (!PyArg_ParseTuple(args, "I", &seconds))
				return (PyObject *) NULL;

			action.activate();
			action.wait(seconds);

		} else {

			action.activate();

		}

		Py_INCREF(self);
		return self;

	});

 }

 PyObject * py3270_action_str(PyObject *self) {

 	return py3270_call(self, [](TN3270::Action &action) {
		return PyUnicode_FromString(action.summary());
	});

 }

