#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#include <GL/glut.h>

#include "cgvLight.h"

#define nbScenes 5

class cgvScene3D {
	public:
		int Scene[nbScenes];
		char *Scene_Name[nbScenes];

	protected:
		// Attributes

		bool axes;
		int selectedScene;
		cgvColor* Rd;
		cgvColor* Rs;
		float matNs;

		float xPosition;
		float yPosition;

	public:
		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		void set(int scene);

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
    void render();

	cgvColor getRs();
	cgvColor getRd();
	float getNs();
	void setRs(cgvColor _Rs);
	void setRd(cgvColor _Rd);
	void setNs(float _Ns);
	void moveX(float _n);
	void moveY(float _n);
		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};

};

#endif
