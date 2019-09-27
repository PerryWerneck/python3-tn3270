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

/*---[ Globals ]------------------------------------------------------------------------------------*/

static PyMethodDef py3270_action_methods[] = {

    {
		"activate",
		(PyCFunction) py3270_action_activate,
		METH_NOARGS,
		""
    },

    {
		"wait",
		(PyCFunction) py3270_action_wait,
		METH_VARARGS,
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

// https://docs.python.org/3/c-api/typeobj.html
PyTypeObject py3270_action_type = {

	PyVarObject_HEAD_INIT(NULL, 0)

	.tp_name = "tn3270.Session.Action",
	.tp_doc = "TN3270 Action Object",
	.tp_basicsize = sizeof(pyAction),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_DEFAULT,

	.tp_call = py3270_action_call,
    .tp_descr_get = py3270_action_describe,

	.tp_methods = py3270_action_methods,
	.tp_getset = py3270_action_attributes,
	.tp_str = py3270_action_str,

	.tp_dealloc = py3270_action_dealloc,


};


