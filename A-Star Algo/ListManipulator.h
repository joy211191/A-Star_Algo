#pragma once
#include <vector>
#include "Node.h"

class ListManipulator
{

	template <typename T>
	using DynamicArray = std::vector<T>;

public:
	static const int MAX_PREVIOUS_POSITION_VALUE = 999;
	static const int STRAIGHT_COST = 10;
	static const int DIAGONAL_COST = 10;
	static DynamicArray<Node> GetNeighbourList(DynamicArray<Node> nodeList,Node currentNode, int sizeX, int sizeY);;
	static DynamicArray<Node> RemoveFromList(DynamicArray<Node> nodeList, Node removalNode);
	static DynamicArray<Node> Path(DynamicArray<Node> nodeList, Node endNode);
	static DynamicArray<Node> ArrayToDynanic(const unsigned char* inputArray,int arrayLength,int xSize=0,int sizeY=0);
	static Node GetNode(DynamicArray<Node> nodeList, int xPosition, int yPosition);
	
	static Node GetLowestFCost(DynamicArray<Node> nodeList);
	static int CalculateDistance(Node start, Node end);
	static bool CheckNode(DynamicArray<Node> nodeList, Node checkNode);
};