#ifndef __CGVTRIANGLEMESH
#define __CGVTRIANGLEMESH

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


class cgvTriangleMesh {
	protected:
		// Attributes
		long int num_vertices; // number of vertices of the mesh of triangles
		float *vertices; // array with (num_vertices * 3) coordinates of the vertices
		float *normals; // array with (num_vertices * 3) coordinates of the normal vector to each vertex 
		long int num_triangles; // number of triangles in the mesh
		unsigned char *triangles; // array with (num_triangles * 3) indexes and vertices of each triangle array 

		bool vertexArray; // Use or not of vertex arrays. 
		bool includeNormals; // Include or not normals to improve realism. 

	public:
		// Constructor and destructor
		// Section B: constructor of the mesh of triangles
		cgvTriangleMesh(long int _num_vertices, float *_vertices, 
						long int _num_triangles, unsigned char *_triangles,
						bool _vertexArray, bool _includeNormals);
    
                                    

		~cgvTriangleMesh();

		// Methods
		// method with the OpenGL calls to render the mesh of triangles
    void render();


};

#endif
