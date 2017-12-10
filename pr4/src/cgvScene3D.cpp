#include <stdlib.h>
#include <stdio.h>

#include "cgvScene3D.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvTexture.h"

// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D () {
	axes = true;

	Scene[0] = 1;
	Scene[1] = 2;
	Scene[2] = 3;
	Scene[3] = 4;
	Scene[4] = 5;

	Scene_Name[0] = "blue quad";
	Scene_Name[1] = "red quad";
	Scene_Name[2] = "mesh of quads";
	Scene_Name[3] = "spotlight";
	Scene_Name[4] = "texture";

	selectedScene = 1; 

	Rd = new cgvColor (0.5, 0, 0);
	Rs = new cgvColor (0.5, 0, 0);
	matNs = 120;

	xPosition = 3.0;
	yPosition = 1.0;

}

cgvScene3D::~cgvScene3D() {

}


// Public methods ----------------------------------------

void
cgvScene3D::set(int scene) {
	selectedScene = scene;
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

void draw_quad(float div_x, float div_z) {
	float ini_x = 0.0;
	float ini_z = 0.0;
	float size_x = 5.0;
	float size_z = 5.0;

	glNormal3f(0, 1, 0);

	float jumpX = size_x / div_x;
	float jumpZ = size_z / div_z;

	float xCounter = 0.0;
	float zCounter = 0.0;
	
	float textureTJump = 1 / div_x;
	float textureSJump = 1 / div_z;

	float textureTCounter = 0.0;
	float textureSCounter = 0.0;

	for (int i = 0; i < div_x; i++) {
		for (int j = 0; j < div_z; j++) {
			glBegin(GL_QUADS);
			glTexCoord2f(textureSCounter, textureTCounter);
			glVertex3f(xCounter, 0.0, zCounter);

			glTexCoord2f(textureSCounter, textureTCounter + textureTJump);
			glVertex3f(xCounter, 0.0, zCounter + jumpZ);

			glTexCoord2f(textureSCounter + textureSJump, textureTCounter + textureTJump);
			glVertex3f(xCounter + jumpX, 0.0, zCounter + jumpZ);

			glTexCoord2f(textureSCounter + textureSJump, textureTCounter);
			glVertex3f(xCounter + jumpX, 0.0, zCounter);		

			glEnd();
			textureTCounter += textureTJump;
			zCounter += jumpZ;
		}
		textureTCounter = 0.0;
		zCounter = 0.0;
		textureSCounter += textureSJump;
		xCounter += jumpX;
	}

}


void cgvScene3D::render(void) {
  
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();
		// the lights are placed before the transformations, this way they remain static during interaction

	  // TODO: Section B: Define and apply the point light specified in the practice 
	  cgvPoint3D position(1.0, 1.0, 1.0);
	  cgvColor ambient(0.0, 0.0, 0.0, 1.0);
	  cgvColor diffuse(1.0, 1.0, 1.0, 1.0);
	  cgvColor specular(1.0, 1.0, 1.0, 1.0);

	  glPushMatrix();
	  cgvLight light0(GL_LIGHT0, position, ambient, diffuse, specular, 1.0, 0.0, 0.0);
	  light0.switchOn();
	  light0.apply();
	  glPopMatrix();

	  if (selectedScene == 1) { // blue quad

		  draw_quad(1, 1);  

	  }
	  else if (selectedScene == 2) { // red quad
		  /* TODO: Section D: define and apply the material properties as specified in the practice */

		  cgvColor Ka(0.15, 0, 0);
		  cgvColor Kd(0.5, 0, 0);
		  cgvColor Ks(0.5, 0, 0);
		  double Ns = 120;

		  cgvMaterial material(Ka, Kd, Ks, Ns);
		  material.apply();

		  draw_quad(1, 1);
		  
	  }
	  else if (selectedScene == 3) { // mesh of quads
	  /* TODO: Section E and F: */
		  cgvColor Ka(0.15, 0, 0);

		  cgvMaterial material(Ka, *Rd, *Rs, matNs);
		  material.apply();
		  draw_quad(50,50);
	  }
	  else if (selectedScene == 4) { // Spotlight
		  // TODO: Section G: Define and apply a spotlight as specified in the practice instructions

		  cgvPoint3D pos(xPosition, yPosition, 1.0);
		  cgvPoint3D direction(0.0, -2.0, 0.0);

		  cgvLight light1(GL_LIGHT1, pos, ambient, diffuse, specular, 1.0, 0.0, 0.0, direction, 45, 0);
		  light1.apply();

		  cgvColor Ka(0.15, 0, 0);
		  cgvMaterial material(Ka, *Rd, *Rs, matNs);
		  material.apply();
		  draw_quad(50, 50);

		  // TODO: Switch off the new spotlight
		  light1.switchOff();
		  light1.apply();
	  }
	  else if (selectedScene == 5) { // world map
		  /* TODO: Section H: World map. Add the required code to cgvScene3D::render() to:
				o	Create and bind a texture from the file map.BMP.
				o	Render the triangle mesh of the scene. 
			*/

		  cgvPoint3D pos(xPosition, yPosition, 1.0);
		  cgvPoint3D direction(0.0, -2.0, 0.0);

		  cgvLight light1(GL_LIGHT1, pos, ambient, diffuse, specular, 1.0, 0.0, 0.0, direction, 45, 0);
		  light1.apply();

		  cgvTexture texture("map.bmp");
		  //texture.apply();

		  cgvColor Ka(0.15, 0, 0);
		  cgvColor Kd(0.5, 0, 0);
		  cgvColor Ks(0.5, 0, 0);
		  double Ns = 120;

		  cgvMaterial material(Ka, Kd, Ks, Ns);
		  material.apply();

		  draw_quad(50, 50);


	  }


	  // Assign the OpenGL default material. 
	  cgvMaterial defaultMat(cgvColor(0.2, 0.2, 0.2, 1), cgvColor(0.8, 0.8, 0.8, 1), cgvColor(0.0, 0, 0, 1), 0);
	  defaultMat.apply();

	glPopMatrix (); // restore the modelview matrix 
  
}

cgvColor cgvScene3D::getRs()
{
	return *Rs;
}

cgvColor cgvScene3D::getRd()
{
	return *Rd;
}

float cgvScene3D::getNs()
{
	return matNs;
}

void cgvScene3D::setRs(cgvColor _Rs)
{
	delete Rs;
	Rs = new cgvColor(_Rs);
}

void cgvScene3D::setRd(cgvColor _Rd)
{
	delete Rd;
	Rd = new cgvColor(_Rd);
}

void cgvScene3D::setNs(float _Ns)
{
	matNs = _Ns;
}

void cgvScene3D::moveX(float _n)
{
	xPosition += _n;
}

void cgvScene3D::moveY(float _n)
{
	yPosition += _n;
}

