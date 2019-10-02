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

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyObject * py3270_session_getter(PyObject *self, void *name) {

//	debug("%s(%s)",__FUNCTION__,(const char *) name);

	return py3270_session_call(self, [name](TN3270::Host &host){

		auto attribute = host[(const char *) name];

		switch(attribute.getType()) {
		case TN3270::Attribute::String:
			return PyUnicode_FromString(attribute.toString().c_str());

		case TN3270::Attribute::Boolean:
			return PyBool_FromLong(attribute.getBoolean());

		case TN3270::Attribute::Uchar:
			throw std::system_error(ENOTSUP, std::system_category());

		case TN3270::Attribute::Int16:
			throw std::system_error(ENOTSUP, std::system_category());

		case TN3270::Attribute::Uint16:
			throw std::system_error(ENOTSUP, std::system_category());

		case TN3270::Attribute::Int32:
			return PyLong_FromLong(attribute.getInt32());

		case TN3270::Attribute::Int32x:
			throw std::system_error(ENOTSUP, std::system_category());

		case TN3270::Attribute::Uint32:
			return PyLong_FromLong(attribute.getUint32());

		case TN3270::Attribute::Int64:
			throw std::system_error(ENOTSUP, std::system_category());

		case TN3270::Attribute::Uint64:
			throw std::system_error(ENOTSUP, std::system_category());

		default:
			throw runtime_error("Unexpected atttribute type");
		}

		return PyLong_FromLong(0);

	});

}

int py3270_session_setter(PyObject *self, PyObject *value, void *name) {

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

