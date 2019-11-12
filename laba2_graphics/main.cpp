//
//  main.cpp
//  laba2_graphics
//
//  Created by Yaroslav Zarechnyy on 9/7/19.
//  Copyright © 2019 Yaroslav Zarechnyy. All rights reserved.
//

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "DrawableFacade/DrawableFacade.cpp"
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define PI 3.14159265
#define ESCAPE '\033'
#include <cmath>
#include <iostream>

float varray[300][3];
float x = 0.5f, y = 0.5f, z;
static double cx = 0., cy = 0., cz = 0.;
double angleH = 45.0, angleV = 45.0;
double scaleCoef = 1;
double change_x, change_y, change_z = 0.;
double rotate_x, rotate_y, rotate_z = 0.;

void ChangeCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
    cx = cos(angleV * PI / 180.0) * cos(angleH * PI / 180.0);
    cz = cos(angleV * PI / 180.0) * sin(angleH * PI / 180.0);
    cy = sin(angleV * PI / 180.0);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    gluLookAt(cx, cy, cz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void light() {
        GLfloat light_ambient[] = {1, 0, 0, 1.0};
        GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0};

        /* устанавливаем параметры источника света */
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);   //Інтенсивність фонового світла
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);   //Інтенсивність дифузного світла
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //Інтенсивність дзеркального світла
        glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Положення джерела світла (x, y, z, w)
        /* включаем z-буфер */
        glEnable(GL_DEPTH_TEST);
        /* включаем освещение и источник2 света */
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        //glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);
}

void scale() {
    GLdouble scale_matrix[] = {
        scaleCoef, 0, 0, 0,
        0, scaleCoef, 0, 0,
        0, 0, scaleCoef, 0,
        0, 0, 0, 1};
    glMultMatrixd(scale_matrix);
    light();
}

void rotate() {
    GLdouble rotation_matrix_X[] = {
            1, 0, 0, 0,
            0, cos(rotate_x), sin(rotate_x), 0,
            0, -sin(rotate_x), cos(rotate_x), 0,
            0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_X);

    GLdouble rotation_matrix_Y[] = {
            cos(rotate_y), 0, -sin(rotate_y), 0,
            0, 1, 0, 0,
            sin(rotate_y), 0, cos(rotate_y), 0,
            0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_Y);

    GLdouble rotation_matrix_Z[] = {
            cos(rotate_z), sin(rotate_z), 0, 0,
            -sin(rotate_z), cos(rotate_z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    glMultMatrixd(rotation_matrix_Z);
    light();
}

void translate() {
    GLdouble translation_matrix_T[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        static_cast<GLdouble>(change_x),
        static_cast<GLdouble>(change_y), static_cast<GLdouble>(change_z), 1};
    glMultMatrixd(translation_matrix_T);
    light();
}

void display(void) {
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ChangeCamera();
    scale();
    translate();
    rotate();
    
    DrawableFacade facade;
    facade.drawTorus();
    facade.drawCones();
    
    GLint list_of_lists[] = {1, 2, 3, 4};
    glCallLists(4, GL_INT, list_of_lists);
    
    glutSwapBuffers();
    glFinish();

    facade.drawGraph();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -10000, 10000);
    //glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
        case ESCAPE:
            break;
        case '8':
            rotate_z += 1;
            break;
        case '7':
            rotate_x += 1;
            break;
        case '9':
            rotate_z += 1;
            break;
        case '0':
            change_x -= 2;
            break;
        case '1':
            change_x += 2;
            break;
        case '2':
            change_y -= 2;
            break;
        case '3':
            change_y += 2;
            break;
        case '6':
            scaleCoef -= 0.5;
            break;
        case '5':
            scaleCoef += 0.5;
            break;
        }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
    
    if (key == GLUT_KEY_RIGHT)
    {
        angleH += 5.0f;
    }
    if (key == GLUT_KEY_LEFT)
    {
        angleH -= 5.0f;
    }
    if (key == GLUT_KEY_UP)
    {
        if (angleV < 90.0)
            angleV += 5.0f;
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (angleV > -90.0)
            angleV -= 5.0f;
    }
    
    glutPostRedisplay();
}

void update (int value){
    
    angleH += value;
    if (angleH> 360) {
        angleH -=360;
    }
    glutPostRedisplay();
    glutTimerFunc(40, update, 2);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3d");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(40, update, 2);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
