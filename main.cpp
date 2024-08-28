#include "model.h"
#include <iostream>
#include <SOIL2/SOIL2.h>

int w1, h1;
double k = 0;
double q = 1;

constexpr int SZX = 640;
constexpr int SZY = 640;
constexpr float ASP = static_cast<float>(SZX) / static_cast<float>(SZY);

bool lr = false;
float teta = 0, teta_l = 0;
void materialInit(void) {
    GLfloat myAmbient[] = { .25, .25, .25, 1. };
    glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
    GLfloat myDiffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse);
    GLfloat mySpecular[] = { 0.774597, 0.774597, 0.774597, 1 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);
    GLfloat myShininess[] = { 76.8 };
    glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(teta_l, 0, 1, 0);
	GLfloat myLightPosition[] = { 0, 2, -10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -.5, 0);
	glScalef(q, q, q);
	glRotatef(k, 0, 1, 0);
	glEnable(GL_NORMALIZE);
    draw_model();
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void keyX(unsigned char key, int x, int y) {
    switch (key) {
    case 'F':
    case 'f':
        glEnable(GL_LIGHTING);
        break;
    case 'B':
    case 'b':
        glDisable(GL_LIGHTING);
        break;
    case 'O':
    case 'o':
		teta_l += 6;
        break;
    case 'I':
    case 'i':
		teta_l -= 6;
        break;
	case 'x':
	case 'X':
		k += 5;
		break;
	case 'y':
	case 'Y':
		k -= 5;
		break;
    }
}

void init() {
    glClearColor(75. / 256., 0./ 256., 130. / 255., 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, ASP, 0.01f, 110.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-1.0, -1.0, -6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	unsigned char* image1 = SOIL_load_image("tex2.jpg", &w1, &h1, 0, SOIL_LOAD_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w1, h1, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glEnable(GL_TEXTURE_2D);

    glEnable(GL_DEPTH_TEST);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
		q += 0.1;
    }
    else if (button == GLUT_RIGHT_BUTTON) {
		if (q >= 0.1)
		{
			q -= 0.1;
		}
    }
}

int main(int argc, char** argv) try {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SZX, SZY);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Lab8");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutKeyboardFunc(keyX);
    glutMouseFunc(mouse);

    materialInit();
    init();
    glutMainLoop();
    return 0;
}
catch (std::exception& err) {
    std::cerr << err.what() << std::endl;
}