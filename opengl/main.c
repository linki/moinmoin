// from: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=02
#include <stdlib.h>

#ifdef __APPLE__
   #include <OpenGL/gl.h>
   #include <OpenGL/glu.h>
   #include <GLUT/glut.h>
#else
   #include <GL/gl.h>
   #include <GL/glu.h>
   #include <GL/glut.h>
#endif

// Constants -----------------------------------------------------------------

#define kWindowWidth     512
#define kWindowHeight    256

// Function Prototypes -------------------------------------------------------

GLvoid InitGL(GLvoid);
GLvoid DrawGLScene(GLvoid);
GLvoid ReSizeGLScene(int Width, int Height);
GLvoid Idle(GLvoid);

// Global Variables ----------------------------------------------------------

GLfloat rtri;                   // Angle For The Triangle
GLfloat rquad;                  // Angle For The Quad

// Main ----------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(kWindowWidth, kWindowHeight);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);

   InitGL();

   glutDisplayFunc(DrawGLScene);
   glutReshapeFunc(ReSizeGLScene);
   glutIdleFunc(Idle);

   glutMainLoop();

   rtri  = 0;
   rquad = 0;

   return EXIT_SUCCESS;
}

// InitGL --------------------------------------------------------------------

GLvoid InitGL(GLvoid)
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // This Will Clear The Background Color To Black
   glClearDepth(1.0);                                   // Enables Clearing Of The Depth Buffer
   glDepthFunc(GL_LESS);                                // The Type Of Depth Test To Do
   glEnable(GL_DEPTH_TEST);                             // Enables Depth Testing
   glShadeModel(GL_SMOOTH);                             // Enables Smooth Color Shading

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();                                    // Reset The Projection Matrix

   gluPerspective(45.0f, (GLfloat)kWindowWidth / (GLfloat)kWindowHeight, 0.1f, 100.0f);
   
   // Calculate The Aspect Ratio Of The Window
   glMatrixMode(GL_MODELVIEW);
}

// Idle ----------------------------------------------------------------------

GLvoid Idle(GLvoid)
{
   rtri  += 0.2f;                   // Increase The Rotation Variable For The Triangle
   rquad -= 0.15f;                  // Decrease The Rotation Variable For The Quad

   glutPostRedisplay();
}

// DrawGLScene ---------------------------------------------------------------

