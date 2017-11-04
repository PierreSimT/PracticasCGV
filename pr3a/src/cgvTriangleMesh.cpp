

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
								 long int _num_triangles, unsigned char *_triangles,
								 bool _vertexArray, bool _includeNormals):vertexArray(_vertexArray), includeNormals(_includeNormals) {

	// TODO: Sections B, C and D: Create the mesh representing the octahedron. 
	//							Use vertices and triangles arrays adequately. 
	num_triangles = _num_triangles;
	num_vertices = _num_vertices;

	vertices = new float[num_vertices * 3];
	for (int i = 0; i < num_vertices * 3; i++) {
		vertices[i] = _vertices[i];
	}

	triangles = new unsigned char[num_triangles * 3];
	for (int i = 0; i < num_triangles * 3; i++) {
		triangles[i] = _triangles[i];
	}

	float normal[] = {  0,0,1,
						1,0,0,
						0,0,1,
						1,0,0,
						0,0,1, 
						0,0,1};

	normals = new float[num_vertices*3];
	for (int i = 0; i < num_vertices * 3; i++) {
		normals[i] = normal[i];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, triangles);
	glDisableClientState(GL_VERTEX_ARRAY);
}


cgvTriangleMesh::~cgvTriangleMesh() {

	if (vertices != NULL)
		delete[] vertices; 
	if (normals != NULL)
		delete normals; 
	if (triangles != NULL)
		delete triangles; 
}


// Public methods 
void cgvTriangleMesh::render(void) {

	/* TODO: Section B: Render triangle by triangle */
	if (!vertexArray) {
		int cont = 0;
		for (int i = 0; i < num_triangles; i++) {
				glBegin(GL_TRIANGLES);
				glVertex3f(vertices[triangles[cont] * 3], vertices[triangles[cont] * 3 + 1], vertices[triangles[cont] * 3 + 2]);
				cont++;
				glVertex3f(vertices[triangles[cont] * 3], vertices[triangles[cont] * 3 + 1], vertices[triangles[cont] * 3 + 2]);
				cont++;
				glVertex3f(vertices[triangles[cont] * 3], vertices[triangles[cont] * 3 + 1], vertices[triangles[cont] * 3 + 2]);
				cont++;
				glEnd();			
		}
	}
	


	/* TODO: Sections B, C, D: Render with a vertex array and 
	           add the array of normal vectors */
	if ( vertexArray ) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, triangles);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	else if (vertexArray && includeNormals) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, normals);

		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, triangles);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

