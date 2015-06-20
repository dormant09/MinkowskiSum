//
//  GeometryHandler.cpp
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//

#include "GeometryHandler.h"



GeometryHandler::GeometryHandler()
{
    
}
void GeometryHandler::initGeometries()
{
    C = Surface();
    D = Surface();
    
    C.setColor(0.8, 0.2, 0.4);
    D.setColor(0.5, 0.3, 0.8);
    
    //Control points of the surface C initialization
    
    C.setPoint(0, 0, -5.0, -1.0, -5.0);
    C.setPoint(0, 1, -5.0, -1.0, -2.0);
    C.setPoint(0, 2, -5.0, -1.0, 2.0);
    C.setPoint(0, 3, -5.0, -1.0, 5.0);
    
    C.setPoint(1, 0, -2.0, -2.0, -5.0);
    C.setPoint(1, 1, -2.0, -2.0, -2.0);
    C.setPoint(1, 2, -2.0, -2.0, 2.0);
    C.setPoint(1, 3, -2.0, -2.0, 5.0);
    
    C.setPoint(2, 0, 2.0, -3.0, -5.0);
    C.setPoint(2, 1, 2.0, -3.0, -2.0);
    C.setPoint(2, 2, 2.0, -3.0, 2.0);
    C.setPoint(2, 3, 2.0, -3.0, 5.0);
    
    C.setPoint(3, 0, 5.0, -4.0, -5.0);
    C.setPoint(3, 1, 5.0, -4.0, -2.0);
    C.setPoint(3, 2, 5.0, -4.0, 2.0);
    C.setPoint(3, 3, 5.0, -4.0, 5.0);
    
    
    
    //Control points of the surface D initialization
    
    D.setPoint(0, 0, -4.0, 2.0, -4.0);
    D.setPoint(0, 1, -1.0, 2.0, -4.0);
    D.setPoint(0, 2, 1.0, 2.0, -4.0);
    D.setPoint(0, 3, 4.0, 2.0, -4.0);
    
    D.setPoint(1, 0, -4.0, 2.0, -1.0);
    D.setPoint(1, 1, -1.0, 2.0, -1.0);
    D.setPoint(1, 2, 1.0, 2.0, -1.0);
    D.setPoint(1, 3, 4.0, 2.0, -1.0);
    
    D.setPoint(2, 0, -4.0, 2.0, 1.0);
    D.setPoint(2, 1, -1.0, 2.0, 1.0);
    D.setPoint(2, 2, 1.0, 2.0, 1.0);
    D.setPoint(2, 3, 4.0, 2.0, 1.0);
    
    D.setPoint(3, 0, -4.0, 2.0, 4.0);
    D.setPoint(3, 1, -1.0, 2.0, 4.0);
    D.setPoint(3, 2, 1.0, 2.0, 4.0);
    D.setPoint(3, 3, 4.0, 2.0, 4.0);
    
    setSurfaces();
    
}

bool GeometryHandler::isSelected(int u, int v, int axes[2], double posX, double posY, int index)
{
    if(index == C_SELECTED)
    {
        if(posX - C.getPoint(u, v, axes[0]) < CLICK_ERROR && posX - C.getPoint(u, v, axes[0]) > - CLICK_ERROR)
        {
            if(posY - C.getPoint(u, v, axes[1]) < CLICK_ERROR && posY - C.getPoint(u, v, axes[1]) > - CLICK_ERROR)
            {
                return true;
            }
        }
        
    }
    else if(index == D_SELECTED)
    {
        if(posX - D.getPoint(u, v, axes[0]) < CLICK_ERROR && posX - D.getPoint(u, v, axes[0]) > - CLICK_ERROR)
        {
            if(posY - D.getPoint(u, v, axes[1]) < CLICK_ERROR && posY - D.getPoint(u, v, axes[1]) > - CLICK_ERROR)
            {
                return true;
            }
        }
    }
    
    return false;
}

void GeometryHandler::movePoint(int selectedPoint[2], int selectedAxes[2], double posX, double posY, int index)
{
    if(index == C_SELECTED)
    {
        C.changePoint(selectedPoint[0], selectedPoint[1], selectedAxes[0], posX);
        C.changePoint(selectedPoint[0], selectedPoint[1], selectedAxes[1], posY);
    }
    else if(index == D_SELECTED)
    {
        D.changePoint(selectedPoint[0], selectedPoint[1], selectedAxes[0], posX);
        D.changePoint(selectedPoint[0], selectedPoint[1], selectedAxes[1], posY);
    }
}



void GeometryHandler::setSurfaces()
{
    C.setSurface();
    D.setSurface();
    
}

void GeometryHandler::drawProjectedControlPoints(int horizontal, int vertical)
{
    C.drawControlPoints(horizontal, vertical);
    D.drawControlPoints(horizontal, vertical);
}

void GeometryHandler::drawLinesConnectingProjectedControlPoints(int horizontal, int vertical)
{
    C.drawLinesConnectingControlPoints(horizontal, vertical);
    D.drawLinesConnectingControlPoints(horizontal, vertical);
    
}

void GeometryHandler::drawSurfaces()
{
    C.drawSurface();
    D.drawSurface();
}


