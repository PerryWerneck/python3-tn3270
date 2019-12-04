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
 * Este programa está nomeado como - e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 * <https://docs.python.org/3/extending/extending.html>
 *
 */

 #include <py3270.h>

 static void cleanup(PyObject *module);

/*---[ Globals ]------------------------------------------------------------------------------------*/

static PyMethodDef methods[] = {

	{
		"version",
		py3270_get_module_version,
		METH_NOARGS,
		"Get package version"
	},

	{
		"revision",
		py3270_get_module_revision,
		METH_NOARGS,
		"Get package revision"

	},

	{
		NULL,
		NULL,
		0,
		NULL
	}

};

static struct PyModuleDef definition = {
	PyModuleDef_HEAD_INIT,
	.m_name = "tn3270",					// name of module
	.m_doc = PACKAGE_DESCRIPTION,		// module documentation, may be NUL
	.m_size = -1,						// size of per-interpreter state of the module or -1 if the module keeps state in global variables.
	.m_methods = methods,				// Module methods
	.m_free = (freefunc) cleanup
};

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyMODINIT_FUNC PyInit_tn3270(void)
{
	// Initialize custom attributes & methods.
	py3270_session_type_init(&py3270_session_type);
	if (PyType_Ready(&py3270_session_type) < 0)
		return NULL;

	py3270_action_type_init(&py3270_action_type);
	if (PyType_Ready(&py3270_action_type) < 0)
		return NULL;

    //
    // Initialize module.
    //

    Py_Initialize();

    PyObject *module = PyModule_Create(&definition);

	debug("Initializing module %p", module);

    if(!module)
		return NULL;

	//
	// Create custom type
	//
	Py_INCREF(&py3270_session_type);
    if (PyModule_AddObject(module, "Session", (PyObject *) &py3270_session_type) < 0) {
		Py_DECREF(&py3270_session_type);
		Py_DECREF(module);
		return NULL;
    }

    return module;
}

static void cleanup(PyObject *module) {

	debug("Cleaning up module %p", module);

	if(py3270_session_type.tp_getset) {
		free(py3270_session_type.tp_getset);
		py3270_session_type.tp_getset = NULL;
	}

}

