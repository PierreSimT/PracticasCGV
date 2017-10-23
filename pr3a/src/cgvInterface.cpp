#include <cstdlib>
#include <stdio.h>

#include "cgvInterface.h"

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface ():camType(CGV_PARALLEL) {
	camera = cgvCamera(cgvPoint3D(3.0, 2.0, 4), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0),
		1 * 3, 1 * 3, 0.1, 200);
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

	create_menu();

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
  glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation. 

}

void cgvInterface::create_menu() {
	int menu_id = glutCreateMenu(menuHandle);
	for (int i=0;i<nbScenes;++i) {
		glutAddMenuEntry(interface.scene.Scene_Name[i], interface.scene.Scene[i]);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'x': // TODO: Section A: rotate positive X 
		break;
    case 'X': // TODO: Section A: rotate negative X  
		break;
    case 'y': // TODO: Section A: rotate positive Y 
		break;
    case 'Y': // TODO: Section A: rotate negative Y 
		break;
    case 'z': // TODO: Section A: rotate positive Z 
		break;
    case 'Z': // TODO: Section C: rotate negative Z 
		break; 
		
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


  // store the new values of the viewport and the display window. 
  interface.set_width_window(w);
  interface.set_height_window(h);

  // Set up the kind of projection to be used
  interface.camera.apply(interface.camType);

}

void cgvInterface::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, interface.get_width_window(), interface.get_height_window());
	// Apply the camera and projection parameters
	interface.camera.apply(interface.camType);

	// Render the scene
	interface.scene.render();

	// refresh the window
	glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering
	
}

void cgvInterface::menuHandle(int value)
{
	interface.scene.set(value);  
	glutPostRedisplay(); // renew the content of the window
}


void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
