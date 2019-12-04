dnl
dnl Software pw3270, desenvolvido com base nos códigos fontes do  C3270  e  X3270
dnl (Paul Mattes Paul.Mattes@usa.net), de emulação de terminal 3270 para acesso a
dnl aplicativos mainframe. Registro no INPI sob o nome G3270.
dnl
dnl Copyright (C) <2008> <Banco do Brasil S.A.>
dnl
dnl Este programa é software livre. Você pode redistribuí-lo e/ou modificá-lo sob
dnl os termos da GPL v.2 - Licença Pública Geral  GNU,  conforme  publicado  pela
dnl Free Software Foundation.
dnl
dnl Este programa é distribuído na expectativa de  ser  útil,  mas  SEM  QUALQUER
dnl GARANTIA; sem mesmo a garantia implícita de COMERCIALIZAÇÃO ou  de  ADEQUAÇÃO
dnl A QUALQUER PROPÓSITO EM PARTICULAR. Consulte a Licença Pública Geral GNU para
dnl obter mais detalhes.
dnl
dnl Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este
dnl programa;  se  não, escreva para a Free Software Foundation, Inc., 59 Temple
dnl Place, Suite 330, Boston, MA, 02111-1307, USA
dnl
dnl Contatos:
dnl
dnl perry.werneck@gmail.com	(Alexandre Perry de Souza Werneck)
dnl erico.mendonca@gmail.com	(Erico Mascarenhas de Mendonça)
dnl

dnl Process this file with autoconf to produce a configure script.

dnl The minimum version of autoconf required.
AC_PREREQ(2.61)

dnl Initialise automake with the package name, version and
dnl bug-reporting address.
AC_INIT([python3-tn3270], [5.2], [perry.werneck@gmail.com])

dnl Place auxilliary scripts here.
AC_CONFIG_AUX_DIR([scripts])

dnl Compute the canonical host-system type
AC_CANONICAL_HOST

dnl Put macro definitions here (though they aren't used).
AC_CONFIG_HEADER([src/include/config.h])

dnl Initialise automake stuff.
AM_INIT_AUTOMAKE

dnl Check for iconv
AM_ICONV

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_SED
AC_PROG_LN_S

AC_LANG([C++])

dnl ---------------------------------------------------------------------------
dnl Version info
dnl ---------------------------------------------------------------------------

app_vrs_major=$(echo $VERSION | cut -d. -f1)
app_vrs_minor=$(echo $VERSION | cut -d. -f2)

AC_DEFINE_UNQUOTED(PACKAGE_MAJOR_VERSION, $app_vrs_major)
AC_DEFINE_UNQUOTED(PACKAGE_MINOR_VERSION, $app_vrs_minor)

AC_SUBST(PACKAGE_MAJOR_VERSION,$app_vrs_major)
AC_SUBST(PACKAGE_MINOR_VERSION,$app_vrs_minor)

app_cv_release="`date +%-y`.`date +%-m`.`date +%-d`"
app_cv_revision=`date +%y%m%d`

app_rls_major=$(echo $app_cv_release.0.0 | cut -d. -f1)
app_rls_minor=$(echo $app_cv_release.0.0 | cut -d. -f2)

AC_DEFINE_UNQUOTED(PACKAGE_RELEASE, $app_cv_release)
AC_DEFINE_UNQUOTED(PACKAGE_REVISION,$app_cv_revision)
AC_DEFINE_UNQUOTED(PACKAGE_MAJOR_RELEASE, $app_rls_major)
AC_DEFINE_UNQUOTED(PACKAGE_MINOR_RELEASE, $app_rls_minor)

AC_SUBST(PACKAGE_RELEASE,$app_cv_release)
AC_SUBST(PACKAGE_REVISION,$app_cv_revision)
AC_SUBST(PACKAGE_MAJOR_RELEASE,$app_rls_major)
AC_SUBST(PACKAGE_MINOR_RELEASE,$app_rls_minor)

dnl ---------------------------------------------------------------------------
dnl Check for OS specifics
dnl ---------------------------------------------------------------------------

case "$host" in
	*-mingw32|*-pc-msys)
		app_cv_osname="windows"

		CFLAGS="$CFLAGS -pthread -D_WIN32_WINNT=0x0600"
		CXXFLAGS="$CXXFLAGS -pthread -D_WIN32_WINNT=0x0600"
		LIBS="$LIBS -lws2_32 -lwtsapi32 -lcomdlg32"
		LDFLAGS="$LDFLAGS -static-libgcc -static-libstdc++"
		DLLEXT=".dll"

		app_win32_revision=$(date +%-y.%-m.%-d.%-H)
		AC_SUBST(WIN32_VERSION,$app_win32_revision)

		app_win32_file_version=$(date +%-y,%-m,%-d,%-H)
		AC_SUBST(WIN32_FILE_VERSION,$app_win32_file_version)

		AC_CONFIG_FILES(src/module/windows/resources.rc)
