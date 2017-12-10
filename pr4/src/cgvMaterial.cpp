#include "cgvMaterial.h"

// Constructor and destructor methods 

cgvMaterial::cgvMaterial () {
	
}

cgvMaterial::~cgvMaterial () {

}

cgvMaterial::cgvMaterial (const cgvMaterial& m) {	//copy constructor
	Ka = m.Ka;
	Kd = m.Kd;
	Ks = m.Ks;
	Ns = m.Ns;
}

cgvMaterial::cgvMaterial(cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Public methods 

void cgvMaterial::apply(void) {

// Section C
// Apply the attributes of the cgvMaterial object:
// - ambient coefficient 
// - diffuse coefficient
// - specular coefficient
// - Phong exponent

	GLfloat ambient[] = { Ka[0], Ka[1], Ka[2], Ka[3] };
	GLfloat diffuse[] = { Kd[0], Kd[1], Kd[2], Kd[3] };
	GLfloat specular[] = { Ks[0], Ks[1], Ks[2], Ks[3] };

	GLfloat emission[] = { 0, 0, 0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

// set the color (0.0, 0.0, 0.0) as emission color (the object is not a light source )


}

void cgvMaterial::set(cgvColor _Ka, cgvColor _Kd, cgvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



