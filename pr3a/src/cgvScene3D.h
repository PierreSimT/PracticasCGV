#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#include "cgvTriangleMesh.h"

#define nbScenes 4

class cgvScene3D {
	public: 
		int Scene[nbScenes]; 
		char *Scene_Name[nbScenes]; 

	protected:
		// TODO: Section A: Define the attributes for interaction
		

		bool axes;
		int sceneSelected; 

		cgvTriangleMesh *mesh; // mesh of triangles associated with the scene

	public:
		// Public attributes

		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		void set(int scene); 

		// Methods
		// method with the OpenGL calls to render the scene
    void render();

		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};

		// TODO: Section A: Implement the methods to rotate the scene w.r.t the axes. 

protected: 
	    void setOctahedronWithMeshes(bool vertexArray, bool withNormals);

};

#endif