dnl		AC_CONFIG_FILES(win/py3270.nsi)

		if test "$host_cpu" = "x86_64"; then
			app_cv_programfiles="PROGRAMFILES64"
dnl			app_cv_winarch="64"
		else
			app_cv_programfiles="PROGRAMFILES"
dnl			app_cv_winarch="32"
		fi

		AC_SUBST(PROGRAMFILES,$app_cv_programfiles)
dnl		AC_SUBST(WINARCH,$app_cv_winarch)
dnl                AC_SUBST(SONAME,py3270.dll)

		;;

 	*)
		CFLAGS="$CFLAGS -pthread"
		CXXFLAGS="$CXXFLAGS -pthread"
		LDFLAGS="$LDFLAGS -pthread"
		app_cv_osname="linux"
		LOGDIR="/var/log"
		DLLEXT=".so"
dnl                AC_SUBST(SONAME,py3270.so.$app_vrs_major.$app_vrs_minor)

esac

dnl ---------------------------------------------------------------------------
dnl Check for other programs
dnl ---------------------------------------------------------------------------

AC_PATH_TOOL([AR], [ar], [ar])
AC_PATH_TOOL([WINDRES], [windres], [no])
AC_PATH_TOOL([VALGRIND], [valgrind], [no])
AC_PATH_TOOL([ZIP], [zip], [zip])

PKG_CHECK_EXISTS

AC_ARG_WITH([product-name], [AS_HELP_STRING([--with-product-name], [Set product name])], [ app_cv_product="$withval" ],[ app_cv_product=`$PKG_CONFIG --variable=product_name lib3270` ])
AC_DEFINE_UNQUOTED(PRODUCT_NAME, $app_cv_product)
AC_SUBST(PRODUCT_NAME,$app_cv_product)

dnl ---------------------------------------------------------------------------
dnl Check for C++ 2011 support
dnl ---------------------------------------------------------------------------
AC_DEFUN([AX_CHECK_COMPILE_FLAG],
[AC_PREREQ(2.59)dnl for _AC_LANG_PREFIX
AS_VAR_PUSHDEF([CACHEVAR],[ax_cv_check_[]_AC_LANG_ABBREV[]flags_$4_$1])dnl
AC_CACHE_CHECK([whether _AC_LANG compiler accepts $1], CACHEVAR, [
  ax_check_save_flags=$[]_AC_LANG_PREFIX[]FLAGS
  _AC_LANG_PREFIX[]FLAGS="$[]_AC_LANG_PREFIX[]FLAGS $4 $1"
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM()],
    [AS_VAR_SET(CACHEVAR,[yes])],
    [AS_VAR_SET(CACHEVAR,[no])])
  _AC_LANG_PREFIX[]FLAGS=$ax_check_save_flags])
AS_IF([test x"AS_VAR_GET(CACHEVAR)" = xyes],
  [m4_default([$2], :)],
  [m4_default([$3], :)])
AS_VAR_POPDEF([CACHEVAR])dnl
])dnl AX_CHECK_COMPILE_FLAGS

AX_CHECK_COMPILE_FLAG([-std=gnu++11], [CXXFLAGS="$CXXFLAGS -std=gnu++11"])

dnl ---------------------------------------------------------------------------
dnl Check for IPC3270
dnl ---------------------------------------------------------------------------

AC_ARG_WITH([static-ipc3270],
        [AS_HELP_STRING([--with-static-ipc3270], [Uses static version of ipc3270])],
[
	app_cv_static_ipc3270=$withval
],[
	app_cv_static_ipc3270="no"
])

if test "$app_cv_static_ipc3270" == "yes"; then

	PKG_CHECK_MODULES( [IPC3270], [ipc3270-static], AC_DEFINE(USING_STATIC_IPC3270), AC_MSG_ERROR([IPC3270 not present.]))

else

	PKG_CHECK_MODULES( [IPC3270], [ipc3270], AC_DEFINE(USING_SHARED_IPC3270), AC_MSG_ERROR([IPC3270 not present.]))

	case "$host" in
	*-mingw32|*-pc-msys)
		LDFLAGS="$LDFLAGS -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive,-Bdynamic"
		AC_MSG_NOTICE([Using shared version of libipc3270 with static winpthread.])
		;;

	*)
		AC_MSG_NOTICE([Using shared version of libipc3270.])

	esac

fi

AC_SUBST(IPC3270_LIBS)
AC_SUBST(IPC3270_CFLAGS)

dnl ---------------------------------------------------------------------------
dnl Check for Python
dnl ---------------------------------------------------------------------------

PKG_CHECK_MODULES( [PYTHON], [python3], AC_DEFINE(HAVE_PYTHON3), AC_MSG_ERROR([Python devel is unavailable]))

