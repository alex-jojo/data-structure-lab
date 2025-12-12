#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UndirectedGraph
{
private:
    struct Node//节点的结构
    {
        int data;
        vector<int> neighbors;
    };
    vector<Node> nodes;
    
    int findNodeIndex(int node)//O(n)
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

    void insertEdge(int node1, int node2)//插入边:O(n)
    {
        insertNode(node1);
        insertNode(node2);

        int idx1 = findNodeIndex(node1);
        int idx2 = findNodeIndex(node2);

        nodes[idx1].neighbors.push_back(node2);
        nodes[idx2].neighbors.push_back(node1);
    }

    void removeEdge(int node1, int node2)//删除边:O(n)
    {
        int idx1 = findNodeIndex(node1);
        int idx2 = findNodeIndex(node2);

        if (idx1 != -1) {
            nodes[idx1].neighbors.erase(
                remove(nodes[idx1].neighbors.begin(), nodes[idx1].neighbors.end(), node2),
                nodes[idx1].neighbors.end()
            );
        }
        if (idx2 != -1) {
            nodes[idx2].neighbors.erase(
                remove(nodes[idx2].neighbors.begin(), nodes[idx2].neighbors.end(), node1),
                nodes[idx2].neighbors.end()
            );
        }
    }

    bool findNode(int node)//查找节点:O(n)
    {
        return findNodeIndex(node) != -1;
    }

    bool findEdge(int node1, int node2)
    {
        int idx1 = findNodeIndex(node1);
        if (idx1 != -1)
        {
            return find(nodes[idx1].neighbors.begin(), nodes[idx1].neighbors.end(), node2) != nodes[idx1].neighbors.end();
        }
        return false;
    }

    void displayGraph()//输出图:O(n)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i].data << ":";
            for (int j = 0; j < nodes[i].neighbors.size(); j++)
            {
                cout << nodes[i].neighbors[j] << " ";
            }
            cout << endl;
        }
    }
};

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

};

int main()
{
    UndirectedGraph undirectedGraph;

    cout << "无向无权图操作示例：" << endl;
    undirectedGraph.insertNode(1);
    undirectedGraph.insertNode(2);
    undirectedGraph.insertNode(3);

    undirectedGraph.insertEdge(1, 2);
    undirectedGraph.insertEdge(1, 3);
    undirectedGraph.displayGraph();

    cout << "查找结点1：" << undirectedGraph.findNode(1) << endl;
    cout << "查找边1-2：" << undirectedGraph.findEdge(1, 2) << endl;

    WeightedGraph weightedGraph;

    cout << "无向无权图操作示例：" << endl;
    weightedGraph.insertNode(1);
    weightedGraph.insertNode(2);
    weightedGraph.insertNode(3);

    weightedGraph.insertEdge(1, 2, 5);
    weightedGraph.insertEdge(1, 3, 2);
    weightedGraph.displayGraph();

    cout << "查找结点1：" << weightedGraph.findNode(1) << endl;
    auto edgeResult = weightedGraph.findEdge(1, 2);
    cout << "查找边1-2：" << edgeResult.first << endl;

    weightedGraph.updateEdge(1, 2, 10);
    weightedGraph.displayGraph();
}

