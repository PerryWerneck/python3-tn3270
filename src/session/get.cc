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

 PyObject * py3270_session_str(PyObject *self) {

 	return py3270_session_call(self, [](TN3270::Host &host){

		return PyUnicode_FromString(host.toString().c_str());

 	});

 }

 PyObject * py3270_session_get_timeout(PyObject *self, void *dunno) {

 	return py3270_session_call(self, [](TN3270::Host &host){

		return PyLong_FromLong(host.getTimeout());

 	});

 }
