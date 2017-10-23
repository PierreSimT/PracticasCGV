

#include <cstdlib>
#include <stdio.h>
#include <math.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#include "cgvTriangleMesh.h"

#define PI 3.14159

// Constructors 

cgvTriangleMesh::cgvTriangleMesh(long int _num_vertices, float *_vertices, 
								 long int _num_triangles, unsigned int *_triangles,
								 bool _vertexArray, bool _includeNormals):vertexArray(_vertexArray), includeNormals(_includeNormals) {

	// TODO: Sections B, C and D: Create the mesh representing the octahedron. 
	//							Use vertices and triangles arrays adequately. 
}


cgvTriangleMesh::~cgvTriangleMesh() {

	if (vertices != NULL)
		delete[] vertices; 
	if (normals != NULL)
		delete[] normals; 
	if (triangles != NULL)
		delete[] triangles; 
}


// Public methods 

void cgvTriangleMesh::render(void) {

	/* TODO: Section B: Render triangle by triangle */

	
	/* TODO: Sections B, C, D: Render with a vertex array and 
	           add the array of normal vectors */

}

