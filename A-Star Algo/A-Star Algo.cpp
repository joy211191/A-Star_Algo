#include <iostream>
#include<vector>
#include<math.h>
#include "Node.h"
#include "ListManipulator.h"
using namespace std;
const int MAX_GRID_SIZE_X = 20;
const int MAX_GRID_SIZE_Y = 20;

unsigned char pMap[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];;
const int totalGrids = MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y;
int startX = 0, startY = 0;
int endX = 0, endY = 0;
int sizeX = 0, sizeY = 0;

template <typename T>
using DynamicArray = std::vector<T>;

DynamicArray<Node> pathList;

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
	//Convert array to dynamic list
	DynamicArray<Node> nodeList = ListManipulator::ArrayToDynanic(pMap, sizeX * sizeY, sizeX, sizeY);
	//Nodes to be traversed
	DynamicArray <Node> openList;
	//Starting node
	Node currentNode = ListManipulator::GetNode(nodeList, nStartX, nStartY);
	//Ending node
	Node endNode = ListManipulator::GetNode(nodeList, nTargetX, nTargetY);
	//Neighbours around a certain node
	DynamicArray<Node> neighbourList;

	currentNode.gCost = 0;
	currentNode.hCost = ListManipulator::CalculateDistance(currentNode, endNode);
	currentNode.CalculateFCost();
	
	openList.push_back(currentNode);
	while (openList.size() > 0)
	{
		if (currentNode.hCost == 0)
			return ListManipulator::Path(pathList, currentNode).size();
	//Get the node with lowest FCost
		currentNode = ListManipulator::GetLowestFCost(openList);

		pathList.push_back(currentNode);
		openList = ListManipulator::RemoveFromList(openList, currentNode);
		neighbourList = ListManipulator::GetNeighbourList(nodeList, currentNode, sizeX, sizeY);
		for (int i = 0; i < neighbourList.size(); i++) {
			if (ListManipulator::CheckNode(pathList, neighbourList[i]))
				continue;
			if (neighbourList[i].nodeData == 0) {
				pathList.push_back(neighbourList[i]);
				continue;
			}
			int tentativeGCost = currentNode.gCost + ListManipulator::CalculateDistance(currentNode, neighbourList[i]);
			if (tentativeGCost < neighbourList[i].gCost) {
				neighbourList[i].previousNodeX = currentNode.xPos;
				neighbourList[i].previousNodeY = currentNode.yPos;
				neighbourList[i].gCost = tentativeGCost;
				neighbourList[i].hCost = ListManipulator::CalculateDistance(neighbourList[i], endNode);
				neighbourList[i].CalculateFCost();
				if (!ListManipulator::CheckNode(openList, neighbourList[i])) {
					openList.push_back(neighbourList[i]);
				}
			}
		}
	}
}


int main()
{
	cout << "\nEnter number of rows(20 Max) : ";
	cin >> sizeX;
	cout << "\nEnter number of columns(20 Max): ";
	cin >> sizeY;

	int pOutBuffer[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
	cout << "\n Type 1 for walkable and 0 for non walkable";
	for (int i = 0; i < sizeX * sizeY; i++) {
		cout << "\nElement number " << i<<": ";
		cin >> pMap[i];
	}
	cout << "\nStart position x,y: ";
	cin >> startX >> startY;
	cout << "\nEnd position x,y: ";
	cin >> endX >> endY;

	cout<< FindPath(startX, startY, endX, endY, pMap, sizeX, sizeY, pOutBuffer, sizeX * sizeY);

}