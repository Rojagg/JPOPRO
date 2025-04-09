#PROJECT JPO - Szymon Półgęsek

#APPLICATION TO MONITOR AIR QUALITY IN POLAND
_______________________________________________________________________________

##REQUIERMENTS
- C++ version 17 or newer
- CMAKE
- vcpkg
______________________________________________________________________________

##Setup on Windows - step by step

1. Install vcpkg 
	- type in CMD:
																					
	git clone https://github.com/Microsoft/vcpkg.git
	cd vcpkg
	./bootstrap-vcpkg.sh


2. Add vcpkg to enviroment varaibales
	- add user variable named: "VCPKG_ROOT" with path: C:\Path\To\vcpkgDirectory\vcpkg
	- add above varaible to user Varaiable named "PATH"

3. Add vcpkg path to "CMakeUserPresets.json"
	- set environment["VCPKG_ROOT"] to: C:\Path\To\vcpkgDirectory\vcpkg

4. Install packages

	- type in cmd:

	./vcpkg install

 ______________________________________________________________________________