AC_SUBST(PYTHON_LIBS)
AC_SUBST(PYTHON_CFLAGS)

AC_ARG_WITH([python-sitelib], [AS_HELP_STRING([--with-python-sitelib], [Set python-sitelib])], [ app_cv_python_sitelib="$withval" ],[ app_cv_python_sitelib=`python3 -c 'import site; print(site.getsitepackages().pop(0))'` ])
AC_DEFINE_UNQUOTED(PYTHON_SITELIB, $app_cv_python_sitelib)
AC_SUBST(PYTHON_SITELIB,$app_cv_python_sitelib)

AC_ARG_WITH([python-version], [AS_HELP_STRING([--with-python-version], [Set Python Version])], [ app_cv_python_version="$withval" ],[ app_cv_python_version=`$PKG_CONFIG --modversion python3` ])
AC_DEFINE_UNQUOTED(PYTHON_VERSION, $app_cv_python_version)
AC_SUBST(PYTHON_VERSION,$app_cv_python_version)

dnl ---------------------------------------------------------------------------
dnl Check for ELF symbol visibility support
dnl ---------------------------------------------------------------------------
m4_define([GLIB_CHECK_COMPILE_WARNINGS],
[m4_ifvaln([$1], [AC_LANG_CONFTEST([$1])])dnl
rm -f conftest.$ac_objext
glib_ac_compile_save="$ac_compile"
ac_compile='$CC -c $CFLAGS $CPPFLAGS conftest.$ac_ext'
AS_IF([_AC_EVAL_STDERR($ac_compile) &&
         AC_TRY_COMMAND([(if test -s conftest.err; then false ; else true; fi)])],
      [$2],
      [echo "$as_me: failed program was:" >&AS_MESSAGE_LOG_FD
cat conftest.$ac_ext >&AS_MESSAGE_LOG_FD
m4_ifvaln([$3],[$3])dnl])
ac_compile="$glib_ac_compile_save"
rm -f conftest.$ac_objext conftest.err m4_ifval([$1], [conftest.$ac_ext])[]dnl
])# GLIB_CHECK_COMPILE_WARNINGS

AC_MSG_CHECKING(for GNUC visibility attribute)
GLIB_CHECK_COMPILE_WARNINGS([
void
__attribute__ ((visibility ("hidden")))
     f_hidden (void)
{
}
void
__attribute__ ((visibility ("internal")))
     f_internal (void)
{
}
void
__attribute__ ((visibility ("protected")))
     f_protected (void)
{
}
void
__attribute__ ((visibility ("default")))
     f_default (void)
{
}
int main (int argc, char **argv)
{
        f_hidden();
        f_internal();
        f_protected();
        f_default();
        return 0;
}
],g_have_gnuc_visibility=yes,g_have_gnuc_visibility=no)
AC_MSG_RESULT($g_have_gnuc_visibility)
if test x$g_have_gnuc_visibility = xyes; then
  AC_DEFINE(HAVE_GNUC_VISIBILITY, 1, [supports GCC visibility attributes])
fi

dnl ---------------------------------------------------------------------------
dnl Check for pic
dnl ---------------------------------------------------------------------------

AC_ARG_ENABLE([pic],
	[AS_HELP_STRING([--disable-pic], [disable support for PIC libraries (required to compile on 64bits)])],
[
	app_cv_pic="$enableval"
],[

	case "$host_cpu" in
	x86_64)
		app_cv_pic="yes"
		;;

	aarch64)
		app_cv_pic="yes"
		;;

	*)
		app_cv_pic="no"
	esac

])

if test "$app_cv_pic" == "yes"; then
	CFLAGS="$CFLAGS -fPIC"
	CXXFLAGS="$CXXFLAGS -fPIC"
fi

dnl ---------------------------------------------------------------------------
dnl Configure program options
dnl ---------------------------------------------------------------------------

app_cv_description="Python $app_cv_python_version bindings for lib3270/pw3270"

AC_SUBST(PACKAGE_DESCRIPTION,"$app_cv_description")
AC_DEFINE_UNQUOTED(PACKAGE_DESCRIPTION,"$app_cv_description")

AC_SUBST(OSNAME,$app_cv_osname)
AC_SUBST(LIBS)
AC_SUBST(DLLEXT)

CFLAGS="$CFLAGS -DHAVE_CONFIG_H"
CXXFLAGS="$CXXFLAGS -DHAVE_CONFIG_H"

AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(BASEDIR,$ac_pwd)

dnl ---------------------------------------------------------------------------
dnl Configure which files to generate.
dnl ---------------------------------------------------------------------------

AC_CONFIG_FILES(Makefile)

dnl ---------------------------------------------------------------------------
dnl Output the generated config.status script.
dnl ---------------------------------------------------------------------------

AC_OUTPUT


