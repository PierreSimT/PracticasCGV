#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#include <math.h>
#include <stdio.h>

#include "cgvCamera.h"

// Constructors
cgvCamera::cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up,
	double _xwhalfdistance, double _ywhalfdistance,
	double _znear, double _zfar):zoomFactor(0.01), currentZoom(1)
{
	setCameraParameters(_PV, _rp, _up);
	setParallelParameters(_xwhalfdistance, _ywhalfdistance, _znear, _zfar);
}


cgvCamera::~cgvCamera () {}

void cgvCamera::setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up) {
	PV = _PV;
	rp = _rp;
	up = _up;
}

void cgvCamera::getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up) {
	_PV = PV;
	_rp = rp;
	_up = up;
}

void cgvCamera::setParallelParameters(double _xwhalfdistance, double _ywhalfdistance,
	double _znear, double _zfar)
{
	xwmin = -_xwhalfdistance;
	xwmax = _xwhalfdistance;
	ywmin = -_ywhalfdistance;
	ywmax = _ywhalfdistance;
	znear = _znear;
	zfar = _zfar;

}


void cgvCamera::getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax, 
										double& _znear, double& _zfar)
{
	_xwmin = xwmin;
	_xwmax = xwmax;
	_ywmin = ywmin;
	_ywmax = ywmax;
	_znear = znear;
	_zfar = zfar;
}



void cgvCamera::apply(cameraType type) {

// TODO: Practice 2b.C: Modify this method in order to adequately apply a zoom to the camera. 

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (type==CGV_PARALLEL) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (type==CGV_PERSPECTIVE) {
		double fovy, aspect; 
		computePerspectiveParameters(fovy, aspect, xwmin, xwmax, ywmin, ywmax);
		gluPerspective(fovy,aspect,znear,zfar);
	}
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PV[X],PV[Y],PV[Z], rp[X],rp[Y],rp[Z], up[X],up[Y],up[Z]);
}

void cgvCamera::setZoomFactor(double factor) {
	zoomFactor = factor; 
}

// TODO: Practice 2b.C: Implement these functions. 
void cgvCamera::zoomIn() {}
void cgvCamera::zoomOut() {}


void cgvCamera::computePerspectiveParameters(double &fovy, double &aspect, 
	double _xwmin, double _xwmax, double _ywmin, double _ywmax)
{
	// TODO: Practice 2b.A: Implement this function to compute the perspective parameters based on the current parallel parameters. 
}



