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
	
	public: 
		const int SceneA = 1;
		const int SceneB = 2;

		const char *SceneA_Name = "Scene A"; 
		const char *SceneB_Name = "Scene B"; 

	protected:
		// Attributes
		
		bool axes;



	public:
		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		// Methods
		// method with the OpenGL calls to render the scene
	    void render(int scene);

		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};

protected:
	void renderSceneA();
	void renderSceneB();
};

#endif
