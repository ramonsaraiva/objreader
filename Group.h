#include "Face.h"

using namespace std;

class Group
{
	private:
		string name;
		vector<Face> faces;

	public:
		Group();

		string getName();
		vector<Face>& getFaces();

		void setName(string n);
};