GLvoid DrawGLScene(GLvoid)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // Clear The Screen And The Depth Buffer
   glLoadIdentity();                                            // Reset The View
   glTranslatef(-1.5f, 0.0f, -6.0f);                            // Move Left And Into The Screen

   glRotatef(rtri, 0.0f, 1.0f, 0.0f);                           // Rotate The Pyramid On It's Y Axis

   glBegin(GL_POLYGON);                                         // Start Drawing The Pyramid
   glColor3f(1.0f, 0.0f, 0.0f);                                 // Red
   glVertex3f(0.0f, 1.0f, 0.0f);                                // Top Of Triangle (Front)
   glColor3f(0.0f, 1.0f, 0.0f);                                 // Green
   glVertex3f(-1.0f, -1.0f, 1.0f);                              // Left Of Triangle (Front)
   glColor3f(0.0f, 0.0f, 1.0f);                                 // Blue
   glVertex3f(1.0f, -1.0f, 1.0f);                               // Right Of Triangle (Front)

   glColor3f(1.0f, 0.0f, 0.0f);                                 // Red
   glVertex3f(0.0f, 1.0f, 0.0f);                                // Top Of Triangle (Right)
   glColor3f(0.0f, 0.0f, 1.0f);                                 // Blue
   glVertex3f(1.0f, -1.0f, 1.0f);                               // Left Of Triangle (Right)
   glColor3f(0.0f, 1.0f, 0.0f);                                 // Green
   glVertex3f(1.0f, -1.0f, -1.0f);                              // Right Of Triangle (Right)

   glColor3f(1.0f, 0.0f, 0.0f);                                 // Red
   glVertex3f(0.0f, 1.0f, 0.0f);                                // Top Of Triangle (Back)
   glColor3f(0.0f, 1.0f, 0.0f);                                 // Green
   glVertex3f(1.0f, -1.0f, -1.0f);                              // Left Of Triangle (Back)
   glColor3f(0.0f, 0.0f, 1.0f);                                 // Blue
   glVertex3f(-1.0f, -1.0f, -1.0f);                             // Right Of Triangle (Back)

   glColor3f(1.0f, 0.0f, 0.0f);                                 // Red
   glVertex3f(0.0f, 1.0f, 0.0f);                                // Top Of Triangle (Left)
   glColor3f(0.0f, 0.0f, 1.0f);                                 // Blue
   glVertex3f(-1.0f, -1.0f, -1.0f);                             // Left Of Triangle (Left)
   glColor3f(0.0f, 1.0f, 0.0f);                                 // Green
   glVertex3f(-1.0f, -1.0f, 1.0f);                              // Right Of Triangle (Left)
   glEnd();                                                     // Done Drawing Pyramid

   glLoadIdentity();
   glTranslatef(1.5f, 0.0f, -7.0f);                             // Move Right And Into The Screen

   glRotatef(rquad, 1.0f, 1.0f, 1.0f);                          // Rotate The Cube On X, Y & Z

   glBegin(GL_QUADS);                                           // Start Drawing The Cube
   glColor3f(0.0f, 1.0f, 0.0f);                                 // Set The Color To Blue
   glVertex3f(1.0f, 1.0f, -1.0f);                               // Top Right Of The Quad (Top)
   glVertex3f(-1.0f, 1.0f, -1.0f);                              // Top Left Of The Quad (Top)
   glVertex3f(-1.0f, 1.0f, 1.0f);                               // Bottom Left Of The Quad (Top)
   glVertex3f(1.0f, 1.0f, 1.0f);                                // Bottom Right Of The Quad (Top)

   glColor3f(1.0f, 0.5f, 0.0f);                                 // Set The Color To Orange
   glVertex3f(1.0f, -1.0f, 1.0f);                               // Top Right Of The Quad (Bottom)
   glVertex3f(-1.0f, -1.0f, 1.0f);                              // Top Left Of The Quad (Bottom)
   glVertex3f(-1.0f, -1.0f, -1.0f);                             // Bottom Left Of The Quad (Bottom)
   glVertex3f(1.0f, -1.0f, -1.0f);                              // Bottom Right Of The Quad (Bottom)

   glColor3f(1.0f, 0.0f, 0.0f);                                 // Set The Color To Red
   glVertex3f(1.0f, 1.0f, 1.0f);                                // Top Right Of The Quad (Front)
   glVertex3f(-1.0f, 1.0f, 1.0f);                               // Top Left Of The Quad (Front)
   glVertex3f(-1.0f, -1.0f, 1.0f);                              // Bottom Left Of The Quad (Front)
   glVertex3f(1.0f, -1.0f, 1.0f);                               // Bottom Right Of The Quad (Front)

   glColor3f(1.0f, 1.0f, 0.0f);                                 // Set The Color To Yellow
   glVertex3f(1.0f, -1.0f, -1.0f);                              // Top Right Of The Quad (Back)
   glVertex3f(-1.0f, -1.0f, -1.0f);                             // Top Left Of The Quad (Back)
   glVertex3f(-1.0f, 1.0f, -1.0f);                              // Bottom Left Of The Quad (Back)
   glVertex3f(1.0f, 1.0f, -1.0f);                               // Bottom Right Of The Quad (Back)

   glColor3f(0.0f, 0.0f, 1.0f);                                 // Set The Color To Blue
   glVertex3f(-1.0f, 1.0f, 1.0f);                               // Top Right Of The Quad (Left)
   glVertex3f(-1.0f, 1.0f, -1.0f);                              // Top Left Of The Quad (Left)
   glVertex3f(-1.0f, -1.0f, -1.0f);                             // Bottom Left Of The Quad (Left)
   glVertex3f(-1.0f, -1.0f, 1.0f);                              // Bottom Right Of The Quad (Left)

   glColor3f(1.0f, 0.0f, 1.0f);                                 // Set The Color To Violet
   glVertex3f(1.0f, 1.0f, -1.0f);                               // Top Right Of The Quad (Right)
   glVertex3f(1.0f, 1.0f, 1.0f);                                // Top Left Of The Quad (Right)
   glVertex3f(1.0f, -1.0f, 1.0f);                               // Bottom Left Of The Quad (Right)
   glVertex3f(1.0f, -1.0f, -1.0f);                              // Bottom Right Of The Quad (Right)
   glEnd();                                                     // Done Drawing The Quad

   glutSwapBuffers();
   glFlush();
}

// ReSizeGLScene ------------------------------------------------------------

GLvoid ReSizeGLScene(int Width, int Height)
{
   glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(45.0, (GLfloat)Width / (GLfloat)Height, 0.1, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
