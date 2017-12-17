#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"

// Constructor methods -----------------------------------
int cgvScene3D::LEFTLEG = 0;
int cgvScene3D::RIGHTLEG = 1;
int cgvScene3D::BODY = 2;
int cgvScene3D::LEFTARM = 3;
int cgvScene3D::RIGHTARM = 4;
int cgvScene3D::HEAD = 5;

cgvScene3D::cgvScene3D () {
	axes = true;
// Section B: initialize the attributes to control the degrees of freedom of the model
	armRightAngle = 0;
	armLeftAngle = 0;

	armRightSideways = 0;
	armLeftSideways = 0;

	bodyAngle = 0;

	armLDown = false;
	armRDown = false;

	armLmove = false;
	armRmove = false;

	maxBody = false;
	nameSelected = -1;
// Section D: initialize the attribute/s that identifies the select object and to colour it yellow

}

cgvScene3D::~cgvScene3D() {}


// Public methods ----------------------------------------

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

void cgvScene3D::head() {

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	glScalef(1, 1.3, 1);
	glutSolidCube(0.5);
	glPopMatrix();
}

void cgvScene3D::body() {

	glScalef(1, 1, 0.5);
	glutSolidCube(2);
}

void cgvScene3D::rightArm() {
	
	glutSolidCube(0.7); // SHOULDER

	glTranslatef(0, -0.35, 0);
	glutSolidCube(0.45); // ELBOW

	glTranslatef(0, -0.65, 0);
	glScalef(0.35, 0.6, 0.32);
	glutSolidCube(1.5); // FOREARM
}

void cgvScene3D::leftArm() {

	glutSolidCube(0.7); // SHOULDER

	glTranslatef(0, -0.35, 0);
	glutSolidCube(0.45); // ELBOW

	glTranslatef(0, -0.65, 0);
	glScalef(0.35, 0.6, 0.32);
	glutSolidCube(1.5); // FOREARM
}

void cgvScene3D::rightLeg() {

	glutSolidCube(0.8);

	glTranslatef(0, -0.68, 0);
	glScalef(0.28, 0.5, 0.28);
	glutSolidCube(2);
}

void cgvScene3D::leftLeg() {
	
	glutSolidCube(0.8);

	glTranslatef(0, -0.68, 0);
	glScalef(0.28, 0.5, 0.28);
	glutSolidCube(2);

}

void cgvScene3D::render(void) {

	// lights
	GLfloat light0[4]={8.0,8.0,8.0,1}; // point light source  
	glLightfv(GL_LIGHT0,GL_POSITION,light0); // this light is placed here and it remains still 
	glEnable(GL_LIGHT0);
  
  
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

 		//glLightfv(GL_LIGHT0,GL_POSITION,light0); // the light is placed here and it moves with the scene
	  float mesh_color[4] = {1.0, 0.0, 0.0, 1.0}; 
	  glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

///// Section B: include here the visualization of the tree of the model by using the OpenGL stack of matrices 
/////             it is advisable to create an auxiliary method to encapsulate the code to visualize the model
/////             leaving here only the call to this method. In Section D add the names to the mobile parts of the object by 
/////		          the stack of names and control the selected object to colour it yellow

	  float yellow[4] = {1.0, 1.0, 0.0, 1.0};

	glInitNames();
	glPushMatrix();

	//LEFT LEG
	glPushMatrix();
		if ( nameSelected == LEFTLEG )
			glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
		else
			glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
		glTranslatef(0.42, 0.85, 0);
		glPushName(LEFTLEG);
		leftLeg();
		glPopName();
	glPopMatrix();

	//RIGHT LEG
	glPushMatrix();
	glTranslatef(-0.42, 0.85, 0);
	if ( nameSelected == RIGHTLEG )
			glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
	glPushName(RIGHTLEG);
	rightLeg();
	glPopName();
	glPopMatrix();

	//glPopMatrix();

	//BODY
	glRotatef(bodyAngle, 0 ,1 ,0 );
	glPushMatrix();
	if ( nameSelected == BODY )
		glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
	glTranslatef(0, 2.22, 0);
	glPushName(BODY);
	body();
	glPopMatrix();

	// RIGHT ARM
	glPushMatrix();
	if ( nameSelected == RIGHTARM )
		glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
	glTranslatef(-1.24, 2.7, 0);
	glRotatef(armRightSideways, 0, 0, 1);
	glRotatef(armRightAngle, 1, 0, 0);
	glPushName(RIGHTARM);
	rightArm();
	glPopName();
	glPopMatrix();

	// LEFT ARM
	glPushMatrix();
	if ( nameSelected == LEFTARM )
		glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
	glTranslatef(1.24, 2.7, 0);
	glRotatef(armLeftSideways, 0, 0, 1);
	glRotatef(armLeftAngle, 1, 0, 0);

	glPushName(LEFTARM);
	leftArm();
	glPopName();

	glPopMatrix();

	glPushMatrix();
	if ( nameSelected == HEAD )
		glMaterialfv(GL_FRONT,GL_EMISSION,yellow);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);
	glPushName(HEAD);
	head();
	glPopName();
	glPopMatrix();

	glPopMatrix (); // restore the modelview matrix 


}

void cgvScene3D::rotateOneArm(int arm, float angle) {

	if (arm == 0) {
		if ( armRightAngle > -180 && !armRDown ) {
			armRightAngle -= angle;
		} else {
			armRDown = true;
			armRightAngle += angle;
			if ( armRightAngle == 0 )
				armRDown = false;
		}
	}
	else {
		if ( armLeftAngle > -180 && !armLDown ) {
			armLeftAngle -= angle;
		} else {
			armLDown = true;
			armLeftAngle += angle;
			if ( armLeftAngle == 0 )
				armLDown = false;
		}
	}

}

void cgvScene3D::rotateArmSideways(int arm, float angle) {
	if ( arm == 0 ){
		if ( armRightSideways < 45 && !armRmove )
			armRightSideways += angle;
		else {
			armRmove = true;
			armRightSideways -= angle;
			if ( armRightSideways== 0 )
				armRmove = false;
		}
	} else {
		if ( armLeftSideways > -45 && !armLmove )
			armLeftSideways -= angle;
		else {
			armLmove = true;
			armLeftSideways += angle;
			if ( armLeftSideways== 0 )
				armLmove = false;
		}
	}

}

void cgvScene3D::rotateBody( float angle ){

	if ( bodyAngle < 20 && !maxBody ) {
		bodyAngle += angle;
	}
	else {
		maxBody = true;
		bodyAngle -= angle;
		if ( bodyAngle == -20 ) {
			maxBody = false;
		}
	}
}

void cgvScene3D::selectedObject(int name) {
	nameSelected = name;
}

