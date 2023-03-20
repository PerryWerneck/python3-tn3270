# Python Extension Module for TN3270 Access

Provide python3 objects to remote control an active pw3270 window or to direct access a TN3270 host using lib3270.

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![CodeQL](https://github.com/PerryWerneck/lib3270/workflows/CodeQL/badge.svg)
[![WinPackage](https://github.com/PerryWerneck/python3-tn3270/actions/workflows/winpkg.yml/badge.svg)](https://github.com/PerryWerneck/python3-tn3270/actions/workflows/winpkg.yml)
[![build result](https://build.opensuse.org/projects/home:PerryWerneck:pw3270/packages/python3-tn3270/badge.svg?type=percent)](https://build.opensuse.org/package/show/home:PerryWerneck:pw3270/python3-tn3270)

## Installation

### Linux

You can download installation package for supported distributions in Open Build Service.

[<img src="https://raw.githubusercontent.com/PerryWerneck/pw3270/master/branding/obs-badge-en.svg" alt="Download from open build service" height="80px">](https://software.opensuse.org/download.html?project=home%3APerryWerneck%3Apw3270&package=python3-tn3270)

### Windows

The installler for windows can be found on [Releases](../../releases)

## Examples

Getting module version

```python
#!/usr/bin/python
#-*- coding: utf-8

import tn3270

print("Using py3270 Version " + tn3270.version() + " revision " + tn3270.revision())
```

Getting pw3270 version

```python
#!/usr/bin/python
#-*- coding: utf-8

import tn3270

session = tn3270.Session(":a")

print("Using PW3270 version " + session.version + " revision " + session.revision)
```

Connecting first pw3270 window to host (if not connected), getting contents

```python
#!/usr/bin/python
#-*- coding: utf-8

import tn3270

session = tn3270.Session(":a")

if session.reconnect.try_activate():
	print("Reconnecting to host")
	session.wait(10)

print(session)
```

## Building from sources

### Linux

1. Install libipc3270-devel

2. Get python-tn3270 sources from git

	```shell
	git clone https://github.com/PerryWerneck/python-tn3270.git ./python-tn3270
	```

3. Build the extension using setup.py

	```shell
	cd python-tn3270
	python setup.py build
	```

4. Install extension

	```shell
	python setup.py install
	```
	
### Windows (With MSVC & Python SetupTools)

1. Install pw3270 with remote control and sdk modules

2. Download and install Visual Studio Build Tools (https://visualstudio.microsoft.com/pt-br/downloads/)

3. Get python-tn3270 sources from git

	```shell
	git clone https://github.com/PerryWerneck/python-tn3270.git ./python-tn3270
	```

4. Download and unpack libipc3270 pre-compiled image

	```shell
	wget https://github.com/PerryWerneck/libipc3270/releases/download/5.5/msvc-libipc3270.zip
	7z x msvc-libipc3270.zip -y -oipc3270
	```

5. Build the extension using setup.py

	```shell
	cd python-tn3270
	python setup.py build
	```

6. Install extension

	```shell
	python setup.py install
	```
	
7. Build windows installer (optional)

	```shell
	python setup.py bdist_wininst
	```


