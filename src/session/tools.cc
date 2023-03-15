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
 */

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #endif // HAVE_CONFIG_H

 #include <py3270.h>
 #include <stdexcept>
 #include <iostream>
 #include <string>

 using namespace std;

 PyObject * py3270_new_object(const char *classname) {

	PyObject *module_name = PyUnicode_FromString("tn3270");
	PyObject *module = PyImport_Import(module_name);
	if(!module) {
		Py_DECREF(module_name);
		throw runtime_error("Cant import module");
	}
	Py_DECREF(module_name);

	PyObject *dict = PyModule_GetDict(module);
	if(!dict) {
		Py_DECREF(module);
		throw runtime_error("Cant get module dict");
	}
	Py_DECREF(module);

	PyObject *pyclass = PyDict_GetItemString(dict,classname);
	if(!pyclass) {
		Py_DECREF(dict);
		throw runtime_error(string{"Cant find class '"} + classname + "'");
	}
	Py_DECREF(dict);

	// Creates an instance of the class
	if (PyCallable_Check(pyclass)) {
		PyObject *object = PyObject_CallObject(pyclass, nullptr);
		Py_DECREF(pyclass);
		return object;
	}
	Py_DECREF(pyclass);

	throw runtime_error(string{"Cant method '"} + classname + "' is not callable");

 }

