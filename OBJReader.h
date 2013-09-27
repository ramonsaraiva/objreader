#include <fstream>
#include <iostream>
#include <sstream>
#include "Mesh.h"

using namespace std;

class OBJReader
{
	private:
		string src;
		Mesh* mesh;

	public:
		OBJReader(string s, Mesh* m);

		void readObj();
		Group* OBJReader::searchForExistingGroup(string name);

		vector<string>& split(const string &s, char delim, vector<string> &elems);
};