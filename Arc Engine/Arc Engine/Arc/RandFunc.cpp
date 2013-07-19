#include "RandFunc.h"

void Arc::initRandom( void )
{
    srand( unsigned(time(nullptr)) );
}

int Arc::randInt( int min, int max )
{
    return min + (rand() % (max - min + 1));
}

float Arc::randFloat( float min, float max )
{
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

double Arc::randDouble( double min, double max )
{
    return min + (double)rand() / (double)(RAND_MAX / (max - min));
}

