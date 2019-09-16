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
 * Este programa está nomeado como private.h e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

#ifndef PRIVATE_H_INCLUDED

	#define PRIVATE_H_INCLUDED

	// http://stackoverflow.com/questions/28683358/error-hypot-has-not-been-declared-in-cmath-while-trying-to-embed-python
	#include <cmath>

	// https://lists.gt.net/python/dev/340073
	#pragma GCC diagnostic push
	#pragma GCC system_header
	#include <Python.h>
	#pragma GCC diagnostic pop

	#include <pw3270/pw3270cpp.h>
	#include "config.h"

	#if defined(_WIN32)

			#include <windows.h>

			#define DLL_PRIVATE	extern
			#define DLL_PUBLIC	extern __declspec (dllexport)

	#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)

			#define DLL_PRIVATE		__hidden extern
			#define DLL_PUBLIC		extern

	#elif defined (HAVE_GNUC_VISIBILITY)

			#define DLL_PRIVATE		__attribute__((visibility("hidden"))) extern
			#define DLL_PUBLIC		__attribute__((visibility("default"))) extern

	#else

			#error Unable to set visibility attribute

	#endif


	using namespace std;

	typedef struct {

		PyObject_HEAD

		PW3270_NAMESPACE::session * session;

	} pw3270_TerminalObject;

	extern PyObject * terminalError;

	extern "C" {

		DLL_PRIVATE PyObject	* terminal_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
		DLL_PRIVATE int			  terminal_init(pw3270_TerminalObject *self, PyObject *args, PyObject *kwds);
		DLL_PRIVATE void		  terminal_dealloc(pw3270_TerminalObject * self);

		DLL_PRIVATE PyObject	* terminal_get_version(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* terminal_get_revision(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* terminal_is_connected(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* terminal_is_ready(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* terminal_connect(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* terminal_disconnect(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject 	* terminal_get_string_at(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* terminal_get_contents(PyObject *self);
		DLL_PRIVATE PyObject 	* terminal_set_string_at(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* terminal_cmp_string_at(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject 	* terminal_pfkey(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* terminal_pakey(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* terminal_enter(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* terminal_action(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject 	* terminal_is_protected_at(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* terminal_set_cursor_at(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* terminal_wait_for_ready(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* terminal_wait_for_string_at(PyObject *self, PyObject *args);

	}

#endif // PRIVATE_H_INCLUDED
