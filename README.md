This is the Community Sensor Model base interface library.

Compilation
-----------
The CSM library uses `cmake` for compilation.  You can build directly in the source area, but it may be better to build in a separate build directory.  For example,

```
mkdir linux7_64
cd linux7_64
cmake -DCMAKE_INSTALL_PREFIX:PATH=$PWD ..
make all install clean
```

or for 32 bit:

```
mkdir linux7_32
cd linux7_32
cmake -DCMAKE_INSTALL_PREFIX:PATH=$PWD -DCMAKE_CXX_FLAGS=-m32 ..
make all install clean
```

Compiling makes a 'csmapi' shared library (libcsmapi.so.3.0.3 on UNIX, csmapi.dll on Windows).  This library must be used when creating both CSM plugins and Sensor Exploitation Tools (SETs) that use CSM.


Windows
-------
Windows compilation requires the use of Cygwin to provide tools like 'make' and 'perl'.  You should also be sure that Microsoft's Visual C++'s "cl.exe" is in your $PATH and that $INCLUDE and $LIB are set appropriately.  When compiling on Windows, the "all" target does not do the right thing.  Instead build with:

  make -f Makefile.win32 csmapi.dll install clean
