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
 * programa;  se  não, escreva para a Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA, 02111-1307, USA
 *
 * Este programa está nomeado como - e possui - linhas de código.
 *
 * Contatos:
 *
 * perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
 * erico.mendonca@gmail.com	(Erico Mascarenhas Mendonça)
 *
 */

 #include <py3270.h>
 #include <lib3270.h>
 #include <lib3270/ipc.h>
 #include <string>

/*--[ Implement ]------------------------------------------------------------------------------------*/

 const char * py3270_check_requires() {

#ifdef _WIN32
	if(TN3270::getInstallLocation().empty()) {
		return "Can't determine location of pw3270 runtime, is it installed?";
	}

	if(strcmp(lib3270_get_revision(),"20220101") < 0) {
		return "lib" LIB3270_STRINGIZE_VALUE_OF(LIB3270_NAME) " is too old";
	}

#else

	if(strcasecmp(lib3270_get_revision(),"20220101") < 0) {
		return "lib" LIB3270_STRINGIZE_VALUE_OF(LIB3270_NAME) " is too old";
	}

#endif // _WIN32

	return NULL;

 }

