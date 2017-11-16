#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"
#include "cgvTriangleMesh.h"


static GLfloat black[]={0, 0, 0, 0};
// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D ():sceneSelected(1), mesh(NULL)
{
	Scene[0] = 1; 
	Scene[1] = 2; 
	Scene[2] = 3; 
	Scene[3] = 4; 
	

	Scene_Name[0] = "Octahedron"; 
	Scene_Name[1] = "OctahedronWithMeshes"; 
	Scene_Name[2] = "OctahedronWithMeshesVertexArray"; 
	Scene_Name[3] = "OctahedronWithMeshesVertexArrayandNormals"; 



	// TODO: Section A: Define the initial values of the interaction attributes. 
	X = 0;
	Y = 0;
	Z = 0;
	axes = true;

}

cgvScene3D::~cgvScene3D() {
	if (mesh != NULL) delete mesh; 
}


// Public methods ----------------------------------------



void 
cgvScene3D::set(int scene) {
	if (scene == sceneSelected) return; 

	//if (mesh!=NULL) delete mesh; 

	switch (scene) {
	case 1: //Initial Octahedron
		break; 
	case 2: setOctahedronWithMeshes(false, false); break; 
	case 3: setOctahedronWithMeshes(true, false); break; 
	case 4: setOctahedronWithMeshes(true, true); break;
	};

	sceneSelected = scene; 
}

void cgvScene3D::setX(float X)
{
	this->X += X;
}

void cgvScene3D::setY(float Y)
{
	this->Y += Y;
}

void cgvScene3D::setZ(float Z)
{
	this->Z += Z;
}

void
cgvScene3D::setOctahedronWithMeshes(bool vertexArray, bool withNormals) {

	// TODO: Sections B, C and D: insert here the code to create a mesh equivalent to the octahedron. 
	//       Use the appropriate constructor of cgvTriangleMesh.

	long int num_vertices; // number of vertices of the mesh of triangles
	long int num_triangles; // number of triangles in the mesh

	float vertex[] = { 0, 1, 0 ,
						0,0,1 ,
						-1,0,0 ,
						0,0,-1 ,
						1,0,0 ,
						0,-1,0 };

	unsigned char index[] ={0,1,4,
							1,5,4,
							0,2,1,
							2,5,1,
							0,3,2,
							3,5,2,
							0,4,3,
							4,5,3 };
	
	num_vertices = 6;
	num_triangles = 8;

	mesh = new cgvTriangleMesh(num_vertices, vertex, num_triangles, index, vertexArray, withNormals);
}


void draw_axes(void) {
  GLfloat red[]={1,0,0,1.0};
  GLfloat green[]={0,1,0,1.0};
  GLfloat blue[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,red);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();

}


void cgvScene3D::render(void) {
	// TODO: include in this method the code to apply the corresponding rotations. 

	GLfloat mesh_color[]={0,0.25,0};

	// lights
	GLfloat light0[]={5,5,5,1}; // point light source
	glLightfv(GL_LIGHT0,GL_POSITION,light0); // this light is placed here and it remains still 
	glEnable(GL_LIGHT0);
  
  	glShadeModel(GL_FLAT);
	//glShadeModel(GL_SMOOTH);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

 		//glLightfv(GL_LIGHT0,GL_POSITION,light0); // the light is placed here and it moves with the scene
	  glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

		// Section A: next call should be substituted by the new method to render the mesh
		glRotatef(X, 1, 0, 0);
		glRotatef(Y, 0, 1, 0);
		glRotatef(Z, 0, 0, 1);
	  if (sceneSelected == 1) {
		glutSolidOctahedron();
	  }
	  else {
			mesh->render(); 
	  }
		

	glPopMatrix (); // restore the modelview matrix 
  
}

