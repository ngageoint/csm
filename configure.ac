AC_PREREQ([2.69])
AC_INIT([csm], [3.1.0])
AC_CONFIG_SRCDIR([Version.cpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIRS([m4])
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_PROG_AR

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_INSTALL
LT_INIT([disable-static shared])

AC_CHECK_PROGS([DOXYGEN], [doxygen], [:])
AC_CHECK_LIB([dl], [dlopen], [DL_LIBS="-ldl"], [DL_LIBS=""])
AC_SUBST([DL_LIBS])

AC_ARG_ENABLE([legacy-cxx11-abi],
  [AS_HELP_STRING([--enable-legacy-cxx11-abi],
    [build with -D_GLIBCXX_USE_CXX11_ABI=0 for compatibility with historical Linux builds])],
  [enable_legacy_cxx11_abi="$enableval"],
  [enable_legacy_cxx11_abi="no"])
AM_CONDITIONAL([ENABLE_LEGACY_CXX11_ABI], [test "x$enable_legacy_cxx11_abi" = "xyes"])

case "$host_os" in
  linux*)
    AC_DEFINE(
      [LINUX_BUILD],
      [1],
      [Define when building on Linux so exported symbols use ELF visibility attributes.]
    )
    ;;
esac

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
