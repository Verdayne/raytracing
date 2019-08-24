#pragma once
#ifndef RAYCASTING_UTIL_H
#define RAYCASTING_UTIL_H

#ifdef _MSC_VER
	#define M_PI 3.14159f
    #define MAXFLOAT FLT_MAX
#endif // _MSC_VER

// https://iquilezles.org/www/articles/sfrand/sfrand.htm
// Return a random float: [0, 1)
float randf() {
    static int seed = 2019;
    
    union
    {
        float fres;
        unsigned int ires;
    };

    seed *= 16807;
    ires = ((((unsigned)seed)>>9 ) | 0x3f800000);
    return fres - 1.0f;
}

#endif // RAYCASTING_UTIL_H
