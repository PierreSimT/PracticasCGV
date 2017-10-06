#include <cstdlib>
#include <stdio.h>

#include "cgvInterface.h"

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface ():currentCam(0), camType(CGV_PARALLEL) {

	camera[0] = cgvCamera(cgvPoint3D(3.0, 2.0, 4), cgvPoint3D(0, 0, 0), cgvPoint3D(0, 1.0, 0));
	camera[0].setPerspParameters( 60, 1, 1.0, 6.0 );
	camera[0].setParallelParameters(1 * 3, 1 * 3, 0.1, 200);


	// TODO: Practice 2B.b: Define top, lateral and front cameras, respectively
	camera[1] = cgvCamera( cgvPoint3D(0, 5.0, 0), cgvPoint3D(0, 0, 0), cgvPoint3D(1,0,0 ));
	camera[1].setPerspParameters( 60, 1, 1.0, 6.0 );
	camera[1].setParallelParameters(3,3,0.1,200);
	
	camera[2] = cgvCamera( cgvPoint3D(5.0, 0, 0), cgvPoint3D(0,0,0), cgvPoint3D(0,1,0));
	camera[2].setParallelParameters(3,3,0.1,200);
	camera[2].setParallelParameters(1 * 3, 1 * 3, 0.1, 200);

	camera[3] = cgvCamera( cgvPoint3D(0, 0, 5.0), cgvPoint3D(0,0,0), cgvPoint3D(0,1,0));
	camera[3].setParallelParameters(3,3,0.1,200);
	camera[3].setParallelParameters(1 * 3, 1 * 3, 0.1, 200);
}

cgvInterface::~cgvInterface () {}


// Public methods ----------------------------------------
void cgvInterface::configure_environment(int argc, char** argv,
			                       int _width_window, int _height_window,
			                       int _pos_X, int _pos_Y, const char* _title)
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

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
  glClearColor(1.0,1.0,1.0,0.0); // define the background color of the window

	glEnable(GL_LIGHTING); // enable the lighting of the scene
  glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation.

}

void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
    case 'p': // change the type of projection between parallel and perspective. See the attribute camType;
		switch (interface.camType) 
		{
			case CGV_PARALLEL:	
				interface.camType = CGV_PERSPECTIVE;
				double fov, asp, neara, fara;
				interface.camera[interface.currentCam].getPerspParameters (fov, asp, neara, fara);
				interface.camera[interface.currentCam].setPerspParameters( fov, asp, neara, fara );
				interface.camera[interface.currentCam].apply();
				break;
			case CGV_PERSPECTIVE:
				interface.camType = CGV_PARALLEL;
				double wmin,wmax,ymin,ymax,near,far;
    			interface.camera[interface.currentCam].getParallelParameters( wmin, wmax, ymin, ymax, near, far );
    			interface.camera[interface.currentCam].setParallelParameters( wmax, ymax, near, far );
				interface.camera[interface.currentCam].apply();
				break;
		}

		break;
    case 'v': // change the current camera to show these views: panoramic, top, front and lateral view
			interface.currentCam = (interface.currentCam + 1)%4;
			interface.camera[interface.currentCam].apply();
	  break;
    case '+': // zoom in
    	interface.camera[interface.currentCam].zoom(1.05);
		break;
    case '-': // zoom out
    	interface.camera[interface.currentCam].zoom(0.95);
	  break;
    case 'n': // increment the distance to the near plane
    	switch ( interface.currentCam ) {
    		case CGV_PARALLEL:
				double wmin,wmax,ymin,ymax,near,far;
    			interface.camera[interface.currentCam].getParallelParameters( wmin, wmax, ymin, ymax, near, far );
    			interface.camera[interface.currentCam].setParallelParameters( wmax, ymax, near+0.2, far );
    			interface.camera[interface.currentCam].apply();
    			break;
    		case CGV_PERSPECTIVE:
    			double fov, asp, neara, fara;
				interface.camera[interface.currentCam].getPerspParameters (fov, asp, neara, fara);
				interface.camera[interface.currentCam].setPerspParameters( fov, asp, neara+0.2, fara );
    	} 
	  break;
    case 'N': // decrement the distance to the near plane
    		switch ( interface.currentCam ) {
    		case CGV_PARALLEL:
				double wmin,wmax,ymin,ymax,near,far;
    			interface.camera[interface.currentCam].getParallelParameters( wmin, wmax, ymin, ymax, near, far );
    			interface.camera[interface.currentCam].setParallelParameters( wmax, ymax, near-0.2, far );
    			interface.camera[interface.currentCam].apply();
    			break;
    		case CGV_PERSPECTIVE:
    			double fov, asp, neara, fara;
				interface.camera[interface.currentCam].getPerspParameters (fov, asp, neara, fara);
				interface.camera[interface.currentCam].setPerspParameters( fov, asp, neara-0.2, fara );
    	} 
	  break;
	  break;
    case '9': // change to format 16:9 with deformation

	  break;
    case 'a': // enable/disable the visualization of the axes
			interface.scene.set_axes(!interface.scene.get_axes());
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

  // set up the viewport
  glViewport(0, 0, interface.get_width_window(), interface.get_height_window());

  // Set up the kind of projection to be used
  interface.camera[interface.currentCam].apply();

}

void cgvInterface::set_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, interface.get_width_window(), interface.get_height_window());

	// Set up the kind of projection to be used
	interface.camera[interface.currentCam].apply();

	// Render the scene
	interface.scene.render();

	// refresh the window
	glutSwapBuffers(); // it is used instead of glFlush() to avoid flickering

}

void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
}
