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
 * Este programa está nomeado como actions.cc e possui - linhas de código.
 *
 * Contatos
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

 #include <py3270.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyObject * py3270_session_pfkey(PyObject *self, PyObject *args) {

 	return py3270_session_call(self, [args](TN3270::Host &host){

		unsigned int keycode;

		if (!PyArg_ParseTuple(args, "I", &keycode))
			return (PyObject *) NULL;

		host.pfkey((unsigned short) keycode);

		return PyLong_FromLong(0);

	});

}

PyObject * py3270_session_pakey(PyObject *self, PyObject *args) {

 	return py3270_session_call(self, [args](TN3270::Host &host){

		unsigned int keycode;

		if (!PyArg_ParseTuple(args, "I", &keycode))
			return (PyObject *) NULL;

		host.pakey((unsigned short) keycode);

		return PyLong_FromLong(0);

 	});

}

PyObject * py3270_session_set_cursor_position(PyObject *self, PyObject *args) {

 	return py3270_session_call(self, [args](TN3270::Host &host){

		switch(PyTuple_Size(args)) {
		case 1:	// Only Address
			{
				int baddr;

				if(!PyArg_ParseTuple(args, "i", &baddr))
					return (PyObject *) NULL;

				host.setCursor(baddr);
			}
			break;

		case 2:	// Row, col
			{
				unsigned int row, col;

				if (!PyArg_ParseTuple(args, "II", &row, &col))
					return (PyObject *) NULL;

				host.setCursor(row,col);

			}
			break;

		default:
			throw std::system_error(EINVAL, std::system_category());

		}

		return PyLong_FromLong(0);

 	});

}
