#include "Group.h"

class Mesh
{
	private:
		vector<Vertex> vertexes;
		vector<Vertex> normals;
		vector<Vertex> textures;
		vector<Group> groups;

	public:
		Mesh();

		vector<Vertex>& getVertexes();
		vector<Vertex>& getNormals();
		vector<Vertex>& getTextures();
		vector<Group>& getGroups();
};