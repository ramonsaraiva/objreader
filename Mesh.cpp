#include "Mesh.h"

Mesh::Mesh()
{
}

vector<Vertex>& Mesh::getVertexes()
{
	return vertexes;
}

vector<Vertex>& Mesh::getNormals()
{
	return normals;
}

vector<Vertex>& Mesh::getTextures()
{
	return textures;
}

vector<Group>& Mesh::getGroups()
{
	return groups;
}