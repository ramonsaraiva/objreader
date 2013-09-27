#include "OBJReader.h"



OBJReader::OBJReader(string s, Mesh* m)
{
	src = s;
	mesh = m;
}

void OBJReader::readObj()
{
	ifstream in;

	const int buffer_size = 100;
	char buffer[buffer_size];
	vector<string> tokens;
	vector<string> indexes;
	int index;

	Group* current;
	Face* curface;

	in.open(src);

	while (!in.eof())
	{
		tokens.clear();

		in.getline(buffer, buffer_size);
		split(buffer, ' ', tokens);

		mesh->getGroups().push_back(Group());
		current = &mesh->getGroups().back();
		
		switch (buffer[0])
		{
			case '#':
				break;
			case 'g':
				if (tokens.size() > 1)
				{
					current = searchForExistingGroup(tokens.at(1));
					
					if (!current)
					{
						mesh->getGroups().push_back(Group());
						current = &mesh->getGroups().back();
						current->setName(tokens.at(1));
					}
				}
				else
				{
					mesh->getGroups().push_back(Group());
					current = &mesh->getGroups().back();
				}
				break;
			case 'v':
				if (buffer[1] == ' ')
				{
					mesh->getVertexes().push_back(Vertex(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()), atof(tokens.at(3).c_str())));
				}
				else if (buffer[1] == 'n')
				{
					 mesh->getNormals().push_back(Vertex(atof(tokens.at(1).c_str()), atof(tokens.at(2).c_str()), atof(tokens.at(3).c_str())));
				}
				break;
			case 'f':
				current->getFaces().push_back(Face());
				curface = &current->getFaces().back();

				for (int i = 1; i < tokens.size(); i++)
				{
					indexes.clear();

					split(tokens.at(i), '/', indexes);

					switch (indexes.size())
					{
						case 2:
							// Vertex
							index = atoi(indexes.at(0).c_str());
							curface->getVertexes().push_back(--index);

							// Normal
							index = atoi(indexes.at(1).c_str());
							curface->getNormals().push_back(--index);
							break;
						case 3:
							// Vertex
							index = atoi(indexes.at(0).c_str());
							if (index > 0)
								curface->getVertexes().push_back(--index);

							// Texture
							index = atoi(indexes.at(1).c_str());
							if (index > 0)
								curface->getTextures().push_back(--index);

							// Normal
							index = atoi(indexes.at(2).c_str());
							if (index > 0)
								curface->getNormals().push_back(--index);
							break;
						default:
							break;
					}
				}
		}
	}
}

Group* OBJReader::searchForExistingGroup(string name)
{
	Group* current;

	for (int i = 0; i < mesh->getGroups().size(); i++)
	{
		current = &mesh->getGroups().at(i);

		if (current->getName().compare(name) == 0)
			return current;
	}

	return NULL;
}

vector<string>& OBJReader::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}