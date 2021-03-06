## Python Extension Module for TN3270 Access

## Installation

### Linux

For the supported distributions get the install repositories and instructions from https://software.opensuse.org/download.html?project=home%3APerryWerneck%3Apw3270&package=python3-tn3270

### Windows

Installation package for windows is not available yet.

## Building from sources

### Linux

	TODO

### Windows (With MSVC & Python SetupTools)

1. Install pw3270 with remote control and sdk modules

2. Download and install Visual Studio Build Tools (https://visualstudio.microsoft.com/pt-br/downloads/)

3. Build and install the "glue" library using the MSVC Native tools command prompt as administrator.

	```shell
	git clone https://github.com/PerryWerneck/libipc3270.git ./ipc3270
	cd ipc3270
	install.bat
	```

4. Get python-tn3270 sources from git

	```shell
	git clone https://github.com/PerryWerneck/python-tn3270.git ./python-tn3270
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


