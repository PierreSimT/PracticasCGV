#include <cstdlib>

#include "cgvInterface.h"

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface () {
	// TODO: Practice 1: Initialize the variable 'axes' to TRUE.
	this->setAxes(true);
}

cgvInterface::~cgvInterface () {}


// Public methods ----------------------------------------

void cgvInterface::configure_environment(int argc, char** argv,
			                       int _width_window, int _height_window,
			                       int _pos_X, int _pos_Y,
													 string _title)
													 {
	// initialization of the interface variables
	width_window = _width_window;
	height_window = _height_window;

	// initialization of the display window
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_width_window,_height_window);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_title.c_str());

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

}

void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
// TODO: practice 1: Add the code to enable/disable the visualization of the axes after pressing 'a'.
	case 97:
		if (interface.getAxes()) interface.setAxes(false);
			else interface.setAxes(true);
		break;
    case 27: // Escape key to exit
      exit(1);
    break;
  }
	glutPostRedisplay(); // renew the content of the window
}

void cgvInterface::set_glutReshapeFunc(int w, int h) {
  // dimension of the viewport with a new width and a new height of the display window
  glViewport(0,0,(GLsizei) w,(GLsizei) h);

  // store the new values of the viewport and the display window.
  interface.set_width_window(w);
  interface.set_height_window(h);

  // Set up the kind of projection to be used
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-1,1,-1,1,-1,200);

  // it defines the camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void cgvInterface::set_glutDisplayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the depth buffer
  glPushMatrix(); // store the model matrix

  // TODO: Practice 1: Draw the axis
	// Test
  if (interface.getAxes())
  {
	  glBegin(GL_LINES);

		  glColor3f(1.0f, 0.0f, 0.0f); // X Axis (RED)
		  glVertex3f(-100.0f, 0.0f, 0.0f);
		  glVertex3f(100.0f, 0.0f, 0.0f);

		  glColor3f(0.0f, 1.0f, 0.0f); // Y Axis (GREEN)
		  glVertex3f(0.0f, -100.0f, 0.0f);
		  glVertex3f(0.0f, 100.0f, 0.0f);

		  glColor3f(0.0f, 0.0f, 1.0f); // Z Axis (BLUE)
		  glVertex3f(0.0f, 0.0f, -100.0f);
		  glVertex3f(0.0f, 0.0f, 100.0f);

	  glEnd();
  }
  // TODO: Practice 1: draw the object of the scene

  glColor3f(0.0f, 0.0f, 0.0f);
  glutWireCube(1.0f);

  glPopMatrix (); // restore the model matrix
  glutSwapBuffers(); // it is used instead of glFlush(), in case of double buffer, to avoid flickering
}

void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
