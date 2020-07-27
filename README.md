This is the Community Sensor Model base interface library.

[![Powered by NumFOCUS](https://img.shields.io/badge/powered%20by-NumFOCUS-orange.svg?style=flat&colorA=E1523D&colorB=007D8A)](http://numfocus.org)

About csm
=========

Compilation using make
----------------------
The CSM library can be compiled on Linux (tested on RHEL5) i386, x86_64, or IA-64, Solaris SPARC (32 or 64 bit, with or without the "stlport" mode) and x86, and Windows.  Use the appropriate Makefile when building.  For example:

    make -f Makefile.linux64 all install clean

By default, the built files are placed in an architecture subdirectory in the build area.  This allows multiple architectures to be built.  To specify a different installation directory, set the INSTDIR make variable:

    make -f Makefile.linux64 all install clean INSTDIR=/path/to/csm3/install/dir

Compiling makes a 'csmapi' shared library (libcsmapi.so.3.1.0 on UNIX, csmapi.dll on Windows).  This library must be used when creating both CSM plugins and Sensor Exploitation Tools (SETs) that use CSM.

Building CSM Cmake
------------------
This repo uses a CMake based build configuration. Run CMake with the desired configurations and generator to configure your build. Then, run your build system or use cmake. For example:

```
mkdir build install
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=../install ..
cmake --build . --target install
```

will build the library in your `build` directory and install it and the headers into your `install` directory.

Windows
-------
Windows compilation requires the use of Cygwin to provide tools like 'make' and 'perl'.  You should also be sure that Microsoft's Visual C++'s "cl.exe" is in your $PATH and that $INCLUDE and $LIB are set appropriately.  When compiling on Windows, the "all" target does not do the right thing.  Instead build with:

    make -f Makefile.win32 csmapi.dll install clean

Package license: Public Domain

Feedstock license: BSD 3-Clause

Current build status
====================
[![Linux](https://img.shields.io/circleci/project/github/conda-forge/csm-feedstock/master.svg?label=Linux)](https://circleci.com/gh/conda-forge/csm-feedstock)
[![OSX](https://img.shields.io/travis/conda-forge/csm-feedstock/master.svg?label=macOS)](https://travis-ci.org/conda-forge/csm-feedstock)
[![Windows](https://img.shields.io/appveyor/ci/conda-forge/csm-feedstock/master.svg?label=Windows)](https://ci.appveyor.com/project/conda-forge/csm-feedstock/branch/master)

Current release info
====================

| Name | Downloads | Version | Platforms |
| --- | --- | --- | --- |
| [![Conda Recipe](https://img.shields.io/badge/recipe-csm-green.svg)](https://anaconda.org/conda-forge/csm) | [![Conda Downloads](https://img.shields.io/conda/dn/conda-forge/csm.svg)](https://anaconda.org/conda-forge/csm) | [![Conda Version](https://img.shields.io/conda/vn/conda-forge/csm.svg)](https://anaconda.org/conda-forge/csm) | [![Conda Platforms](https://img.shields.io/conda/pn/conda-forge/csm.svg)](https://anaconda.org/conda-forge/csm) |

Installing csm via conda
========================

Installing `csm` from the `conda-forge` channel can be achieved by adding `conda-forge` to your channels with:

```
conda config --add channels conda-forge
```

Once the `conda-forge` channel has been enabled, `csm` can be installed with:

```
conda install csm
```

It is possible to list all of the versions of `csm` available on your platform with:

```
conda search csm --channel conda-forge
```
