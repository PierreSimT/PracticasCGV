#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

class cgvScene3D {
	protected:
		// Attributes

		bool axes;

	public:
		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
    void render();

		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};
};

#endif
