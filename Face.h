#include "Vertex.h"
#include <vector>

using namespace std;

class Face
{
	private:
		vector<int> vertexes;
		vector<int> normals;
		vector<int> textures;

	public:
		Face();

		vector<int>& getVertexes();
		vector<int>& getNormals();
		vector<int>& getTextures();
};