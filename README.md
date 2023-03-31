# FreeMat


### Installation of Python2 is necessary because it is based on Python 2 
### Work in progress to shift to python3
Here are some general instructions on building FreeMat from scratch on various platforms. 

*******************************************************************************

Fedora:
```sh
yum install cmake
yum install qt4 qt4-devel portaudio-devel atlas-devel atlas
yum install ufsparse-devel fftw-devel llvm-devel pcre-devel gcc-c++ libffi-devel
yum install ncurses-devel clang-devel rpm-build
yum install arpack-devel lapack-devel
```
(this doesn't include VTK).

Ubuntu 20.04 :

In Root: 
```sh
apt install cmake
add-apt-repository ppa:rock-core/qt4  #for Ubuntu 20.04
apt install qt4-dev-tools libqt4-dev 
apt install portaudio19-dev/libasound-dev libatlas-base-dev libatlas3-base
apt install libsuitesparse-dev libfftw3-dev llvm-dev libpcre3-dev libffi-dev
apt install lib64ncurses-dev libclang-dev libopencl-clang-dev librpm-dev
apt install libparpack2-dev libarpack2-dev liblapack-dev
apt install python2 
```
Ubuntu 22.04 :

In Root: 
```sh
apt install cmake
add-apt-repository ppa:ubuntuhandbook1/ppa #for Ubuntu 22.04 works for 20.04 also
apt install qt4-dev-tools libqt4-dev 
apt install portaudio19-dev/libasound-dev libatlas-base-dev libatlas3-base
apt install libsuitesparse-dev libfftw3-dev llvm-dev libpcre3-dev libffi-dev
apt install lib64ncurses-dev libclang-dev libopencl-clang-dev librpm-dev
apt install libparpack2-dev libarpack2-dev liblapack-dev
apt install python2 
```


At the moment, LLVM and CLANG do not install correctly in Fedora/Ubuntu.  So
you will have to build them.  Make a build directory somewhere.

```sh
mkdir build
cd build
```
Create a subdirectory for the unfound dependencies (LLVM and CLANG in
this case).  If you name it "deps", you won't have to change any variables later.

```sh
mkdir deps
cd deps
```
Configure with the FreeMat dependencies script

```sh
cmake <Path to freemat source>/tools/dependencies
make
```
This will download and build LLVM and CLANG into a local directory.

Then, from the "build" directory, do

```sh
cmake <Path to freemat source>
make
```

And it should build.

********************************************************************************
Not Tested For Windows
Windows 64/Fedora cross

Install the cross compiling dependencies.

```sh
yum install mingw64-gcc-c++ mingw64-gcc mingw64-qt mingw64-pcre
yum install mingw64-libffi-static mingw64-gcc-gfortran
yum install mingw32-nsiswrapper
yum install wine
```
Build the dependencies

```sh
mkdir build
cd build
```
```sh
mkdir deps
cd deps
```
```sh
cmake -DCMAKE_TOOLCHAIN_FILE=<Path to freemat
source>/cmake/Toolchain-cross-mingw64-fedora-linux <path to freemat>/tools/dependencies
```
********************************************************************************

Windows 32/Fedora cross

Install the cross compiling dependencies.

```sh
yum install mingw32-gcc-c++ mingw32-gcc mingw32-qt mingw32-pcre
yum install mingw32-libffi-static mingw32-gcc-gfortran
```
Build the dependencies

```sh
mkdir build
cd build
```
```sh
mkdir deps
cd deps
```

```sh
cmake -DCMAKE_TOOLCHAIN_FILE=<Path to freemat
source>/cmake/Toolchain-cross-mingw32-fedora-linux <path to freemat>/tools/dependencies
```
********************************************************************************
Not Tested For Mac
Mac native

Install brew

brew install qt cmake autoconf automake gfortran portaudio doxygen 

