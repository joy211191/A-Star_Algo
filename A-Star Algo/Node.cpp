#include "Node.h"

Node::Node()
{
	nodeData = ' ';
	gCost = 9999;
	hCost = 0;
	fCost = gCost + hCost;
	xPos = 0;
	yPos = 0;
	previousNodeX = 999;
	previousNodeY = 999;
}

void Node::Init(int x,int y)
{
	xPos = x;
	yPos = y;
}

void Node::GCostUpdate()
{
	gCost = 9999;
}

void Node::AddNodeData(char info)
{
	nodeData = info;
}

void Node::CalculateFCost()
{
	fCost = gCost + hCost;
}


