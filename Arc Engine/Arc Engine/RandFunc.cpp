#include "RandFunc.h"

void initRandom( void )
{
    srand( unsigned(time(nullptr)) );
}

int randInt( int min, int max )
{
    return min + (rand() % (max - min + 1));
}

float randFloat( float min, float max )
{
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

double randDouble( double min, double max )
{
    return min + (double)rand() / (double)(RAND_MAX / (max - min));
}

