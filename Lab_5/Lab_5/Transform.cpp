#include "GlutWin.h"
#include "Vector3.h"

// types //////////////////////////////////////////////////
struct TransformInfo {

	// holds transformation info
	Vector3	vTranslate,
		vRotate,
		vScale;

	// also some RGB color info
	Vector3	vColor;

};

// globals ////////////////////////////////////////////////////
int					n;			// index to "selected" object in scene
TransformInfo		pTransInfo[9];// array to hold info for each object
GLUquadricObj	*	qobj;			// pointer to GLU structure/handle
GlutWin		*	win;

// functions //////////////////////////////////////////////////
void glRotatefv(Vector3 r) {

	glRotatef(r[0], 1, 0, 0);
	glRotatef(r[1], 0, 1, 0);
	glRotatef(r[2], 0, 0, 1);

}

void glTranslatefv(Vector3 t) {

	glTranslatef(t[0], t[1], t[2]);

}

void glScalefv(Vector3 s) {

	glScalef(s[0], s[1], s[2]);

}

void glColorfv(Vector3 c) {

	// RGB style
	glColor3f(c[0], c[1], c[2]);

}

void initTable(float topWidth, float topThick, float legLen, float legThick) {

	pTransInfo[3].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[3].vScale = Vector3(topWidth, topThick, topWidth); // no scale
	pTransInfo[3].vTranslate = Vector3(0.5f, 0.5f, 0.5f);// small cube at (0,1,1)

	pTransInfo[4].vColor = Vector3(1.0f, 0.0f, 1.0f); 
	pTransInfo[4].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[4].vScale = Vector3(legThick, legLen, legThick); 
	pTransInfo[4].vTranslate = Vector3(0.85f, 0.0f, 0.85f);

	pTransInfo[5].vColor = Vector3(0.0f, 1.0f, 0.0f);
	pTransInfo[5].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[5].vScale = Vector3(legThick, legLen, legThick);
	pTransInfo[5].vTranslate = Vector3(0.15f, 0.0f, 0.85f);

	pTransInfo[6].vColor = Vector3(1.0f, 1.0f, 0.0f); 
	pTransInfo[6].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[6].vScale = Vector3(legThick, legLen, legThick);
	pTransInfo[6].vTranslate = Vector3(0.15f, 0.0f, 0.15f);

	pTransInfo[7].vColor = Vector3(1.0f, 0.0f, 0.0f); 
	pTransInfo[7].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[7].vScale = Vector3(legThick, legLen, legThick);
	pTransInfo[7].vTranslate = Vector3(.85f,0.0f, 0.15f);
}
void init() {

	// first entry governs whole scene
	//pTransInfo[0].vColor = Vector3(1.0f, 0.0f, 0.0f); // red
	pTransInfo[0].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[0].vScale = Vector3(1.0f, 1.0f, 1.0f); // no scale
	pTransInfo[0].vTranslate = Vector3(0.5f, 0.5f, 0.5f); // center of scene

														  // sphere
	//pTransInfo[1].vColor = Vector3(0.0f, 0.0f, 0.0f); // black
	pTransInfo[1].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[1].vScale = Vector3(1.0f, 1.0f, 1.0f); // no scale
	pTransInfo[1].vTranslate = Vector3(-0.5f, 0.5f, 0.5f);// sphere at (1,1,0)

														  // teapot
	//pTransInfo[2].vColor = Vector3(0.0f, 0.0f, 0.0f); // black
	pTransInfo[2].vRotate = Vector3(0.0f, 0.0f, 0.0f);	// no rotation
	pTransInfo[2].vScale = Vector3(1.0f, 1.0f, 1.0f); // no scale
	pTransInfo[2].vTranslate = Vector3(0.5f, 0.5f, 0.5f); // teapot at (1,1,1)
	
	initTable(1.0f, .15f, 1.0f, .05f);
														   // initialize quadric handle
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);

	n = 0;

	// clear rendering surface
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white
	glViewport(0, 0, 640, 480);

	// set the view 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 1000);

}



