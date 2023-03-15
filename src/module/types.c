/*
 * "Software pw3270, desenvolvido com base nos códigos fontes do WC3270  e X3270
 * (Paul Mattes Paul.Mattes@usa.net), de emulação de terminal 3270 para acesso a
 * aplicativos mainframe. Registro no INPI sob o nome G3270.
 *
 * Copyright (C) <2008> <Banco do Brasil S.A.>
 *
 * Este programa é software livre. Você pode redistribuí-lo e/ou modificá-lo sob
 * os termos da GPL v.2 - Licença Pública Geral  GNU,  conforme  publicado  pela
 * Free Software Foundation.
 *
 * Este programa é distribuído na expectativa de  ser  útil,  mas  SEM  QUALQUER
 * GARANTIA; sem mesmo a garantia implícita de COMERCIALIZAÇÃO ou  de  ADEQUAÇÃO
 * A QUALQUER PROPÓSITO EM PARTICULAR. Consulte a Licença Pública Geral GNU para
 * obter mais detalhes.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este
 * programa; se não, escreva para a Free Software Foundation, Inc., 51 Franklin
 * St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Este programa está nomeado como py3270.cc e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 * Referências:
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
		.ml_doc = ""
    },

    {
		.ml_name = "wait",
		.ml_meth = (PyCFunction) py3270_session_wait,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "set",
		.ml_meth = (PyCFunction) py3270_session_set,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "get",
		.ml_meth = (PyCFunction) py3270_session_get,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "find",
		.ml_meth = (PyCFunction) py3270_session_find,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "count",
		.ml_meth = (PyCFunction) py3270_session_count,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "setcursor",
		.ml_meth = (PyCFunction) py3270_session_set_cursor_position,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "getcursor",
		.ml_meth = (PyCFunction) py3270_session_get_cursor_position,
		.ml_flags = METH_NOARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "pf",
		.ml_meth = (PyCFunction) py3270_session_pfkey,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "pa",
		.ml_meth = (PyCFunction) py3270_session_pakey,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "pfkey",
		.ml_meth = (PyCFunction) py3270_session_pfkey,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
    },

    {
		.ml_name = "pakey",
		.ml_meth = (PyCFunction) py3270_session_pakey,
		.ml_flags = METH_VARARGS,
		.ml_doc = ""
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
		"activate",
		(PyCFunction) py3270_action_activate,
		METH_NOARGS,
		""
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
