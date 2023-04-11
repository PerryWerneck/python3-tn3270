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
 #include <pysession.h>
 #include <workers.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyObject * py3270_session_pfkey(PyObject *self, PyObject *args) {

 	return py3270_call(self, [args](TN3270::Session &session){

		unsigned int keycode;

		if (!PyArg_ParseTuple(args, "I", &keycode))
			throw std::system_error(EINVAL, std::system_category());

		session.pfkey((unsigned short) keycode);
		return 0;

	});

}

PyObject * py3270_session_pakey(PyObject *self, PyObject *args) {

 	return py3270_call(self, [args](TN3270::Session &session){

		unsigned int keycode;

		if (!PyArg_ParseTuple(args, "I", &keycode))
			throw std::system_error(EINVAL, std::system_category());

		session.pakey((unsigned short) keycode);
		return 0;

	});

}

PyObject * py3270_session_set_cursor_position(PyObject *self, PyObject *args) {

 	return py3270_call(self, [args](TN3270::Session &session){

		switch(PyTuple_Size(args)) {
		case 1:	// Only Address
			{
				int baddr;

				if(!PyArg_ParseTuple(args, "i", &baddr))
					throw std::system_error(EINVAL, std::system_category());

				session.setCursor(baddr);
			}
			break;

		case 2:	// Row, col
			{
				unsigned int row, col;

				if (!PyArg_ParseTuple(args, "II", &row, &col))
					throw std::system_error(EINVAL, std::system_category());

				session.setCursor(row,col);

			}
			break;

		default:
			throw std::system_error(EINVAL, std::system_category());

		}

		return 0;

 	});

}

PyObject * py3270_session_get_cursor_position(PyObject *self, void *dunno) {

 	return py3270_call(self, [](TN3270::Session &session){

		auto cursor_position = session.getCursorPosition();

		return Py_BuildValue("{s:i,s:i}", "row", (int) cursor_position.row , "col", (int) cursor_position.col );

 	});

}

PyObject * py3270_session_get_geometry(PyObject *self, void *dunno) {

 	return py3270_call(self, [](TN3270::Session &session){

		return Py_BuildValue(
					"{s:i,s:i,s:i}",
						"width", (int) session.getScreenWidth() ,
						"height", (int) session.getScreenHeight(),
						"length", (int) session.getScreenLength()
					);

 	});

}
