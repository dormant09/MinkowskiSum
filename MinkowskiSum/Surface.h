//
//  Surface.h
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//

#ifndef __MinkowskiSum__Surface__
#define __MinkowskiSum__Surface__

#include <math.h>
#include <GLUT/GLUT.h>
#include "Constants.h"



class Surface
{
    public :
    
    
    double color[3];
    
    double point[4][4][3];
    double surface[LINE_STRIP + 1][LINE_STRIP + 1][3];
    
    
    //Constructors
    Surface();
    
    
    //Setting functions
    void setSurface();
    void setColor(double red, double blue, double green);
    void setPoint(int u, int v, double x, double y, double z);
    void changePoint(int u, int v, int axis, double value);
    
    //Getting functions
    double getPoint(int u, int v, int axis);
    
    //Drawing functions
    void drawSurface();
    void drawControlPoints(int horizontal, int vertical);
    void drawLinesConnectingControlPoints(int horizontal, int vertical);
    
    
    
    
};



#endif /* defined(__MinkowskiSum__Surface__) */
