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
 * Referênces:
 *
 * <https://docs.python.org/2/extending/newtypes.html>
 * <https://docs.python.org/2.7/extending/extending.html#a-simple-example>
 *
 */

 #include <py3270.h>
 #include <lib3270/ipc.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

static void cleanup(pySession * session) {

	if(session->host) {
		delete session->host;
		session->host = nullptr;
	}

}

static void py3270_session_attribute_init(struct PyGetSetDef *attribute, const LIB3270_PROPERTY * descriptor) {

	attribute->name    = (char *) descriptor->name;
	attribute->doc     = (char *) (descriptor->description ? descriptor->description : descriptor->summary);

}

void py3270_session_type_init(PyTypeObject *type) {

	// Load attributes
	{
		auto attributes = TN3270::getAttributes();
		auto actions	= TN3270::getActions();
		size_t ix = 0;

		// Compute block size
		size_t szData = sizeof(struct PyGetSetDef) * (attributes.size() + actions.size() + 1);

		for(size_t i = 0; py3270_session_attributes[i].name; i++) {
			szData += sizeof(struct PyGetSetDef);
		}

		// Allocate and clean
		type->tp_getset = (struct PyGetSetDef *) malloc(szData);
		memset(type->tp_getset,0,szData);

		// Copy internal attributes
		for(size_t i = 0; py3270_session_attributes[i].name; i++) {
			type->tp_getset[ix] = py3270_session_attributes[i];
			ix++;
		}

		// Copy lib3270's attributes
		for(auto attribute : attributes) {

			py3270_session_attribute_init(&type->tp_getset[ix], (const LIB3270_PROPERTY *) attribute);

			type->tp_getset[ix].get     = py3270_session_getter;
			type->tp_getset[ix].set     = py3270_session_setter;
			type->tp_getset[ix].closure = (void *) attribute->name;

			ix++;

		}

		// Copy lib3270's actions
		for(auto action : actions) {

			py3270_session_attribute_init(&type->tp_getset[ix], (const LIB3270_PROPERTY *) action);

			type->tp_getset[ix].get = py3270_action_new_from_session;
			type->tp_getset[ix].closure = (void *) action;

			ix++;

		}

	}

}

int py3270_session_init(PyObject *self, PyObject *args, PyObject *kwds) {

	pySession * session = (pySession *) self;
	debug("%s session=%p host=%p",__FUNCTION__,session,session->host);

	try {

		cleanup(session);

		const char *id = "";

		if (!PyArg_ParseTuple(args, "s", &id))
			id = "";

		session->host = new TN3270::Host(id,"UTF-8");

        return 0;

	} catch(const std::exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch(...) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return -1;

}

void py3270_session_finalize(PyObject *self) {

	debug("%s",__FUNCTION__);
	cleanup((pySession *) self);

}

PyObject * py3270_session_alloc(PyTypeObject *type, PyObject *args, PyObject *kwds) {

	debug("%s",__FUNCTION__);
	return type->tp_alloc(type,0);

}

void py3270_session_dealloc(PyObject * self) {

	debug("%s",__FUNCTION__);

	cleanup((pySession *) self);
	Py_TYPE(self)->tp_free(self);

}
