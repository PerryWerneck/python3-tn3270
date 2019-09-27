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
 * Implementa métodos básicos inicio/final do objeto python
 *
 * Referências:
 *
 * <https://docs.python.org/2/extending/newtypes.html>
 * <https://docs.python.org/2.7/extending/extending.html#a-simple-example>
 *
 */

 #include <py3270.h>
 #include <lib3270/ipc.h>
 #include <lib3270/ipc/action.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyObject * py3270_action_call(PyObject *self, PyObject *args, PyObject *kwargs) {

	return py3270_action_activate(self,args);

}

PyObject * py3270_action_describe(PyObject *self, PyObject *obj, PyObject *type) {

	return py3270_action_call(self, [](TN3270::Action &action) {

		return (PyObject *) PyUnicode_FromString(action.getDescription());

	});

}

PyObject * py3270_action_activate(PyObject *self, PyObject *args) {

	return py3270_action_call(self, [args, self](TN3270::Action &action) {

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

PyObject * py3270_action_get_activatable(PyObject *self, void *dunno) {

	return py3270_action_call(self, [](TN3270::Action &action) {

		return PyBool_FromLong(action.activatable());

	});

}

PyObject * py3270_action_wait(PyObject *self, PyObject *args) {

	return py3270_action_call(self, [args, self](TN3270::Action &action) {

		py3270_wait( * ((pyAction *) self)->session->host, args);

		Py_INCREF(self);
		return self;

	});

}

PyObject * py3270_action_str(PyObject *self) {

	return py3270_action_call(self, [](TN3270::Action &action) {

		return PyUnicode_FromString(action.getSummary());

	});

}



