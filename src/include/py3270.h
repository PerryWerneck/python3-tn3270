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

 #pragma once

 #ifdef HAVE_CONFIG_H
	#include <config.h>
 #else
	#define PACKAGE_DESCRIPTION "Python bindings for lib3270/pw3270"
	#define PACKAGE_NAME "python3-tn3270"
	#define HAVE_GNUC_VISIBILITY 1
 #endif // HAVE_CONFIG_H

 #if defined(_WIN32)

	#include <WinSock2.h>
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

 #define PY_SSIZE_T_CLEAN
 #include <Python.h>

 #ifdef __cplusplus
	extern "C" {
 #endif // __cplusplus

 DLL_PRIVATE PyTypeObject py3270_session_type;
 DLL_PRIVATE PyTypeObject py3270_action_type;

 DLL_PRIVATE void py3270_session_type_init();
 DLL_PRIVATE void py3270_action_type_init();

 DLL_PRIVATE PyObject * py3270_get_module_version(PyObject *self, PyObject *args);
 DLL_PRIVATE PyObject * py3270_get_module_revision(PyObject *self, PyObject *args);

 DLL_PRIVATE PyObject * py3270_new_object(const char *classname);

 #ifdef __cplusplus
	}
 #endif // __cplusplus

