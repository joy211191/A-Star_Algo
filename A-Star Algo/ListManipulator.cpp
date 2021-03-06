#include "ListManipulator.h"
#include <math.h>


template <typename T>
using DynamicArray = std::vector<T>;

DynamicArray<Node> ListManipulator::GetNeighbourList(DynamicArray<Node> nodeList, Node currentNode, int sizeX, int sizeY)
{
	DynamicArray<Node> neighbourList;
	if (currentNode.xPos < sizeX - 1) {
		if (currentNode.yPos < sizeY - 1)
			neighbourList.push_back(GetNode(nodeList,currentNode.xPos + 1, currentNode.yPos + 1));
		neighbourList.push_back(GetNode(nodeList, currentNode.xPos + 1, currentNode.yPos));
		if (currentNode.yPos > 0)
			neighbourList.push_back(GetNode(nodeList, currentNode.xPos + 1, currentNode.yPos - 1));
	}
	if (currentNode.xPos > 0) {
		if (currentNode.yPos < sizeY - 1)
			neighbourList.push_back(GetNode(nodeList,currentNode.xPos - 1, currentNode.yPos + 1));
		neighbourList.push_back(GetNode(nodeList,currentNode.xPos - 1, currentNode.yPos));
		if (currentNode.yPos > 0)
			neighbourList.push_back(GetNode(nodeList,currentNode.xPos - 1, currentNode.yPos - 1));
	}
	if (currentNode.yPos > 0)
		neighbourList.push_back(GetNode(nodeList,currentNode.xPos, currentNode.yPos - 1));
	if (currentNode.yPos < sizeY - 1)
		neighbourList.push_back(GetNode(nodeList,currentNode.xPos, currentNode.yPos + 1));
	return neighbourList;
}

DynamicArray<Node> ListManipulator::RemoveFromList(DynamicArray<Node> nodeList, Node removalNode)
{
	auto node = nodeList.begin();
	while (node != nodeList.end()) {
		if ((*node).xPos == removalNode.xPos && (*node).yPos == removalNode.yPos) {
			nodeList.erase(node);
			break;
		}
		node++;
	}
	return nodeList;
}

DynamicArray<Node> ListManipulator::Path(DynamicArray<Node> nodeList, Node endNode)
{
	DynamicArray<Node> path;
	path.push_back(endNode);
	Node currentNode = endNode;
	while (currentNode.previousNodeX < MAX_PREVIOUS_POSITION_VALUE-1) {
		Node temp = GetNode(nodeList,currentNode.previousNodeX, currentNode.previousNodeY);
		path.push_back(temp);
		currentNode = temp;
	}
	return path;
}

DynamicArray<Node> ListManipulator::ArrayToDynanic(const unsigned char* inputArray,int arrayLength, int sizeX,int sizeY)
{
	DynamicArray<Node> dynamicArray;
	for (int i = 0; i < arrayLength; i++) {
		Node tempNode;
		tempNode.nodeData =inputArray[i]-48;
		if (sizeX > 0 && sizeY > 0) {
			tempNode.xPos = i % sizeX;
			tempNode.yPos=i / sizeY;
		}
		dynamicArray.push_back(tempNode);
	}
	return dynamicArray;
}

Node ListManipulator::GetNode(DynamicArray<Node> nodeList, int xPosition, int yPosition)
{
	auto node = nodeList.begin();
	while (node != nodeList.end()) {
		if ((*node).xPos == xPosition&&(*node).yPos==yPosition)
			return *node;
		node++;
	}
}

Node ListManipulator::GetLowestFCost(DynamicArray<Node> nodeList)
{
	Node lowestHCostNode = nodeList[0];
	for (int i = 1; i < nodeList.size(); i++) {
		if (nodeList[i].fCost < lowestHCostNode.fCost)
			lowestHCostNode = nodeList[i];
	}
	return lowestHCostNode;
}

int ListManipulator::CalculateDistance(Node start, Node end)
{
	int xDistance = abs(start.xPos - end.xPos);
	int yDistance = abs(start.yPos - end.yPos);
	int remaining = abs(xDistance - yDistance);
	int diagonalCost = DIAGONAL_COST * fmin(xDistance, yDistance);
	int straightCost = STRAIGHT_COST * remaining;
	return  diagonalCost + straightCost;
}

bool ListManipulator::CheckNode(DynamicArray<Node> nodeList, Node checkNode)
{
	auto node = nodeList.begin();
	while (node != nodeList.end()) {
		if ((*node).xPos == checkNode.xPos && (*node).yPos == checkNode.yPos)
				return true;
		node++;
	}
	return false;
}
