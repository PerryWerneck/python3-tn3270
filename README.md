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

1. Install python and python devel

2. Build and install lib3270 

	* Follow the guide on https://github.com/PerryWerneck/lib3270

3. Build and install libv3270 

	* Follow the guide on https://github.com/PerryWerneck/libv3270

4. Build and install libipc3270 

	* Follow the guide on https://github.com/PerryWerneck/libipc3270

5. Get python-tn3270 sources from git

	* git clone https://github.com/PerryWerneck/python-tn3270.git ./python-tn3270

6. Build the extension using setup.py

	* cd python-tn3270
	* python setup.py build

7. Install extension

	* python setup.py install
	

