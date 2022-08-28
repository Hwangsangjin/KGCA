#pragma once

#include "Node.h"
#include "ObjectBase.h"

enum SD_Type
{
	Quadtree,
	Octree,
	BSP
};

class SpaceDivision
{
private:
	SD_Type _sdType = Octree;

protected:
	Node* _pRootNode;

};

