// GD-Praktikum:   teil_ownPartAdditionalPoints.cpp
// Hergenroether / Groch    Last Update: 20.11.2018

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"
#include <string>

#include <GL/SOIL.h>

float fRotorheight = -1.0f;
float fRotation = 215.0f;
float fBeinchen = -0.4f;
float fFlighing = 0.0f;

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ position of the camera
float x = 0.0f, z = 1.0f, y = 0.0f;

GLuint boden_texture;

GLfloat extent = 1.0;   // Mass fuer die Ausdehnung des Modells
GLuint tex_2d;

void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgefuehrt werden muessen
	glClearColor(0.33f, 0.225f, 0.0f, 1.0f);	// Hintergrundfarbe definieren
	// Textur einlesen usw.
	tex_2d = SOIL_load_OGL_texture("boden.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	// Transparenz einsetzen (z.B. fuer Billboards)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Licht
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 3.0, -3.0, 3.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	// z-Buffer
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	// Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
	glEnable(GL_NORMALIZE);
}

void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden mus
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 80.0 / 255.0, 0.0, 1.0);		// Orange = FF8000
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	gluLookAt(x, y, z,
		0, 0, 0,
		0, 1, 0);

	// Draw ground
	glPushMatrix();
	glTranslatef(0, -1, 0);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);   glVertex3f(-4.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f);   glVertex3f(4.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f);   glVertex3f(4.0f, 0.0f, 4.0f);
		glTexCoord2f(0.0f, 1.0f);   glVertex3f(-4.0f, 0.0f, 4.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(0., fFlighing, 0.);

	//Hauptwürfel
	glPushMatrix();
	glScalef(3, 3, 3);
	Wuerfel(0.4, 0, 0, 0, 1);
	glPopMatrix();

	// Beine
	glPushMatrix();
	glTranslatef(0.39, fBeinchen, 0.39);
	glScalef(1, 3, 1);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.39, fBeinchen, -0.39);
	glScalef(1, 3, 1);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.39, fBeinchen, 0.39);
	glScalef(1, 3, 1);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.39, fBeinchen, -0.39);
	glScalef(1, 3, 1);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	// ROTOR
	glPushMatrix();

	glRotatef(fRotation, 0, 1, 0);
	glTranslatef(0, fRotorheight, 0);
	// Rotorhalter
	glPushMatrix();
	glTranslatef(0, 0.6, 0);
	glScalef(0.5, 2, 0.5);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	// Rotorblatt
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(2.9, 0.1, 1);
	Wuerfel(0.4, 0, 1, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(1, 0.1, 2.9);
	Wuerfel(0.4, 0, 1, 0, 1);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		x = sin(angle);
		z = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		x = sin(angle);
		z = -cos(angle);
		break;
	case GLUT_KEY_UP:
		y += 0.5 * fraction;
		break;
	case GLUT_KEY_DOWN:
		y -= 0.5 * fraction;
		break;
	}
}

void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt

	 // Matrix für Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten)
	glOrtho(-15., 15., -15., 15., -15., 15.);
	//gluPerspective(50.0, 1.0, 1.0, +5.0*extent);

	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	bool legready{};
	if (fRotorheight < 0)
	{
		fRotorheight += 0.01;
	}
	else {
		legready = true;
	}

	bool readyToFligh{ false };
	if (legready) {
		if (fBeinchen < -0.05) {
			fBeinchen = fBeinchen + 0.01;
		}
		else {
			readyToFligh = true;
		}

		fRotation = fRotation - 1.0; // Rotationswinkel aendern
		if (fRotation <= 0.0) {
			fRotation = fRotation + 360.0;
		}
	}



	if (readyToFligh) {
		fFlighing = fFlighing + 0.04f;
	}

	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Aaron; Markus");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	//AmbientLighting();
	//PointLight(0, 1, 1, 0, 1, 1);
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
