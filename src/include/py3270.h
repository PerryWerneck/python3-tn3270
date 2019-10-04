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
 */

#ifndef PY3270_H_INCLUDED

	#define PY3270_H_INCLUDED

	#ifdef HAVE_CONFIG_H
		#include <config.h>
	#else
		#define PACKAGE_DESCRIPTION "Python bindings for lib3270/pw3270"
		#define HAVE_GNUC_VISIBILITY 1
	#endif // HAVE_CONFIG_H

	#ifndef PACKAGE_NAME
		#define PACKAGE_NAME "Python-TN3270"
	#endif // !PACKAGE_NAME

	#define PY_SSIZE_T_CLEAN
	#include <Python.h>

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

	#ifdef DEBUG
		#include <stdio.h>
		#undef trace
		#define trace( fmt, ... )       fprintf(stderr, "%s(%d) " fmt "\n", __FILE__, __LINE__, __VA_ARGS__ ); fflush(stderr);
		#define debug( fmt, ... )       fprintf(stderr, "%s(%d) " fmt "\n", __FILE__, __LINE__, __VA_ARGS__ ); fflush(stderr);
	#else
		#undef trace
		#define trace(x, ...)           // __VA_ARGS__
		#define debug(x, ...)           // __VA_ARGS__
	#endif

#ifdef __cplusplus

	#include <functional>
	#include <exception>
	#include <stdexcept>
	#include <system_error>
	#include <vector>
	#include <string>
	#include <lib3270/ipc.h>
	#include <lib3270/ipc/action.h>
	#include <lib3270/actions.h>

	using std::exception;
	using std::runtime_error;
	using std::string;
	using TN3270::Host;
	using TN3270::Action;

	DLL_PRIVATE PyObject	* py3270_session_call(PyObject *self, std::function<PyObject * (TN3270::Host &host)> worker) noexcept;
	DLL_PRIVATE PyObject	* py3270_session_call(PyObject *self, std::function<int (TN3270::Host &host)> worker) noexcept;

	DLL_PRIVATE PyObject	* py3270_action_call(PyObject *self, std::function<PyObject * (TN3270::Action &action)> worker) noexcept;

	DLL_PRIVATE void		  py3270_wait(Host &host, PyObject *args);

	DLL_PRIVATE string		  py3270_get_datadir() noexcept;

	extern "C" {

#else

	typedef void Host;
	typedef void Action;

#endif

		typedef struct {
			PyObject_HEAD
			Host *host;
		} pySession;

		typedef struct {
			PyObject_HEAD
			pySession	* session;
			Action		* action;
		} pyAction;

		DLL_PRIVATE PyTypeObject py3270_session_type;
		DLL_PRIVATE PyTypeObject py3270_action_type;

		DLL_PRIVATE const PyGetSetDef	py3270_session_attributes[];

		DLL_PRIVATE PyObject	* py3270_get_module_version(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_get_module_revision(PyObject *self, PyObject *args);

		// Types
		DLL_PRIVATE void 		  py3270_action_type_init(PyTypeObject *type);
		DLL_PRIVATE void 		  py3270_session_type_init(PyTypeObject *type);

		// Session object
		DLL_PRIVATE PyObject	* py3270_session_alloc(PyTypeObject *type, PyObject *args, PyObject *kwds);
		DLL_PRIVATE void		  py3270_session_dealloc(PyObject * self);

		DLL_PRIVATE int			  py3270_session_init(PyObject *self, PyObject *args, PyObject *kwds);
		DLL_PRIVATE void		  py3270_session_finalize(PyObject *self);

		DLL_PRIVATE PyObject	* py3270_session_getter(PyObject *self, void *name);
		DLL_PRIVATE int			  py3270_session_setter(PyObject *self, PyObject *value, void *name);

		DLL_PRIVATE PyObject	* py3270_session_get_timeout(PyObject *self, void *dunno);
		DLL_PRIVATE int			  py3270_session_set_timeout(PyObject *self, PyObject *value, void *dunno);

		DLL_PRIVATE PyObject	* py3270_session_connect(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* py3270_session_get(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_session_set(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject 	* py3270_session_str(PyObject *self);
		DLL_PRIVATE PyObject	* py3270_session_wait(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_session_find(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_session_count(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* py3270_session_pfkey(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_session_pakey(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_session_set_cursor_position(PyObject *self, PyObject *args);

		// Action object
		DLL_PRIVATE PyObject	* py3270_action_new_from_session(PyObject *session, void *action);
		DLL_PRIVATE void		  py3270_action_dealloc(PyObject * self);

		DLL_PRIVATE PyObject	* py3270_action_call(PyObject *callable, PyObject *args, PyObject *kwargs);
		DLL_PRIVATE PyObject	* py3270_action_describe(PyObject *self, PyObject *obj, PyObject *type);
		DLL_PRIVATE PyObject	* py3270_action_activate(PyObject *self, PyObject *args);
		DLL_PRIVATE PyObject	* py3270_action_wait(PyObject *self, PyObject *args);

		DLL_PRIVATE PyObject	* py3270_action_get_activatable(PyObject *self, void *dunno);
		DLL_PRIVATE PyObject 	* py3270_action_str(PyObject *self);

#ifdef __cplusplus
	}
#endif

#endif // PY3270_H_INCLUDED
