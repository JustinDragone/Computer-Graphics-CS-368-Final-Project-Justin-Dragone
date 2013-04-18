// lighthouse with spinning light and moon
// is situated on rocks in ocean
// can press up or down arrow to move
// left and right arrows will make you move faster
// clicking left mouse button will make you see side to side

#include <gl/glut.h>
#include <stdlib.h>
#include <math.h>

static float animate = 0.0;

float angle = 0.0;

float vectorx=0.0, vectorz=-1.0;

float x=0.0f, y=0.0, z=60.0f;

float camera = 0.0;

int origin = 0.0;

void display(int width, int height) {
    float ratio =  width * 1.0 / height;
    glViewport(0, 0, width, height);
  gluPerspective(40.0, ratio, 0.5, 90.0);
	glMatrixMode(GL_MODELVIEW);
}

void lighthouse() {
    glBegin(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
    
    glColor3f(0.5, 0.35, 0.05);   
    glTranslatef(0.0, 0.0, 1.0);
    glutSolidDodecahedron();
    glTranslatef(1.0, 0.0, 1.0);
    glutSolidDodecahedron();
    glTranslatef(3.0, 0.0, 1.0);
    glutSolidDodecahedron();
    glTranslatef(3.0, 0.0, 1.0);
    glutSolidDodecahedron();
    glTranslatef(0.0, 0.0, 0.0);
    glutSolidDodecahedron();
    glutSolidCube(3);
    glTranslatef(0.0, 0.0, 0.0);
    
    GLUquadricObj * quadObj;
    quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GL_LINE);
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluDisk(quadObj, 0.0, 1.0, 35.0, 1.0);
    gluCylinder(quadObj, 1.0, 1.0, 8.0, 33.0, 1.0);
    glTranslatef(0.0, 0.0, 2.0);
    gluCylinder(quadObj, 1.0, 1.0, 3.0, 33.0, 1.0);
    gluDisk(quadObj, 0.0, 1.0, 35.0, 1.0);
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    
    glRotatef(animate,0,1,0);
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0,8.8,0);
    glPushMatrix();
    glRotatef(90,1,0,0);
    glutSolidCube(1.6);
    
    glBegin(GL_LIGHT_MODEL_AMBIENT);
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0,1.0,0.0);
    glutSolidSphere(0.6,30,3.0);
    
    glColor3f(1.0, 0.0, 0.0);
    glRotatef(-180,1,10,0);
    glTranslatef(-0.3,-1.0,0.9);
    glutSolidCone(1.0,2.0,40.0,10.0);
    
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0,10.0,10.0);
    glutSolidSphere(1.0,30.0,8.0);

    glPopMatrix();
    glEnd();
    glFlush();
    
}

void position(float camera) {
    
	x += camera * vectorx * 0.1;
	z += camera * vectorz * 0.1;
    
}

void background(void) {
    if (camera)
        position(camera);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glLoadIdentity();
	
	gluLookAt(x, 1.0, z, x+vectorx, 1.0, z+vectorz, 0.0, 1.0,  0.0);

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0, -100.0);
	glEnd();
    
	for(int i = -1; i < 1; i++)
		for(int j=-1; j < 1; j++) {
            glPushMatrix();
            glTranslatef(i * 0.0,0, j * 0.0);
            lighthouse();
            glPopMatrix();
        }
    glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_UP : camera = 0.5; break;
        case GLUT_KEY_DOWN : camera = -0.5; break;
        case GLUT_KEY_LEFT : camera = 0.5; break;
        case GLUT_KEY_RIGHT : camera = -0.5; break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
    }
    
}

void releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_UP : camera = 0.0; break;
        case GLUT_KEY_DOWN : camera = 0.0; break;
        case GLUT_KEY_LEFT : camera = 0.5; break;
        case GLUT_KEY_RIGHT : camera = -0.5; break;
    }
}

void mouse(int x, int y) {
    
    if (origin >= 0) {
        
		angle = (x - origin) * 0.001;
        
		vectorx = sin(angle + angle);
		vectorz = -cos(angle + angle);
	}
}

void modelMouse(int button, int state, int x, int y) {
    
	if (button == GLUT_LEFT_BUTTON) {
        
		if (state == GLUT_UP) {
			angle += angle;
			origin = 0;
		}
		else  {
			origin = x;
		}
	}
}

void animation()
{
    animate+=0.5;
    if (animate>360) animate=0;
    glutPostRedisplay();
    
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("Project 4");
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LIGHTING);
    glLoadIdentity();
	glutDisplayFunc(background);
	glutReshapeFunc(display);
	glutIdleFunc(background);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    glutMotionFunc(mouse);
	glutMouseFunc(modelMouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(animation);
	glutMainLoop();
}
