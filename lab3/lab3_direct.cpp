#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class WeightedGraph
{
private:
    struct Edge
    {
        int to;
        int weight;
    };

    struct Node
    {
        int data;
        vector<Edge> edges;
    };

    vector<Node> nodes;

    int findNodeIndex(int node)//找到节点对应的标签:O(n)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].data == node)
            {
                return i;
            }
        }
        return -1;
    }

public:
    void insertNode(int node)//插入节点:O(n)
    {
        if (findNodeIndex(node) == -1)
        {
            Node newNode;
            newNode.data = node;
            nodes.push_back(newNode);
        }
    }

    void insertEdge(int node1, int node2, int weight)//插入边:O(n)
    {
        insertNode(node1);
        insertNode(node2);

        int idx1 = findNodeIndex(node1);
        int idx2 = findNodeIndex(node2);

        Edge edge1;
        edge1.to = node2;
        edge1.weight = weight;
        nodes[idx1].edges.push_back(edge1);

        Edge edge2;
        edge2.to = node1;
        edge2.weight = weight;
        nodes[idx2].edges.push_back(edge2);
    }

    void updateEdge(int node1, int node2, int newWeight)//更新边的权重:O(n)
    {
        int idx1 = findNodeIndex(node1);
        int idx2 = findNodeIndex(node2);

        if (idx1 != -1)
        {
            for (int i = 0; i < nodes[idx1].edges.size(); i++)
            {
                if (nodes[idx1].edges[i].to == node2) {
                    nodes[idx1].edges[i].weight = newWeight;
                    break;
                }
            }
        }
        if (idx2 != -1)
        {
            for (int i = 0; i < nodes[idx2].edges.size(); i++) {
                if (nodes[idx2].edges[i].to == node1) {
                    nodes[idx2].edges[i].weight = newWeight;
                    break;
                }
            }
        }
    }

    bool findNode(int node)//寻找节点:O(n)
    {
        return findNodeIndex(node) != -1;
    }

    pair<bool, int> findEdge(int node1, int node2)
    {
        int idx1 = findNodeIndex(node1);
        if (idx1 != -1)
        {
            for (int i = 0; i < nodes[idx1].edges.size(); i++)
            {
                if (nodes[idx1].edges[i].to == node2)
                {
                    return make_pair(true, nodes[idx1].edges[i].weight);
                }
            }
        }
        return make_pair(false, 0);
    }

    void displayGraph()//输出图:O(n)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i].data << ": ";
            for (int j = 0; j < nodes[i].edges.size(); j++)
            {
                cout << "(" << nodes[i].edges[j].to << "," << nodes[i].edges[j].weight << ") ";
            }
            cout << endl;
        }
    }

private:
    // DFS辅助函数
    void DFSHelper(int nodeIdx, vector<bool>& visited)
    {
        visited[nodeIdx] = true;
        cout << nodes[nodeIdx].data << " ";

        for (int i = 0; i < nodes[nodeIdx].edges.size(); i++)
        {
            int neighborData = nodes[nodeIdx].edges[i].to;
            int neighborIdx = findNodeIndex(neighborData);
            if (neighborIdx != -1 && !visited[neighborIdx])
            {
                DFSHelper(neighborIdx, visited);
            }
        }
    }

public:
    // 深度优先搜索 - 时间复杂度: O(V + E)，V为节点数，E为边数
    // 空间复杂度: O(V)，用于visited数组和递归栈
    void DFS(int startNode)
    {
        int startIdx = findNodeIndex(startNode);
        if (startIdx == -1)
        {
            cout << "起始节点不存在" << endl;
            return;
        }

        vector<bool> visited(nodes.size(), false);
        cout << "DFS遍历结果: ";
        DFSHelper(startIdx, visited);
        cout << endl;
    }

    // 广度优先搜索 - 时间复杂度: O(V + E)，V为节点数，E为边数
    // 空间复杂度: O(V)，用于visited数组和队列
    void BFS(int startNode)
    {
        int startIdx = findNodeIndex(startNode);
        if (startIdx == -1)
        {
            cout << "起始节点不存在" << endl;
            return;
        }

        vector<bool> visited(nodes.size(), false);
        queue<int> q;

        visited[startIdx] = true;
        q.push(startIdx);
        cout << "BFS遍历结果: ";

        while (!q.empty())
        {
            int currentIdx = q.front();
            q.pop();
            cout << nodes[currentIdx].data << " ";

            for (int i = 0; i < nodes[currentIdx].edges.size(); i++)
            {
                int neighborData = nodes[currentIdx].edges[i].to;
                int neighborIdx = findNodeIndex(neighborData);
                if (neighborIdx != -1 && !visited[neighborIdx])
                {
                    visited[neighborIdx] = true;
                    q.push(neighborIdx);
                }
            }
        }
        cout << endl;
    }

    // Dijkstra算法 - 时间复杂度: O(V^2)，可用优先队列优化到O((V+E)logV)
    // 空间复杂度: O(V)，用于距离数组和访问标记
    void Dijkstra(int startNode)
    {
        int startIdx = findNodeIndex(startNode);
        if (startIdx == -1)
        {
            cout << "起始节点不存在" << endl;
            return;
        }

        const int INF = 1e9;
        vector<int> dist(nodes.size(), INF);
        vector<bool> visited(nodes.size(), false);

        dist[startIdx] = 0;

        for (int count = 0; count < nodes.size(); count++)
        {
            int minDist = INF;
            int minIdx = -1;

            // 找到未访问节点中距离最小的
            for (int i = 0; i < nodes.size(); i++)
            {
                if (!visited[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    minIdx = i;
                }
            }

            if (minIdx == -1) break;

            visited[minIdx] = true;

            // 更新相邻节点的距离
            for (int i = 0; i < nodes[minIdx].edges.size(); i++)
            {
                int neighborData = nodes[minIdx].edges[i].to;
                int neighborIdx = findNodeIndex(neighborData);
                int weight = nodes[minIdx].edges[i].weight;

                if (neighborIdx != -1 && !visited[neighborIdx])
                {
                    if (dist[minIdx] + weight < dist[neighborIdx])
                    {
                        dist[neighborIdx] = dist[minIdx] + weight;
                    }
                }
            }
        }

        // 输出结果
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << "从节点 " << startNode << " 到节点 " << nodes[i].data << " 的最短路径: ";
            if (dist[i] == INF)
                cout << "无法到达" << endl;
            else
                cout << dist[i] << endl;
        }
    }
};
