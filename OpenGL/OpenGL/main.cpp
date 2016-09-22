//
//  main.cpp
//  OpenGL
//
//  Created by Emma on 22/09/2016.
//  Copyright © 2016 Emma. All rights reserved.
//

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "hw5.h"

using namespace std;

void setCamera(void);
void drawScene(void);

static int win = 0;
static GLfloat whiteLight[3] = {1.0f, 1.0f, 1.0f};
static GLfloat secondaryLight[3] = {0.0f, 1.0f, 0.0f};
static GLfloat lightPosition[4] = {0.0f, 0.0f, 0.0f, 1.0f};
static GLuint teaTex;

void loadTextures()
{
    generate_texture();
    
    glGenTextures(2, &teaTex);
    glBindTexture(GL_TEXTURE_2D, teaTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPopMatrix();
    
    setCamera();
    
    drawScene();
    
    glutSwapBuffers();
}

void drawScene()
{
    // Draw Teapot
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, secondaryLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidTeapot(1.0f);
    glPopMatrix();
    
    // Draw Floor
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, whiteLight);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(2.0f, 0.0f, -2.0f);
    glTexCoord2f(2.0f, 2.0f); glVertex3f(-2.0f, 0.0f, -2.0f);
    glTexCoord2f(2.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f);
    glEnd();
    glPopMatrix();
}

void idle()
{
    glutPostRedisplay();
}

void setCamera()
{
    glTranslatef(0.0f,-0.75f, -2.0f);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
}


void CreateGlutWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (512, 512);
    win = glutCreateWindow ("Teapot");
}

void CreateGlutCallbacks()
{
    glutDisplayFunc(display);
    glutIdleFunc(idle);
}

void InitOpenGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    loadTextures();
    
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
    glEnable(GL_LIGHT0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void ExitGlut()
{
    glutDestroyWindow(win);
    exit(0);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    CreateGlutWindow();
    CreateGlutCallbacks();
    InitOpenGL();
        
    glutMainLoop();
    
    ExitGlut();
    return 0;		
}
