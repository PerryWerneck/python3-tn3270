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

 using std::string;

/*---[ Implement ]----------------------------------------------------------------------------------*/

 PyObject * py3270_session_get(PyObject *self, PyObject *args) {

 	return py3270_session_call(self, [args](TN3270::Host &host){

		string text;

		switch(PyTuple_Size(args)) {
		case 0: // Get the entire screen
			text = host.toString();
			break;

		case 2:	// Address and length.
			{
				int baddr, length;

				if (!PyArg_ParseTuple(args, "ii", &baddr, &length))
					return (PyObject *) NULL;

				text = host.toString(baddr, length);
			}
			break;

		case 3:	// Row, col and length
			{
				unsigned int row, col;
				int length;

				if (!PyArg_ParseTuple(args, "IIi", &row, &col, &length))
					return (PyObject *) NULL;

				text = host.toString(row, col, length);
			}
			break;

		default:
			throw std::system_error(EINVAL, std::system_category());

		}

		return PyUnicode_FromString(text.c_str());

 	});

 }

 DLL_PRIVATE PyObject * py3270_session_str(PyObject *self) {

 	return py3270_session_call(self, [](TN3270::Host &host){

		return PyUnicode_FromString(host.toString().c_str());

 	});

 }


	/*
DLL_PRIVATE PyObject * py3270_session_getattr(PyObject *self, char *attr_name) {

	PyObject * rc = NULL;

	printf("\n\n*************%s(%s)\n\n",__FUNCTION__,attr_name);

	try {

		TN3270::Property * property = ((pySession * ) self)->host->getProperty(attr_name);

		try {

			switch(property->getType()) {
			case TN3270::Property::String:
				rc = PyUnicode_FromString(property->toString().c_str());
				break;

			case TN3270::Property::Boolean:
				rc = PyBool_FromLong(property->toBool());
				break;

			case TN3270::Property::Uchar:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			case TN3270::Property::Int16:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			case TN3270::Property::Uint16:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			case TN3270::Property::Int32:
				rc = PyLong_FromLong(property->toInt32());
				break;

			case TN3270::Property::Int32x:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			case TN3270::Property::Uint32:
				rc = PyLong_FromLong(property->toUint32());
				break;

			case TN3270::Property::Int64:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			case TN3270::Property::Uint64:
				throw std::system_error(ENOTSUP, std::system_category());
				break;

			default:
				throw runtime_error("Unexpected property type");
			}

		} catch(...) {

			delete property;
			throw;

		}

		delete property;

	} catch(const exception &e) {

		PyErr_SetString(PyExc_RuntimeError, e.what());

	} catch( ... ) {

		PyErr_SetString(PyExc_RuntimeError, "Unexpected error in core module");

	}

	return rc;

}
*/


/*
PyObject * terminal_get_version(PyObject *self, PyObject *args) {

    return PyString_FromString( ((pw3270_TerminalObject *) self)->session->get_version().c_str() );

}

PyObject * terminal_get_revision(PyObject *self, PyObject *args) {

    return PyString_FromString( ((pw3270_TerminalObject *) self)->session->get_revision().c_str() );

}

PyObject * terminal_is_connected(PyObject *self, PyObject *args) {

    return PyBool_FromLong( ((pw3270_TerminalObject *) self)->session->is_connected() );

}

PyObject * terminal_is_ready(PyObject *self, PyObject *args) {

    return PyBool_FromLong( ((pw3270_TerminalObject *) self)->session->is_ready() );

}

PyObject * terminal_is_protected_at(PyObject *self, PyObject *args) {

	int rc, row, col;

	if (!PyArg_ParseTuple(args, "ii", &row, &col)) {
		PyErr_SetString(terminalError, strerror(EINVAL));
		return NULL;
	}

	try {

		rc = ((pw3270_TerminalObject *) self)->session->get_is_protected_at(row,col);

	} catch(std::exception &e) {

		PyErr_SetString(terminalError, e.what());
		return NULL;
	}

    return PyBool_FromLong( rc );

}


PyObject * terminal_cmp_string_at(PyObject *self, PyObject *args) {

	int row, col, rc;
	const char *text;

	if (!PyArg_ParseTuple(args, "iis", &row, &col, &text)) {
		PyErr_SetString(terminalError, strerror(EINVAL));
		return NULL;
	}

	try {

		rc = ((pw3270_TerminalObject *) self)->session->cmp_string_at(row,col,text);

	} catch(std::exception &e) {

		PyErr_SetString(terminalError, e.what());
		return NULL;
	}

	return PyLong_FromLong(rc);

}

PyObject * terminal_get_string_at(PyObject *self, PyObject *args) {

	int row, col, sz;
	string rc;

	if (!PyArg_ParseTuple(args, "iii", &row, &col, &sz)) {
		PyErr_SetString(terminalError, strerror(EINVAL));
		return NULL;
	}

	try {

		rc = ((pw3270_TerminalObject *) self)->session->get_string_at(row,col,sz);

	} catch(std::exception &e) {

		PyErr_SetString(terminalError, e.what());
		return NULL;
	}

	return PyString_FromString(rc.c_str());

}

PyObject * terminal_get_contents(PyObject *self) {

	string rc;

	try {

		rc = ((pw3270_TerminalObject *) self)->session->get_string();

	} catch(std::exception &e) {

		PyErr_SetString(terminalError, e.what());
		return NULL;
	}

	return PyString_FromString(rc.c_str());



}

*/
