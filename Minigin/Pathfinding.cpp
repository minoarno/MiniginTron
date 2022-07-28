#include "MiniginPCH.h"
#include "Pathfinding.h"
#include <map>
#include <set>
#include <limits>
#include "HelperStructs.h"
#include "HelperFunctions.h"

Pathfinding::Pathfinding(int amountOfVertices)
    :m_AmountOfVertices{ amountOfVertices }
{

}

void Pathfinding::PathTo(const Vector2& from, const Vector2& to, std::vector<Vector2>& path)
{
    int srcIndex = ClosestNodeIndexToPosition(from);
    int toIndex = ClosestNodeIndexToPosition(to);
    Dijkstra(toIndex);


    std::vector<int> prevs{ GetPreviousPath() };
    std::vector<Node> nodes{ GetNodes() };
    int index{ srcIndex};

    path.clear();
    while (index != toIndex)
    {
        path.emplace_back(nodes[index].position);
        index = prevs[index];
    }
    path.emplace_back(nodes[toIndex].position);
}

int Pathfinding::AddNode(const Vector2& pos)
{
    Node node{};
    node.position = pos;
    m_Nodes.emplace_back(node);
    m_AmountOfVertices++;
    return int(m_Nodes.size()) - 1;
}

void Pathfinding::AddEdge(int u, int v, int weight)
{
    m_Nodes[u].neighbours.emplace_back(std::make_pair(v, weight));
    m_Nodes[v].neighbours.emplace_back(std::make_pair(u, weight));
}


//https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
void Pathfinding::Dijkstra(int sourceIndex)
{
    //Dists
    m_Dists.clear();
    m_Dists.resize(m_AmountOfVertices, std::numeric_limits<int>::max());
    
    //Prevs
    m_Prevs.clear();

    m_Prevs.resize(m_AmountOfVertices, std::numeric_limits<int>::max());

    m_Queue.clear();
    m_Queue.reserve(m_AmountOfVertices);
    for (int i = 0; i < int(m_Nodes.size()); i++)
    {
        m_Queue.emplace_back(i);
    }
    m_Dists[sourceIndex] = 0;

    while (!m_Queue.empty())
    {
       int u = int(std::min_element(m_Dists.begin(), m_Dists.end()) - m_Dists.begin());

       if (u >= int(m_Queue.size())) break;

       m_Queue[u] = m_Queue.back();
       m_Queue.pop_back();

       for (int i = 0; i < int(m_Nodes[u].neighbours.size()); i++)
       {
           if (std::find(m_Queue.begin(), m_Queue.end(), m_Nodes[u].neighbours[i].first) == m_Queue.end()) continue;

           int alt = m_Dists[u] + m_Nodes[u].neighbours[i].second;
           if (alt < m_Dists[i] && m_Dists[u] != std::numeric_limits<int>::max())
           {
               m_Dists[i] = alt;
               m_Prevs[i] = u;
           }
       }
    }
}

int Pathfinding::GetNodeID(const Vector2& pos)
{
    return ClosestNodeIndexToPosition(pos);
}

int Pathfinding::ClosestNodeIndexToPosition(const Vector2& pos)
{
    int closestDistanceIndex = -1;
    int closestDistance = std::numeric_limits<int>::max();
    for (int i = 0; i < int(m_Nodes.size()); i++)
    {
        int distance = pos.x - m_Nodes[i].position.x + pos.y - m_Nodes[i].position.y;

        if (closestDistance > distance)
        {
            closestDistance = distance;
            closestDistanceIndex = i;
        }
    }
    return closestDistanceIndex;
}
