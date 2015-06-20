//
//  main.cpp
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//


#include <GLUT/GLUT.h>
#include "GeometryHandler.h"

static const double PI = 3.14159265358979;
static const double ANGLE_INTERVAL = PI/128.0;

static const int WINDOW_WIDTH = 720;
static const int WINDOW_HEIGHT = 720;

static const int WINDOW_POSITION_X = 300;
static const int WINDOW_POSITION_Y = 300;

static const double VIEW_SIZE = 15.0;
static const double ORTHO_Z_NEAR = -100.0;
static const double ORTHO_Z_FAR = 100.0;

static const int DISPLAY_MODE_DEFAULT(1);
//static const int DISPLAY_MODE_ISOPARAMETER_CURVE(2);
//static const int DISPLAY_MODE_TETRAHEDRON_TRAJECTORY(3);

int displayMode = DISPLAY_MODE_DEFAULT;

int mouseSelection = NONE_SELECTED;
int selectedPoint[2];
int selectedAxes[2];

GLsizei width, height;

double theta = 0.0;
double scale = 1.0;

GeometryHandler *geometryHandler = new GeometryHandler();

void initLight()
{
    float ambLight[] = {0.9f, 0.9f, 0.9f, 1.0f};
    float specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float specref[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float lightPos[] = {0.0f, 20.0f, 10.0f, 1.0f};
    
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    
    glEnable(GL_LIGHT0);
    
    glShadeModel(GL_SMOOTH);
    
}

void enableLight()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
}
void disableLight()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
}


void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_POINT_SMOOTH);
    
    geometryHandler->initGeometries();
    
    //Intializing others
    glPointSize(6.0);
    glLineWidth(2.0);
    initLight();
    disableLight();
    
}

void drawBackground()
{
    glBegin(GL_QUADS);
    
    glVertex2d(-width/2.0, -height/2.0);
    glVertex2d(-width/2.0, height/2.0);
    glVertex2d(width/2.0, height/2.0);
    glVertex2d(width/2.0, -height/2.0);
    
    glEnd();
}

void project()
{
    GLfloat aspectRatio = (double) width / (double) height;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(width > height)
    {
        glOrtho(-VIEW_SIZE, VIEW_SIZE, -VIEW_SIZE/aspectRatio, VIEW_SIZE/aspectRatio, ORTHO_Z_NEAR, ORTHO_Z_FAR);
    }
    else
    {
        glOrtho(-VIEW_SIZE*aspectRatio, VIEW_SIZE*aspectRatio, -VIEW_SIZE, VIEW_SIZE, ORTHO_Z_NEAR, ORTHO_Z_FAR);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void project3D()
{
    project();
    glScaled(scale, scale, scale);
    gluLookAt(cos(theta), sin(theta), 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0);
}

void drawLeftTop()
{
    glViewport(0, height/2.0, width/2.0, height/2.0);
    
    glColor3d(1.0, 0.8, 1.0);
    drawBackground();
    
    //X-Y
    
    geometryHandler->drawLinesConnectingProjectedControlPoints(0, 1);
    geometryHandler->drawProjectedControlPoints(0, 1);
    
}

void drawLeftBottom()
{
    glViewport(0, 0, width/2.0, height/2.0);
    
    glColor3d(0.8, 1.0, 1.0);
    drawBackground();
    
    //Y-Z
    
    geometryHandler->drawLinesConnectingProjectedControlPoints(1, 2);
    geometryHandler->drawProjectedControlPoints(1, 2);
    
}
void drawRightBottom()
{
    glViewport(width/2.0, 0.0, width/2.0, height/2.0);
    
    glColor3d(1.0, 1.0, 0.8);
    drawBackground();
    
    //Z-X
    
    geometryHandler->drawLinesConnectingProjectedControlPoints(2, 0);
    geometryHandler->drawProjectedControlPoints(2, 0);
    
}



void drawRightTop()
{
    
    glViewport(width/2.0, height/2.0, width/2.0, height/2.0);
    glEnable(GL_DEPTH_TEST);
    enableLight();
    
    switch(displayMode)
    {
        case DISPLAY_MODE_DEFAULT :
            geometryHandler->drawSurfaces();
            break;
    }
    
    disableLight();
    glDisable(GL_DEPTH_TEST);
    
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glPointSize(10.0);
    project();
    drawLeftTop();
    drawLeftBottom();
    drawRightBottom();
    
    
    glPointSize(6.0);
    project3D();
    drawRightTop();
    
    
    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    if(h==0) h=1;
    
    width = w;
    height = h;
    
}

void mouse(int button, int state, int x, int y)
{
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        
        mouseSelection = NONE_SELECTED;
        
        double posX, posY;
        
        if(x >= 0 && x <= width/2.0 && y >= 0 && y <= height/2.0)
        {
            selectedAxes[0] = 0;
            selectedAxes[1] = 1;
            
            posX = (x  - width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else if(x >= 0 && x <= width/2.0 && y >= height/2.0 && y <= height)
        {
            selectedAxes[0] = 1;
            selectedAxes[1] = 2;
            
            posX = (x - width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (3.0*height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else if(x >= width/2.0 && x <= width && y >= height/2.0 && y <= height)
        {
            selectedAxes[0] = 2;
            selectedAxes[1] = 0;
            
            posX = (x - 3.0*width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (3.0*height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else return;
        
        
        
        
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                
                if(geometryHandler->isSelected(i, j, selectedAxes, posX, posY, C_SELECTED))
                {
                    mouseSelection = C_SELECTED;
                    selectedPoint[0] = i;
                    selectedPoint[1] = j;
                    return;
                    
                }
                
                if(geometryHandler->isSelected(i, j, selectedAxes, posX, posY, D_SELECTED))
                {
                    mouseSelection = D_SELECTED;
                    selectedPoint[0] = i;
                    selectedPoint[1] = j;
                    return;
                }
                
            }
        }
        
    }
    
}

void motion(int x, int y)
{
    
    if(mouseSelection != NONE_SELECTED)
    {
        
        double posX, posY;
        
        if(x >= 0 && x <= width/2.0 && y >= 0 && y <= height/2.0)
        {
            if(!(selectedAxes[0] == 0 && selectedAxes[1] == 1)) return;
            
            posX = (x  - width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else if(x >= 0 && x <= width/2.0 && y >= height/2.0 && y <= height)
        {
            if(!(selectedAxes[0] == 1 && selectedAxes[1] == 2)) return;
            
            
            posX = (x - width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (3.0*height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else if(x >= width/2.0 && x <= width && y >= height/2.0 && y <= height)
        {
            if(!(selectedAxes[0] == 2 && selectedAxes[1] == 0)) return;
            
            
            posX = (x - 3.0*width/4.0)*(4.0*VIEW_SIZE)/width;
            posY = (3.0*height/4.0 - y)*(4.0*VIEW_SIZE)/height;
        }
        else return;
        
        geometryHandler->movePoint(selectedPoint, selectedAxes, posX, posY, mouseSelection);
        
        
    }
    
    geometryHandler->setSurfaces();
    
    
    
    
    glutPostRedisplay();
    
}

void idle()
{
    theta += ANGLE_INTERVAL;
    
    glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1' :
            displayMode = DISPLAY_MODE_DEFAULT;
            break;
            
        case '-' : case'_' :
            scale /= 1.1;
            break;
            
        case '+' : case '=' :
            scale *= 1.1;
            break;
            
    }
    
    
    glutPostRedisplay();
}


int main(int argc, const char * argv[])
{
    glutInit(&argc, (char**) argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Minkowski Sum");
    
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    
    glutMainLoop();
    
    return 0;
}
