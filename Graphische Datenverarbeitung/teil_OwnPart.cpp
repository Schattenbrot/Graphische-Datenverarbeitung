// GD-Praktikum:   teil_2.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"

float fRotation = 215.0f;
float fBeinchen = -0.4f;
float fFlighing = 0.0f;

void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden mus
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 80.0 / 255.0, 0.0, 1.0);		// Orange = FF8000
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	gluLookAt(1., 1., 0.3,
		0., 0., 0.,
		0., 1., 0.);
	
	glPushMatrix();

	glTranslatef(0.,fFlighing, 0.);

	//Hauptwürfel
	glPushMatrix();
	glScalef(3,3,3);
	Wuerfel(0.4, 0, 0, 0, 1);
	glPopMatrix();
	
	// Beine
	glPushMatrix();
	glTranslatef(0.39, fBeinchen, 0.39);
	glScalef(1, 3, 1);
	Wuerfel(0.4,1,0,2,1);
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

	// Rotorhalter
	glPushMatrix();
	glTranslatef(0, 0.4, 0);
	glScalef(0.5, 3, 0.5);
	Wuerfel(0.4, 1, 0, 2, 1);
	glPopMatrix();

	// Rotorblatt
	glPushMatrix();
	glTranslatef(0,1,0);
	glScalef(3,0.1,1);
	Wuerfel(0.4,0,1,0,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(1, 0.1, 3);
	Wuerfel(0.4, 0, 1, 0, 1);
	glPopMatrix();
	
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
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
	glOrtho(-5., 5., -5., 5., -5., 5.);
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
	bool readyToFligh{ false };
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

	if (readyToFligh) {
		fFlighing = fFlighing + 0.02f;
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
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}