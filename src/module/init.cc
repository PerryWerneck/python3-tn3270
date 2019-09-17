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
 * <https://docs.python.org/3/extending/extending.html>
 *
 */

 #include <py3270.h>

/*---[ Implement ]----------------------------------------------------------------------------------*/

PyMODINIT_FUNC PyInit_tn3270(void)
{
    static PyMethodDef methods[] = {

        {
            "version",
            py3270_get_module_version,
            METH_NOARGS,
            "Get " PACKAGE_NAME " version"
        },

        {
            "revision",
            py3270_get_module_revision,
            METH_NOARGS,
            "Get " PACKAGE_NAME " revision"

        },

        {
            NULL,
            NULL,
            0,
            NULL
        }

    };

    static struct PyModuleDef definition = {
        PyModuleDef_HEAD_INIT,
        "tn3270",               // name of module
        PACKAGE_DESCRIPTION,    // module documentation, may be NUL
        -1,                     // size of per-interpreter state of the module or -1 if the module keeps state in global variables.
        methods                 // Module methods
    };

    Py_Initialize();

    PyObject *module = PyModule_Create(&definition);

    if(module) {

        PyObject * except = PyErr_NewException("tn3270.error", NULL, NULL);

        Py_XINCREF(except);
        if (PyModule_AddObject(module, "error", except) < 0) {
            Py_XDECREF(except);
            Py_CLEAR(except);
            Py_DECREF(module);
            return NULL;
        }

    }


    /*

    m = PyModule_Create(&spammodule);
    if (m == NULL)
        return NULL;

    SpamError = PyErr_NewException("spam.error", NULL, NULL);
    Py_XINCREF(SpamError);
    if (PyModule_AddObject(m, "error", SpamError) < 0) {
        Py_XDECREF(SpamError);
        Py_CLEAR(SpamError);
        Py_DECREF(m);
        return NULL;
    }

    */

    return module;
}
