
Summary:    Python Extension Module implementing tn3270 protocol
Name:		python-tn3270
Version:	5.2
Release:	0
License:	GPL-2.0
Source:		%{name}-%{version}.tar.xz
URL:		https://github.com/PerryWerneck/python-tn3270
Group:      Development/Libraries/Python

BuildRoot:	/var/tmp/%{name}-%{version}

BuildRequires:  autoconf >= 2.61
BuildRequires:  automake
BuildRequires:  binutils
BuildRequires:  coreutils
BuildRequires:  gcc-c++
BuildRequires:  m4
BuildRequires:  pkgconfig
BuildRequires:	fdupes

BuildRequires:  pkgconfig(ipc3270)

BuildRequires:	python
BuildRequires:  pkgconfig(python3)

Requires:		python

%description

This is an extension for acessing 3270 hosts directly
from python apps.

%prep

%setup

NOCONFIGURE=1 \
	./autogen.sh

%configure \
	--with-python-sitelib=%{python3_sitelib}

%build
make clean
make Release

%install

%make_install
%fdupes %{buildroot}

%clean

%files
%defattr(-,root,root)
%{python3_sitelib}/tn3270.so

%changelog


