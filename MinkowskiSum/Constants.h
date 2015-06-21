//
//  Constants.h
//  MinkowskiSum
//
//  Created by Sijoon's MacBookAir on 2015. 6. 21..
//  Copyright (c) 2015년 Sijoon's MacBookAir. All rights reserved.
//

#ifndef MinkowskiSum_Constants_h
#define MinkowskiSum_Constants_h

static const double PI = 3.14159265358979;
static const int ANGLE_DIVISION = 256;

static const int WINDOW_WIDTH = 720;
static const int WINDOW_HEIGHT = 720;

static const int WINDOW_POSITION_X = 300;
static const int WINDOW_POSITION_Y = 300;

static const double VIEW_SIZE = 15.0;
static const double ORTHO_Z_NEAR = -100.0;
static const double ORTHO_Z_FAR = 100.0;

static const int DISPLAY_MODE_DEFAULT = 1;

static const int LINE_STRIP = 64;

static const int NONE_SELECTED = 0;
static const int C_SELECTED = 100;
static const int D_SELECTED = 200;

static const double CLICK_ERROR = 0.5;


template <int tableSize, class returnType = double, class argumentType = double>
class LookupTable
{
    public :
    
    explicit LookupTable(returnType (*function) (argumentType), double coeff)
    {
        for(int i=0; i<tableSize; i++)
        {
            lookupTableArray[i] = function(coeff * i);
        }
        
    }
    
    const returnType & operator() (int i) const
    {
        return lookupTableArray[i];
    }
    
    private :
    
    returnType lookupTableArray[tableSize];
    
};

static const LookupTable<ANGLE_DIVISION> lookupTableSine(sin, (double)(2*PI/ANGLE_DIVISION));
static const LookupTable<ANGLE_DIVISION> lookupTableCosine(cos, (double)(2*PI/ANGLE_DIVISION));



inline double cubicBernsteinFirst(const double c)
{
    return pow(1.0 - c, 3);
}
inline double cubicBernsteinSecond(const double c)
{
    return 3.0*pow(1.0 - c, 2)*c;
}
inline double cubicBernsteinThird(const double c)
{
    return 3.0*(1.0 - c)*pow(c, 2);
}
inline double cubicBernsteinFourth(const double c)
{
    return pow(c, 3);
}


static const LookupTable<LINE_STRIP + 1> lookupTableBernstein[4] =
{
    LookupTable<LINE_STRIP + 1>(cubicBernsteinFirst, (double)(1.0/LINE_STRIP)),
    LookupTable<LINE_STRIP + 1>(cubicBernsteinSecond, (double)(1.0/LINE_STRIP)),
    LookupTable<LINE_STRIP + 1>(cubicBernsteinThird, (double)(1.0/LINE_STRIP)),
    LookupTable<LINE_STRIP + 1>(cubicBernsteinFourth, (double)(1.0/LINE_STRIP))
};


#endif
