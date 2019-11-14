#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct center
{
 double x;
 double y;
 double z;
};struct center center;

struct eye
{
 double x;
 double y;
 double z;
};struct eye eye;

double mov = 1;
double angulo = 0;
double raio = -4;
double dimensao = 20;



void configuraProjecao() {
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, razaoAspecto, 1, 60);
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void redimensiona(int width, int height)
{
    glViewport(0, 0, width, height);
    configuraProjecao();
}

void desenha()
{
    configuraProjecao();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0,191,255);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao, -2, -dimensao);
        glVertex3d(dimensao, -2, -dimensao);
        glVertex3d(dimensao, 10, -dimensao);
        glVertex3d(-dimensao, 10, -dimensao);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(dimensao, -2, dimensao);
        glVertex3d(-dimensao, -2, dimensao);
        glVertex3d(-dimensao, 10, dimensao);
        glVertex3d(dimensao, 10, dimensao);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao, -2, dimensao);
        glVertex3d(-dimensao, -2, -dimensao);
        glVertex3d(-dimensao, 10, -dimensao);
        glVertex3d(-dimensao, 10, dimensao);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(dimensao, -2, -dimensao);
        glVertex3d(dimensao, -2, dimensao);
        glVertex3d(dimensao, 10, dimensao);
        glVertex3d(dimensao, 10, -dimensao);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao, 10, dimensao);
        glVertex3d(-dimensao, 10, -dimensao);
        glVertex3d(dimensao, 10, -dimensao);
        glVertex3d(dimensao, 10, dimensao);
    glEnd();


    glColor3f(0.0f,80.0f,0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao, -2, -dimensao);
        glVertex3d(-dimensao, -2, dimensao);
        glVertex3d(dimensao, -2, dimensao);
        glVertex3d(dimensao, -2, -dimensao);
        glEnd();

    glColor3f(255,255,255);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao+1, 6, 3);
        glVertex3d(-dimensao+1, 6, -3);
        glVertex3d(-dimensao+1, 8, -3);
        glVertex3d(-dimensao+1, 8, 3);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao+1, 8, 9);
        glVertex3d(-dimensao+1, 8, 5);
        glVertex3d(-dimensao+1, 10, 5);
        glVertex3d(-dimensao+1, 10, 9);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3d(-dimensao+1, 8, 2);
        glVertex3d(-dimensao+1, 8, -2);
        glVertex3d(-dimensao+1, 10, -2);
        glVertex3d(-dimensao+1, 10, 2);
    glEnd();

    glutSwapBuffers();
}


static void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :     // Tecla 'ESC
            exit(0);
            break;

        case 'w':
            eye.x -= (sin(angulo)* mov);
            center.x -= (sin(angulo)*mov);

            eye.z -= (cos(angulo)* mov);
            center.z -= (cos(angulo)*mov);
            break;

        case 's':
            eye.x += (sin(angulo)* mov);
            center.x += (sin(angulo)*mov);

            eye.z += (cos(angulo)* mov);
            center.z += (cos(angulo)*mov);
            break;

        case 'a':
            angulo += ((M_PI)/18);
            center.x = eye.x + (sin(angulo)*raio);
            center.z = eye.z + (cos(angulo)*raio);
            break;

        case 'd':
            angulo -= ((M_PI)/12);
            center.x = eye.x + (sin(angulo)*raio);
            center.z = eye.z + (cos(angulo)*raio);
            break;


    }

    glutPostRedisplay();
}

static void atoa(void)
{
    glutPostRedisplay();
}


// configura alguns parâmetros do modelo de iluminação: FONTE DE LUZ
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f};
// configura alguns parâmetros do modelo de iluminação: MATERIAL
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



int main(int argc, char *argv[])
{

    eye.x = 0;
    eye.y = 7;
    eye.z = 0;

    center.x = 0;
    center.y = 6;
    center.z = -4;

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("tp2");

    glutReshapeFunc(redimensiona);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    glutIdleFunc(atoa);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
