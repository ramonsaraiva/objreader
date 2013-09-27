#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	points[0] = x;
	points[1] = y;
	points[2] = z;
}

float* Vertex::getPoints()
{
	return points;
}