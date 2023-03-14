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
 * Este programa está nomeado como get.cc e possui - linhas de código.
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
 #include <workers.h>
 #include <lib3270/ipc/session.h>
 #include <lib3270/ipc/property.h>
 #include <stdexcept>

 using namespace std;

 PyObject * py3270_session_get_attribute(PyObject *self, const LIB3270_PROPERTY *property) {

	return py3270_call(self, [property](TN3270::Session &session){

		switch(TN3270::Property::find(property->name)->type()) {
		case TN3270::Property::Integer:
			return PyLong_FromLong(session.getProperty<int32_t,unsigned long>(property->name));

		case TN3270::Property::Unsigned:
			return PyLong_FromLong(session.getProperty<uint32_t,unsigned long>(property->name));

		case TN3270::Property::String:
			return PyUnicode_FromString(session.getProperty<std::string,std::string>(property->name).c_str());

		case TN3270::Property::Boolean:
			return PyBool_FromLong(session.getProperty<bool,unsigned long>(property->name));

		default:
			throw runtime_error("Invalid attribute");
		}

		return PyLong_FromLong(0);

	});

}

int py3270_session_set_attribute(PyObject *self, PyObject *value, const LIB3270_PROPERTY *property) {

	py3270_call(self, [property,value](TN3270::Session &session){

		switch(TN3270::Property::find(property->name)->type()) {
		case TN3270::Property::Integer:
			session.setProperty(property->name,(int) PyLong_AsUnsignedLong(value));
			break;

		case TN3270::Property::Unsigned:
			session.setProperty(property->name,(unsigned int) PyLong_AsUnsignedLong(value));
			break;

		case TN3270::Property::String:
			session.setProperty(property->name,(const char *) PyUnicode_AsUTF8AndSize(value,NULL));
			break;

		case TN3270::Property::Boolean:
			session.setProperty(property->name,(bool) (PyLong_AsUnsignedLong(value) != 0));
			break;

		default:
			throw runtime_error("Invalid attribute");
		}

		return 0;
	});

	return 0;

}

/*

int py3270_session_set_attribute(PyObject *self, PyObject *value, const LIB3270_PROPERTY *property) {

	try {

		auto attribute = ((pySession * ) self)->host->getAttribute((const char *) name);

		if(PyLong_Check(value)) {

			// Is a long, use PyLong_AsUnsignedLong
			attribute = (int) PyLong_AsUnsignedLong(value);

		} else if(PyBool_Check(value)) {

			// Is a boolean, use PyLong_AsUnsignedLong != 0
			attribute = (bool) (PyLong_AsUnsignedLong(value) != 0);

		} else if(PyUnicode_Check(value)) {

			// Is a unicode string
			attribute = (const char *) PyUnicode_AsUTF8AndSize(value,NULL);

		}

	} catch(const exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());
		return -1;

	} catch( ... ) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error setting attribute");
		return -1;

	}

	return 0;
}
*/
