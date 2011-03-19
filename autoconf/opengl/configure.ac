#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADER([config.h])

# if local
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

AX_CHECK_GL
AX_CHECK_GLU
AX_CHECK_GLUT

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
