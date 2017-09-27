#ifndef __CGVINTERFACE
#define __CGVINTERFACE

#include <GL/glut.h>
#include <string>

using namespace std;

class cgvInterface {
	protected:
		// Attributes
		int width_window; // initial width of the display window
		int height_window;  // initial height of the display window
		
		// TODO: Practice 1: Declare the boolean variable to control whether the axes are visualized or not.  
		bool axes;
	public:
		// Default constructor and destructor
		cgvInterface();
		~cgvInterface();

		// Static methods
		// event callbacks
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // method to control keyboard events
		static void set_glutReshapeFunc(int w, int h); // method to define the camera and the viewport
		                                               // it is automatically called when the window is resized
		static void set_glutDisplayFunc(); // method to render the scene


		// Methods
		// initialize all the parameters to create a display window
		void configure_environment(int argc, char** argv, // main parameters
			                       int _width_window, int _height_window, // width and height of the display window
			                       int _pos_X, int _pos_Y, // init position of the display window
													 string _title // title of the display window
													 ); 
		void init_callbacks(); // init all the callbacks

		void init_rendering_loop(); // render the scene and wait for an event in the interface

		// methods get_ and set_ to access the attributes
		int get_width_window(){return width_window;};
		int get_height_window(){return height_window;};

		void set_width_window(int _width_window){width_window = _width_window;};
		void set_height_window(int _height_window){height_window = _height_window;};
		
		// TODO: practice 1: specify the corresponding methods get_axes() and set_axes() to get the value of the boolean variable axes and to set it, respctively.  
		void setAxes (bool axes) { this->axes = axes; };
		bool getAxes() { return this->axes; };
};

#endif
