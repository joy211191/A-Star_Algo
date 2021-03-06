#pragma once
class Node
{
public:
	char nodeData;
	int xPos, yPos;
	int gCost;
	int hCost;
	int fCost;

	int previousNodeX, previousNodeY;

	Node();
	void Init(int x,int y);
	void GCostUpdate();
	void AddNodeData(char info);
	void CalculateFCost();
};

