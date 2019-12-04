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

/**
 * @file
 *
 * @brief Win32 delayed loading support methods.
 *
 * @author perry.werneck@gmail.com
 *
 */

 #include <py3270.h>

 #if defined(_WIN32)

 #include <lmcons.h>
 #include <delayimp.h>
 #include <fcntl.h>
 #include <string>
 #include <stdexcept>
 #include <lib3270.h>

 #if defined(_MSC_VER)
	#pragma comment(lib,"DelayImp.lib")
	#pragma comment(lib,"Advapi32.lib")
 #endif // _MSC_VER

 extern "C" {

//	extern __declspec (dllexport) PfnDliHook __pfnDliNotifyHook2;
//	extern __declspec (dllexport) PfnDliHook __pfnDliFailureHook2;

	FARPROC WINAPI py3270_delay_load_hook(unsigned reason, DelayLoadInfo * info);

 }

 using std::string;

/*---[ Implement ]----------------------------------------------------------------------------------*/

 // https://docs.microsoft.com/en-us/cpp/build/reference/loading-all-imports-for-a-delay-loaded-dll?view=vs-2019

 #if defined(_MSC_VER)
	const PfnDliHook __pfnDliNotifyHook2 = py3270_delay_load_hook;
	const PfnDliHook __pfnDliFailureHook2 = py3270_delay_load_hook;
 #else
	PfnDliHook __pfnDliNotifyHook2 = py3270_delay_load_hook;
	PfnDliHook __pfnDliFailureHook2 = py3270_delay_load_hook;
 #endif // _MSC_VER

 static HANDLE hModule = 0;
 static HANDLE hEventLog = 0;

 BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwcallpurpose, LPVOID lpvResvd) {
    switch(dwcallpurpose) {
    case DLL_PROCESS_ATTACH:
        hModule = hInstance;
        hEventLog = RegisterEventSource(NULL, PACKAGE_NAME);
        break;

	case DLL_PROCESS_DETACH:
		hModule = 0;
		DeregisterEventSource(hEventLog);
		hEventLog = 0;
		break;

    }

    return TRUE;
 }

 static void eventlog(const char *msg) {

		char	username[UNLEN + 1];
		DWORD	szName = sizeof(username);

		memset(username,0,UNLEN + 1);

		if(!GetUserName(username, &szName)) {
			username[0] = 0;
		}

        const char *outMsg[] = {
                username,
                PACKAGE_NAME,
                msg
        };

        debug("Event: \"%s\"",msg);

        ReportEvent(
                hEventLog,
                EVENTLOG_ERROR_TYPE,
                1,
                0,
                NULL,
                3,
                0,
                outMsg,
                NULL
        );

 }

 static void dummyProc() {
	throw std::runtime_error("Operation not supported");
 }

 FARPROC WINAPI py3270_delay_load_hook(unsigned reason, DelayLoadInfo * info) {

	static string savedpath;

	// https://docs.microsoft.com/en-us/cpp/build/reference/structure-and-constant-definitions?view=vs-2019

	switch (reason) {
	case dliNoteStartProcessing:
		{
			string installLocation = TN3270::getInstallLocation();

			if(!installLocation.empty()) {

				char curdir[4096];
				memset(curdir,0,sizeof(curdir));

				if(GetCurrentDirectory(sizeof(curdir)-1,curdir)) {
					savedpath = curdir;
				} else {
					savedpath.clear();
				}

				SetCurrentDirectory(installLocation.c_str());

			}
		}
		break;

	case dliNoteEndProcessing:

		if(!savedpath.empty()) {
			SetCurrentDirectory(savedpath.c_str());
			savedpath.clear();

		}

		break;

	case dliNotePreLoadLibrary:
		break;

	case dliNotePreGetProcAddress:
		break;

	case dliFailLoadLib:
		{
			string msg = "Can't load ";
			msg += (const char *) info->szDll;
			eventlog(msg.c_str());
		}
		return (FARPROC) hModule;

	case dliFailGetProc:
		{
			string msg = "Can't find method on ";
			msg += (const char *) info->szDll;
			eventlog(msg.c_str());
		}
		return (FARPROC) dummyProc;

	}

	// Returning NULL causes the delay load machinery to perform default
	// processing for this notification.
	return NULL;

 }

 #endif // _WIN32