void doTransform(TransformInfo & t) {

	glTranslatefv(t.vTranslate);
	glRotatefv(t.vRotate);
	glScalefv(t.vScale);

	// finally set color
	glColorfv(t.vColor);

}

void RotateTable() {

}
void ScaleTable() {

}
void TranslateTable() {

}
void doTransformTable() {
	glPushMatrix();
	doTransform(pTransInfo[3]);
	glutSolidCube(1);
	
	glPushMatrix();
	doTransform(pTransInfo[4]);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	doTransform(pTransInfo[5]);
	glutSolidCube(1);
	glPopMatrix();

	
	glPushMatrix();
	doTransform(pTransInfo[6]);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	doTransform(pTransInfo[7]);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void transform_render() {

	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2.0f, 2.0f, 2.0f,   // looking down from (2,2,2)
		0.0f, 0.0f, 0.0f,   // to the origin
		0.0f, 1.0f, 0.0f); // y axis points up

	glPushMatrix();

	//transform entire scene
	doTransform(pTransInfo[0]);
	
	doTransformTable();
	glPushMatrix();
	doTransform(pTransInfo[3]);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	doTransform(pTransInfo[1]);
	glutSolidSphere(0.25, 10, 8);
	glPopMatrix();

	glPushMatrix();
	doTransform(pTransInfo[2]);
	glutSolidTeapot(0.2);
	glPopMatrix();

	
	glPopMatrix();

	// refresh image
	glutSwapBuffers();

}

void transform_keyboard(unsigned char key, int x, int y) {

	if (key == 'q')
		exit(0);

	// select object
	if (key == 'a') {
		// reset color to black
		pTransInfo[n].vColor = Vector3(0.0f, 0.0f, 0.0f);
		n++;	// increment
		n %= 8; // wrap around
				// set color to red
		pTransInfo[n].vColor = Vector3(1.0f, 0.0f, 0.0f);
	}

	// scale object
	if (key == '-') {
		pTransInfo[n].vScale[0] -= 0.1f;
		pTransInfo[n].vScale[1] -= 0.1f;
		pTransInfo[n].vScale[2] -= 0.1f;
	}

	if (key == '+') {
		pTransInfo[n].vScale[0] += 0.1f;
		pTransInfo[n].vScale[1] += 0.1f;
		pTransInfo[n].vScale[2] += 0.1f;
	}

	// translate object
	// along x axis
	if (key == 'w')
		pTransInfo[n].vTranslate[0] += 0.1f;
	if (key == 's')
		pTransInfo[n].vTranslate[0] -= 0.1f;

	// along y axis
	if (key == 'e')
		pTransInfo[n].vTranslate[1] += 0.1f;
	if (key == 'd')
		pTransInfo[n].vTranslate[1] -= 0.1f;

	// along z axis
	if (key == 'r')
		pTransInfo[n].vTranslate[2] += 0.1f;
	if (key == 'f')
		pTransInfo[n].vTranslate[2] -= 0.1f;


	// rotate object
	// about x axis
	if (key == 't')
		pTransInfo[n].vRotate[0] += 1.0f;
	if (key == 'g')
		pTransInfo[n].vRotate[0] -= 1.0f;

	// about y axis
	if (key == 'y')
		pTransInfo[n].vRotate[1] += 1.0f;
	if (key == 'h')
		pTransInfo[n].vRotate[1] -= 1.0f;

	// about z axis
	if (key == 'u')
		pTransInfo[n].vRotate[2] += 1.0f;
	if (key == 'j')
		pTransInfo[n].vRotate[2] -= 1.0f;


	glutPostRedisplay();

}

int main(int argc, char **argv) {

	// initialize GLUT class
	win = new GlutWin(600, 800,
		100, 100,
		GLUT_DOUBLE | GLUT_RGB,
		"3D Transformations Demo");

	init();

	glutDisplayFunc(transform_render);
	glutKeyboardFunc(transform_keyboard);

	// start rendering loop
	glutMainLoop();
	delete win;

	return(0);
}
