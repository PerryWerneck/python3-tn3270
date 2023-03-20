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
 * Este programa está nomeado como misc.cc e possui - linhas de código.
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
 #include <pysession.h>
 #include <workers.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

 PyObject * py3270_session_connect(PyObject *self, PyObject *args) {

 	return py3270_call(self, [args](TN3270::Session &session){

 		// const char * url = "";
 		// bool wait = true;

 		switch(PyTuple_Size(args)) {
		case 0: // No argument.
			session.connect(DEFAULT_TIMEOUT);
			session.wait(TN3270::CONNECTED_TN3270E);
			return 0;

		case 1:	// Just URL (or timeout)
			{
				const char * url = "";
				if(!PyArg_ParseTuple(args, "s", &url)) {
					session.connect(url,DEFAULT_TIMEOUT);
					session.wait(TN3270::CONNECTED_TN3270E);
				}

				unsigned int timeout;
				if(!PyArg_ParseTuple(args, "I", &url,&timeout)) {
					session.connect(timeout);
				}

				throw std::system_error(EINVAL, std::system_category());

			}
			return 0;

		case 2:	// URL and timeout
			{
				const char * url = "";
				unsigned int timeout = 1;

				if(!PyArg_ParseTuple(args, "sI", &url,&timeout))
					throw std::system_error(EINVAL, std::system_category());

				session.connect(url,timeout);
				session.waitForConnectionState(TN3270::CONNECTED_TN3270E,timeout);
				return 0;

			}
			return 0;

		default:
			throw std::system_error(EINVAL, std::system_category());

 		}

		return 0;

	});

 }
