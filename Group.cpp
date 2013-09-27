#include "Group.h"

Group::Group()
{
}

string Group::getName()
{
	return name;
}

vector<Face>& Group::getFaces()
{
	return faces;
}

void Group::setName(string n)
{
	name = n;
}