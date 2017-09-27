

#include "cgvInterface.h"

#include <cstdlib>

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface ():menuSelection(scene.SceneA) {}

cgvInterface::~cgvInterface () {}


// Public methods ----------------------------------------

void cgvInterface::configure_environment(int argc, char** argv, 
			                       int _width_window, int _height_window, 
			                       int _pos_X, int _pos_Y, 
													 char *_title)
													 {
	// initialization of the interface variables																	
	width_window = _width_window;
	height_window = _height_window;
        
	// initialization of the display window
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_width_window,_height_window);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_title);

	create_menu();

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
  glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation. 

}

void cgvInterface::create_menu() {
	int menu_id = glutCreateMenu(menuHandle);
	glutAddMenuEntry(interface.scene.SceneA_Name, interface.scene.SceneA);
	glutAddMenuEntry(interface.scene.SceneB_Name, interface.scene.SceneB);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'a': // enable/disable the visualization of the axes
			interface.scene.set_axes(interface.scene.get_axes()?false:true);

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

	glOrtho(-1*5,1*5,-1*5,1*5,-1*5,200);

  // it defines the camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  	gluLookAt(1.5,1.0,2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // initial view
  //gluLookAt(1.5,0,0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // view of the plant from the positive X axis

}

void cgvInterface::set_glutDisplayFunc() {
	interface.scene.render(interface.menuSelection);
}

void cgvInterface::menuHandle(int value)
{
	interface.menuSelection = value; 
	glutPostRedisplay(); // renew the content of the window
}

void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
