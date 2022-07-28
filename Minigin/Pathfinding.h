#pragma once
#include "HelperStructs.h"
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/


struct Node
{
	Vector2 position;
	std::vector<std::pair<int, int>> neighbours;
};

class Pathfinding
{
public:
	Pathfinding(int amountOfVertices);
	Pathfinding(const Pathfinding&) = delete;
	Pathfinding& operator=(const Pathfinding&) = delete;
	Pathfinding(Pathfinding&&) = delete;
	Pathfinding& operator=(Pathfinding&&) = delete;
	~Pathfinding() = default;

	void PathTo(const Vector2& from, const Vector2& to, std::vector<Vector2>& path);
	int AddNode(const Vector2& pos);
	void AddEdge(int u, int v, int weight);

	void Dijkstra(int sourceIndex);
	std::vector<int> GetPreviousPath()const { return m_Prevs; }
	std::vector<Node> GetNodes()const { return m_Nodes; }
	int GetNodeID(const Vector2& pos);

	int ClosestNodeIndexToPosition(const Vector2& pos);
	void SetAmountOfVertices(int value) { m_AmountOfVertices = value; };
private:
	int m_AmountOfVertices;

	// In a weighted graph, we need to store vertex
	// and weight pair for every edge
	std::vector<Node> m_Nodes;
	std::vector<int> m_Dists;
	std::vector<int> m_Prevs;
	std::vector<int> m_Queue;
};

