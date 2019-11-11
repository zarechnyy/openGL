//
//  DrawableFacade.cpp
//  laba2_graphics
//
//  Created by Yaroslav Zarechnyy on 11/11/19.
//  Copyright © 2019 Yaroslav Zarechnyy. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include "DrawableFacade.hpp"
#include "Drawable.hpp"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <cmath>

class DrawableTorus: Drawable {
public:
    virtual void draw()
    {
        glNewList(3, GL_COMPILE);
        glPushMatrix();
        
        glColor3ub(0, 0, 255);
        glTranslatef(100, 55, -50);
        glutSolidTorus(10, 20, 200, 200);
        
        glPopMatrix();
        glEndList();
        
        glNewList(4, GL_COMPILE);
        glPushMatrix();
        
        glColor3ub(255, 0, 255);
        glTranslatef(100, 55, -100);
        glutWireTorus(20, 30, 50, 50);
        
        glPopMatrix();
        glEndList();
    }
};

class DrawableCone: Drawable {
public:
    virtual void draw()
    {
        glNewList(1, GL_COMPILE);
        glPushMatrix();
        
        glColor3ub(255, 0, 0);
        glTranslatef(0, 0, -50);
        glutSolidCone(30, 50, 20, 20);
        
        glPopMatrix();
        glEndList();
        
        glNewList(2, GL_COMPILE);
        glPushMatrix();
        
        glColor3ub(0, 255, 0);
        glTranslatef(100, 55, 0);
        glutWireCone(30, 50, 20, 20);
        
        glPopMatrix();
        glEndList();
    }
};

class DrawableGraph: Drawable {
public:
    virtual void draw()
    {
        GLdouble points[300];
        GLint count = 0;
        for (GLint y = 0; y < 10; y++) {
            for (GLint x = 0; x < 10; x++) {
                points[count++] = x * 5;
                points[count++] = y * 5;
                points[count++] = sin(x) * cos(y) * 5;
            }
        }
    
        glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0, 1, 0);
        glVertexPointer(3, GL_DOUBLE, 0, points);
    
        glDrawArrays(GL_POINTS, 0, 200);
    
        glDisableClientState(GL_VERTEX_ARRAY);
        glutSwapBuffers();
        glFinish();
    }
};

class DrawableFacade
{
    DrawableTorus one;
    DrawableCone two;
    DrawableGraph third;
public:
    DrawableFacade()
    {
    }
    
    void drawTorus() {
        one.draw();
    }
    
    void drawCones() {
        two.draw();
    }
    
    void drawGraph() {
        third.draw();
    }
};
