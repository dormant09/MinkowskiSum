//
//  Surface.cpp
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//

#include "Surface.h"



//Constructors
Surface::Surface()
{
    

    
}



//Setting functions

void Surface::setSurface()
{
    
    for(int i=0; i<=LINE_STRIP; i++)
    {
        for(int j=0; j<=LINE_STRIP; j++)
        {
            
            double x, y, z;
            
            x = 0.0;
            y = 0.0;
            z = 0.0;
            
            
            for(int k=0; k<4; k++)
            {
                for(int l=0; l<4; l++)
                {
                    double Bernstein = lookupTableBernstein[k](i)*lookupTableBernstein[l](j);
                    
                    x += Bernstein * getPoint(k, l, 0);
                    y += Bernstein * getPoint(k, l, 1);
                    z += Bernstein * getPoint(k, l, 2);
                }
            }
            
            surface[i][j][0] = x;
            surface[i][j][1] = y;
            surface[i][j][2] = z;
            
        }
    }
    
    
}
void Surface::setColor(double red, double blue, double green)
{
    color[0] = red;
    color[1] = blue;
    color[2] = green;
}
void Surface::setPoint(int u, int v, double x, double y, double z)
{
    
    point[u][v][0] = x;
    point[u][v][1] = y;
    point[u][v][2] = z;
}
void Surface::changePoint(int u, int v, int axis, double value)
{
    point[u][v][axis] = value;
}


//Getting functions
double Surface::getPoint(int u, int v, int axis)
{
    return point[u][v][axis];
}


//Drawing functions
void Surface::drawSurface()
{
    
    
    
    glBegin(GL_QUADS);
    
    glColor3d(color[0], color[1], color[2]);
    
    for(int i=0; i<LINE_STRIP; i++)
    {
        for(int j=0; j<LINE_STRIP; j++)
        {
            
            
            glVertex3d(surface[i][j][0], surface[i][j][1], surface[i][j][2]);
            glVertex3d(surface[i][j+1][0], surface[i][j+1][1], surface[i][j+1][2]);
            glVertex3d(surface[i+1][j+1][0], surface[i+1][j+1][1], surface[i+1][j+1][2]);
            glVertex3d(surface[i+1][j][0], surface[i+1][j][1], surface[i+1][j][2]);
            
            
            
        }
    }
    
    glEnd();
    
    
}

void Surface::drawControlPoints(int horizontal, int vertical)
{
    glBegin(GL_POINTS);
    
    glColor3d(color[0], color[1], color[2]);
    
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            glVertex2d(getPoint(i, j, horizontal), getPoint(i, j, vertical));
        }
    }
    
    
    glEnd();
}
void Surface::drawLinesConnectingControlPoints(int horizontal, int vertical)
{
    glBegin(GL_LINES);
    
    glColor3d(0.0, 0.0, 0.0);
    
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<3; j++)
        {
            glVertex2d(getPoint(i, j, horizontal), getPoint(i, j, vertical));
            glVertex2d(getPoint(i, j+1, horizontal), getPoint(i, j+1, vertical));
            
        }
    }
    
    for(int j=0; j<4; j++)
    {
        for(int i=0; i<3; i++)
        {
            glVertex2d(getPoint(i, j, horizontal), getPoint(i, j, vertical));
            glVertex2d(getPoint(i+1, j, horizontal), getPoint(i+1, j, vertical));
            
        }
    }
    
    glEnd();
}


