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
 * Este programa está nomeado como set.cc e possui - linhas de código.
 *
 * Contatos
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

 void py3270_wait(TN3270::Host &host, PyObject *args) {

	switch(PyTuple_Size(args)) {
	case 0:	// No time defined, use the default one.
		host.waitForReady();
		break;

	case 1:	// Only one argument, its the time.
		{
			unsigned int seconds;

			if(!PyArg_ParseTuple(args, "I", &seconds))
				throw std::system_error(EINVAL, std::system_category());

			host.waitForReady(seconds);
		}
		break;

	case 2:	// 2 arguments, it's the address and content.
		{
			int baddr;
			const char *text;

			if(!PyArg_ParseTuple(args, "is", &baddr, &text))
				throw std::system_error(EINVAL, std::system_category());

			host.wait(baddr,text);
		}
		break;

	case 3:	// 3 arguments, it's the row, col, and content.
		{
			unsigned int row, col;
			const char *text;

			if (!PyArg_ParseTuple(args, "IIs", &row, &col, &text))
				throw std::system_error(EINVAL, std::system_category());

			host.wait(row,col,text);

		}
		break;

	default:
		throw std::system_error(EINVAL, std::system_category());

	}


 }

 PyObject * py3270_session_wait(PyObject *self, PyObject *args) {

 	return py3270_session_call(self, [self, args](TN3270::Host &host){

		py3270_wait(host, args);

		Py_INCREF(self);
		return self;

 	});

 }
