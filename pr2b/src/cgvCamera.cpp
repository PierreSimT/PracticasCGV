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
cgvCamera::cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up):camType(CGV_PARALLEL), currentZoom(1)
{
	setCameraParameters(_PV, _rp, _up);
	setParallelParameters(1, 1, 1, 20);
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
	camType = CGV_PARALLEL;

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

void cgvCamera::setPerspParameters(double _fovy, double _aspect, double _znear, double _zfar) {

	camType = CGV_PERSPECTIVE;

	fovy = _fovy;
	aspect = _aspect;
	znear = _znear;
	zfar = _zfar;

}

void cgvCamera::getPerspParameters(double& _fovy, double& _aspect, double& _znear, double& _zfar) {

	_fovy = fovy;
	_aspect = aspect;
	_znear = znear;
	_zfar = zfar;

}


void cgvCamera::apply() {

// TODO: Practice 2b.C: Modify this method in order to adequately apply a zoom to the camera.

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (camType==CGV_PARALLEL) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (camType==CGV_PERSPECTIVE) {
		gluPerspective(fovy,aspect,znear,zfar);
	}

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PV[X],PV[Y],PV[Z], rp[X],rp[Y],rp[Z], up[X],up[Y],up[Z]);
}

void cgvCamera::zoom(double factor) 
{
	// TODO: Practice 2b.C: Implement these functions. 
	// Perspective ZOOM IN = DECREASE ANGLE
	switch ( camType ) {
		case CGV_PARALLEL:
			double wmin,wmax,ymin,ymax,near,far;
			getParallelParameters( wmin, wmax, ymin, ymax , near, far );
			xwmin = wmin / factor;
			xwmax = wmax / factor;
			ywmin = ymin / factor;
			ywmax = ymax / factor;
			apply();
			break;
		case CGV_PERSPECTIVE:
			double fov, asp, neara, fara;
			getPerspParameters(fov, asp, neara, fara);
			fovy = fov / factor;
			apply();
			break;

	}
}
