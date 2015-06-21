//
//  GeometryHandler.h
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//

#ifndef __MinkowskiSum__GeometryHandler__
#define __MinkowskiSum__GeometryHandler__

#include <GLUT/GLUT.h>
#include "Surface.h"




class GeometryHandler
{
    public :
    
    GeometryHandler();
    Surface C, D;
    
    void initGeometries();
    
    bool isSelected(int u, int v, int axes[2], double posX, double posY, int index);
    void movePoint(int selectedPoint[2], int selectedAxes[2], double posX, double posY, int index);
    
    void setSurfaces();
    
    
    //drawing functions
    void drawProjectedControlPoints(int horizontal, int vertical);
    void drawLinesConnectingProjectedControlPoints(int horizontal, int vertical);
    void drawSurfaces();
    
};


#endif /* defined(__MinkowskiSum__GeometryHandler__) */
