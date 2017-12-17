#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


class cgvScene3D {
	protected:
////// Section B: add here the attributes to control the degrees of freedom of the model
		float armRightAngle;
		float armLeftAngle;
		float armRightSideways;
		float armLeftSideways;
		float bodyAngle;
////// Section D: add here the attribute/s to control the selected object and to color it yellow

		int nameSelected;

		// Additional attributes		
		bool armRDown;
		bool armLDown;
		bool armRmove;
		bool armLmove;
		bool maxBody;

		static int LEFTLEG;
		static int RIGHTLEG;
		static int LEFTARM;
		static int RIGHTARM;
		static int BODY;
		static int HEAD;

		bool axes;

	public:
		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
    void render();

	void head();
	void body();

	void rightLeg();

	void leftLeg();

	void rightArm();

	void leftArm();


	////// Section B: include here the methods to modify the degrees of freedom of the model
	void rotateOneArm(int arm, float angle);
	void rotateArmSideways ( int arm, float angle );
	void rotateBody ( float angle );

	////// Section D: include here the method/s to indicate the selected object

	void selectedObject ( int name );

		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};
};

#endif
