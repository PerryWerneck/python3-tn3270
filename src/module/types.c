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
 #include <pysession.h>
 #include <pyaction.h>

 static PyMethodDef py3270_session_methods[] = {
    {
		.ml_name = "connect",
		.ml_meth = (PyCFunction) py3270_session_connect,
		.ml_flags = METH_VARARGS,
		.ml_doc =	"Connect to host, wait for session startup\n\n"
					"connect(): Connect to default host using default timeout\n"
					"connect(url): Connect to host on url using default timeout\n"
					"connect(url,timeout): Connect to host on url wait 'timeout' seconds for session startup\n"
    },

    {
		.ml_name = "wait",
		.ml_meth = (PyCFunction) py3270_session_wait,
		.ml_flags = METH_VARARGS,
		.ml_doc = 	"Wait for session to be ready for input or an specified value\n\n"
					"wait(): Wait for default timeout\n"
					"wait(seconds): Wait for 'seconds' seconds\n"
					"wait(address,'string'): Wait for string at address\n"
					"wait(row,col,'string'): Wait for string at row, col\n"


    },

    {
		.ml_name = "set",
		.ml_meth = (PyCFunction) py3270_session_set,
		.ml_flags = METH_VARARGS,
		.ml_doc =	"Input string to terminal\n\n"
					"set('string'): Input string at current cursor position\n"
					"set(address,'string'): Input string at address\n"
					"set(row,col,'string'): Input string at row, col\n"
    },

    {
		.ml_name = "get",
		.ml_meth = (PyCFunction) py3270_session_get,
		.ml_flags = METH_VARARGS,
		.ml_doc =	"Get terminal contents\n\n"
					"get(): Get the entire terminal contents\n"
					"get(address,length): Get length characters starting at address\n"
					"get(row,col,length): Get length characters starting at row, col"

    },

    {
		.ml_name = "find",
		.ml_meth = (PyCFunction) py3270_session_find,
		.ml_flags = METH_VARARGS,
		.ml_doc =	"Search for string on terminal\n\n"
					"find('string'): Return the address of 'string' on terminal"
    },

    {
		.ml_name = "count",
		.ml_meth = (PyCFunction) py3270_session_count,
		.ml_flags = METH_VARARGS,
		.ml_doc = 	"Get the number of occurrences of a string in the terminal\n\n"
					"count('string'): Return the numger of ocurrences of 'string' on terminal"
    },

    {
		.ml_name = "setcursor",
		.ml_meth = (PyCFunction) py3270_session_set_cursor_position,
		.ml_flags = METH_VARARGS,
		.ml_doc =	"Set cursor position for the next input\n\n"
					"setcursor(address): Next input will take place at address\n"
					"setcursor(row,col): Next input will take place at row, col"
    },

    {
		.ml_name = "getcursor",
		.ml_meth = (PyCFunction) py3270_session_get_cursor_position,
		.ml_flags = METH_NOARGS,
		.ml_doc = "Get cursor position (row and column)"
    },

    {
		.ml_name = "getgeometry",
		.ml_meth = (PyCFunction) py3270_session_get_geometry,
		.ml_flags = METH_NOARGS,
		.ml_doc = "Get terminal geometry (width, height and length)."
    },

    {
		.ml_name = "pf",
		.ml_meth = (PyCFunction) py3270_session_pfkey,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Send PF-Key action to host\n\npf(key-number)"
    },

    {
		.ml_name = "pa",
		.ml_meth = (PyCFunction) py3270_session_pakey,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Send PA-Key action to host\n\npf(key-number)"
    },

    {
		.ml_name = "pfkey",
		.ml_meth = (PyCFunction) py3270_session_pfkey,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Send PF-Key action to host\n\npf(key-number)"
    },

    {
		.ml_name = "pakey",
		.ml_meth = (PyCFunction) py3270_session_pakey,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Send PA-Key action to host\n\npf(key-number)"
    },

    {
    	NULL
	}
 };

 PyTypeObject py3270_session_type = {

	PyVarObject_HEAD_INIT(NULL, 0)

	.tp_name = "tn3270.Session",
	.tp_doc = "TN3270 Session Object",
	.tp_basicsize = sizeof(pySession),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_HAVE_FINALIZE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,

	.tp_new = py3270_session_alloc,
	.tp_dealloc = py3270_session_dealloc,

	.tp_init = py3270_session_init,
	.tp_finalize = py3270_session_finalize,

	.tp_str = py3270_session_str,

	.tp_methods = py3270_session_methods,

 };

 static PyMethodDef py3270_action_methods[] = {

    {
		.ml_name = "activate",
		.ml_meth = (PyCFunction) py3270_action_activate,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Activate action"
    },

    {
		.ml_name = "try_activate",
		.ml_meth = (PyCFunction) py3270_action_try_activate,
		.ml_flags = METH_VARARGS,
		.ml_doc = "Activate action only if available, returns 'true' if activated and 'false' if the action cant be activated"
    },

    {
    	NULL
	}
 };

 static struct PyGetSetDef py3270_action_attributes[] = {

	{
		.name = "activatable",
		.doc = "True if the action can be activated",
		.get = py3270_action_get_activatable
	},

	{
		NULL
	}

 };

 PyTypeObject py3270_action_type = {

	PyVarObject_HEAD_INIT(NULL, 0)

	.tp_name = "tn3270.Action",
	.tp_doc = "TN3270 Action Object",
	.tp_basicsize = sizeof(pyAction),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_HAVE_FINALIZE|Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,

	.tp_new = py3270_action_alloc,
	.tp_dealloc = py3270_action_dealloc,

	.tp_init = py3270_action_init,
	.tp_finalize = py3270_action_finalize,

	.tp_call = py3270_action_call,
    .tp_descr_get = py3270_action_describe,

	.tp_methods = py3270_action_methods,
	.tp_getset = py3270_action_attributes,
	.tp_str = py3270_action_str,

 };
