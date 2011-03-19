# in /usr/share/aclocal/ in my mac
# homebrew: sudo ln -s /usr/local/share /usr/share/aclocal
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS=main
main_SOURCES=main.c

AM_CFLAGS=$(GL_FLAGS) $(GLU_FLAGS) $(GLUT_FLAGS)
AM_LDFLAGS=$(GL_LIBS) $(GLU_LIBS) $(GLUT_LIBS)