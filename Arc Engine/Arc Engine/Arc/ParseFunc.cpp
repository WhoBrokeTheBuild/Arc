#include "ParseFunc.h"
#include "StringFunc.h"
#include "Vector2.h"
#include "Circle.h"
#include "Rect.h"
#include "Color.h"
#include "ArrayList.h"

int Arc::parseInt( const string& value )
{
    stringstream ss(value);
    int result;
    return (ss >> result ? result : 0);
}

float Arc::parseFloat( const string& value )
{
    stringstream ss(value);
    float result;
    return (ss >> result ? result : 0.0f);
}

double Arc::parseDouble( const string& value )
{
    stringstream ss(value);
    double result;
    return (ss >> result ? result : 0.0);
}

bool Arc::parseBool( const string& value )
{
    return (value.find("true") != string::npos);
}

Arc::Vector2 Arc::parseVector2( const string& value )
{
    ArrayList<string> parts = strSplit(value, ',', 2);

    if (parts.size() < 2)
        return Vector2::ZERO;

    return Vector2(parseFloat(parts[0]), parseFloat(parts[1]));
}

Arc::Circle Arc::parseCircle( const string& value )
{
    ArrayList<string> parts = strSplit(value, ',', 3);

    if (parts.size() < 3)
        return Circle::ZERO;

    return Circle(parseFloat(parts[0]), parseFloat(parts[1]), parseFloat(parts[2]));
}

Arc::Rect Arc::parseRect( const string& value )
{
    ArrayList<string> parts = strSplit(value, ',', 4);

    if (parts.size() < 4)
        return Rect::ZERO;

    return Rect(parseFloat(parts[0]), parseFloat(parts[1]), parseFloat(parts[2]), parseFloat(parts[3]));
}

Arc::Color Arc::parseColor( const string& value )
{
    ArrayList<string> parts = strSplit(value, ',', 4);

    if (parts.size() < 4)
        return Color::WHITE;

    return Color(parseInt(parts[0]), parseInt(parts[1]), parseInt(parts[2]), parseInt(parts[3]));
}
