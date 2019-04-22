
%define pythonextpath %(python -c "from distutils.sysconfig import get_python_lib; print get_python_lib()")

Summary:        Python Extension Module implementing tn3270 protocol
Name:		lib3270-python-bindings
Version:	5.1
Release:	0
License:	GPL-2.0
Source:		%{name}-%{version}.tar.xz
URL:		https://portal.softwarepublico.gov.br/social/pw3270/
Group:          Development/Libraries/Python

BuildRoot:	/var/tmp/%{name}-%{version}

BuildRequires:  autoconf >= 2.61
BuildRequires:  automake
BuildRequires:  binutils
BuildRequires:  coreutils
BuildRequires:  gcc-c++
BuildRequires:  m4
BuildRequires:  pkgconfig
BuildRequires:	pkgconfig(pw3270) >= 5.1
BuildRequires:	fdupes

BuildRequires:	python
BuildRequires:  pkgconfig(python)

Requires:	python
Requires:       dbus-1

%description

This is an extension for acessing 3270 hosts directly
from python apps.

%prep

%setup

export CFLAGS="$RPM_OPT_FLAGS"
export CXXFLAGS="$RPM_OPT_FLAGS"
export FFLAGS="$RPM_OPT_FLAGS"

aclocal
autoconf
%configure

%build
make clean
make Release

%install
rm -rf $RPM_BUILD_ROOT

%make_install

%fdupes $RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{pythonextpath}/py3270.so

%changelog

