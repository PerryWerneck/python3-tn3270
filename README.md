Python Extension Module for TN3270 Acess
========================================


Linux Installation repositories
===============================

 You can find instalation repositories in SuSE Build Service:

 * Linux (Many distributions): https://build.opensuse.org/package/show/home:PerryWerneck:pw3270/python-tn3270

Building the windows version
============================

Cross-compiling on SuSE Linux (Native or WSL)
---------------------------------------------


Compiling for Windows (With MSYS2)
----------------------------------

1. Install pw3270 with remote control and sdk modules

2. Build and install the "glue" library

	* Open a MSVC Native tools command prompt as administrator.
	* git clone  https://github.com/PerryWerneck/libipc3270.git ./ipc3270
	* cd ipc3270
	* install.bat

3. Get python-tn3270 sources from git

	* git clone https://github.com/PerryWerneck/python-tn3270.git ./python-tn3270

6. Build the extension using setup.py

	* cd python-tn3270
	* python setup.py build

7. Install extension

	* python setup.py install
	
8. Build windows installer (optional)

	* python setup.py bdist_wininst
