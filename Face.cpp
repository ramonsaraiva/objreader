#include "Face.h"

Face::Face()
{
}

vector<int>& Face::getVertexes()
{
	return vertexes;
}

vector<int>& Face::getNormals()
{
	return normals;
}

vector<int>& Face::getTextures()
{
	return textures;
}