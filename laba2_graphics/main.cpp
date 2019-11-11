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
static double cx = 0., cy = 0., cz = 0., value = 0;


void ChangeCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    cx = sin(value);
    cz = cos(value);
    std::cout << cx << " " << cz << std::endl;
    gluLookAt(cx, cy, cz, 0, 0, 0., 0., 1., 0.);
}

void light() {
//        GLfloat light_ambient[] = {1, 0, 0, 1.0};
//        GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
//        GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
//        GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0};
//
//        /* устанавливаем параметры источника света */
//        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);   //Інтенсивність фонового світла
//        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);   //Інтенсивність дифузного світла
//        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); //Інтенсивність дзеркального світла
//        glLightfv(GL_LIGHT0, GL_POSITION, light_position); //Положення джерела світла (x, y, z, w)
//        /* включаем z-буфер */
//        glEnable(GL_DEPTH_TEST);
//        /* включаем освещение и источник2 света */
//        glEnable(GL_ALPHA_TEST);
//        glEnable(GL_LIGHTING);
//        glEnable(GL_LIGHT0);
//        //glEnable(GL_COLOR_MATERIAL);
//        glEnable(GL_NORMALIZE);
}

void scale(double coef) {
    GLdouble scale_matrix[] = {
        coef, 0, 0, 0,
        0, coef, 0, 0,
        0, 0, coef, 0,
        0, 0, 0, 1};
    glMultMatrixd(scale_matrix);
    light();
}

void rotate(double angle, bool around_x, bool around_y, bool around_z) {
    angle = angle * PI / 180.0;
    if (around_x) {
        GLdouble rotation_matrix_T[] = {
            1, 0, 0, 0,
            0, cos(angle), sin(angle), 0,
            0, -sin(angle), cos(angle), 0,
            0, 0, 0, 1};
        glMultMatrixd(rotation_matrix_T);
    }
    if (around_y) {
        GLdouble rotation_matrix_T[] = {
            cos(angle), 0, -sin(angle), 0,
            0, 1, 0, 0,
            sin(angle), 0, cos(angle), 0,
            0, 0, 0, 1};
        glMultMatrixd(rotation_matrix_T);
    }
    if (around_z) {
        GLdouble rotation_matrix_T[] = {
            cos(angle), sin(angle), 0, 0,
            -sin(angle), cos(angle), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
        glMultMatrixd(rotation_matrix_T);
    }
    light();
}

void translate(int change_x, int change_y, int change_z) {
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
  
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    
//    gluLookAt(cx, cy, cz, 0, 0, 0, 0, -1, 0);
    
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
            scale(0.5);
        case '8':
            rotate(-5, 1, 0, 0);
            break;
        case '2':
            rotate(5, 1, 0, 0);
            break;
        case '4':
            rotate(-5, 0, 1, 0);
            break;
        case '6':
            rotate(5, 0, 1, 0);
            break;
        case '3':
            rotate(-5, 0, 0, 1);
            break;
        case '0':
            translate(0, -1, 0);
            break;
        case '1':
            translate(0, 1, 0);
            break;
        case '7':
            translate(-1, 0, 0);
            break;
        case '9':
            translate(1, 0, 0);
            break;
        case '5':
            scale(1.5);
            break;
        case 'a':
            value += 0.1;
            ChangeCamera();
            break;
        case 's':
            value -= 0.1;
            ChangeCamera();
            break;
//        case 'd':
//            cx += 5.; break;
//        case 'f':
//            cx -= 5.; break;
//        case 'g':
//            cz += 5.; break;
//        case 'h':
//            cz -= 5.; break;
//        case 'q':
//            cx -= 5.; cy -= 5.; cz -= 5.; break;
//        case 'w':
//            cx += 5.; cy += 5.; cz += 5.; break;
        }
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3d");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
