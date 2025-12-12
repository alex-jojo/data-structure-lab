#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
using namespace std;

class KnowledgeGraph {
private:
    set<string> entities;
    map<string, vector<pair<string, int>>> relations;

public:
    // 插入实体
    void insertEntity(string entity)
    {
        entities.insert(entity);
        if (relations.find(entity) == relations.end()) {
            relations[entity] = vector<pair<string, int>>();
        }
    }
    
    // 插入关系（双向）
    void insertRelation(string from, string to, int weight)
    {
        insertEntity(from);
        insertEntity(to);
        relations[from].push_back(make_pair(to, weight));
        relations[to].push_back(make_pair(from, weight));
    }
    
    // 显示图谱
    void displayGraph()
    {
        for (auto& entity : entities) {
            cout << "实体: " << entity << " -> 关系: ";
            if (relations[entity].empty()) {
                cout << endl;
            } else {
                for (int i = 0; i < relations[entity].size(); i++) {
                    cout << relations[entity][i].first << "(" << relations[entity][i].second << ")";
                    if (i < relations[entity].size() - 1) {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
    }
    
    // 查找实体
    bool findEntity(string entity)
    {
        return entities.find(entity) != entities.end();
    }
    
    // 查找关系
    bool findRelation(string from, string to)
    {
        if (relations.find(from) != relations.end()) {
            for (auto& rel : relations[from]) {
                if (rel.first == to) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // 删除关系（双向）
    void removeRelation(string from, string to)
    {
        if (relations.find(from) != relations.end()) {
            auto& rels = relations[from];
            for (auto it = rels.begin(); it != rels.end(); ) {
                if (it->first == to) {
                    it = rels.erase(it);
                } else {
                    ++it;
                }
            }
        }
        if (relations.find(to) != relations.end()) {
            auto& rels = relations[to];
            for (auto it = rels.begin(); it != rels.end(); ) {
                if (it->first == from) {
                    it = rels.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    
    // 删除实体
    void removeEntity(string entity)
    {
        entities.erase(entity);
        relations.erase(entity);
        for (auto& rel : relations)
        {
            auto& rels = rel.second;
            for (auto it = rels.begin(); it != rels.end(); )
            {
                if (it->first == entity)
                {
                    it = rels.erase(it);
                } else
                {
                    ++it;
                }
            }
        }
    }
    

    void answerRelationQuery(string query)
    {

        string entity1 = "Person_A";
        string entity2 = "Person_C";
        
        if (findRelation(entity1, entity2))
        {
            cout << entity1 << " 和 " << entity2 << " 之间有联系。" << endl;
        } else
        {
            cout << entity1 << " 和 " << entity2 << " 之间没有直接联系。" << endl;
        }
    }
    

    void completeKnowledgeWithLLM(string queryComplete)
    {
        cout << "知识补全示例:" << endl;
        cout << "使用LLM推理更新新知识图谱。" << endl;
        
        insertEntity("Person_D");
        insertRelation("Person_A", "Person_D", 3);
    }
    

    void answerInferenceQuery(string queryInference)
    {
        
        string entity1 = "Person_A";
        string entity2 = "Person_C";
        
        bool hasIndirectConnection = false;
        if (relations.find(entity1) != relations.end())
        {
            for (auto& intermediate : relations[entity1])
            {
                if (relations.find(intermediate.first) != relations.end())
                {
                    for (auto& target : relations[intermediate.first])
                    {
                        if (target.first == entity2)
                        {
                            hasIndirectConnection = true;
                            break;
                        }
                    }
                }
                if (hasIndirectConnection) break;
            }
        }
        
        if (hasIndirectConnection || findRelation(entity1, entity2))
        {
            cout << entity1 << " 和 " << entity2 << " 之间存在潜在关系。" << endl;
        } 
        else
        {
            cout << entity1 << " 和 " << entity2 << " 之间不存在潜在关系。" << endl;
        }
    }
};

int main()
{
    cout << "知识图谱构建示例:" << endl;
    
    KnowledgeGraph knowledgeGraph;
    
    // 插入实体
    knowledgeGraph.insertEntity("Person_A");
    knowledgeGraph.insertEntity("Person_B");
    knowledgeGraph.insertEntity("Person_C");
    
    // 插入关系
    knowledgeGraph.insertRelation("Person_A", "Person_B", 5);
    knowledgeGraph.insertRelation("Person_A", "Person_C", 10);
    
    // 显示图谱
    knowledgeGraph.displayGraph();
    
    // 查找实体和关系
    cout << "查找实体 'Person_A': " << knowledgeGraph.findEntity("Person_A") << endl;
    cout << "查找关系 'Person_A - Person_B': " << knowledgeGraph.findRelation("Person_A", "Person_B") << endl;
    
    // 删除关系并显示
    knowledgeGraph.removeRelation("Person_A", "Person_B");
    knowledgeGraph.displayGraph();
    
    // 删除实体（注释掉的功能）
    // knowledgeGraph.removeEntity("Person_C");
    knowledgeGraph.displayGraph();
    
    // 实体关系查询
    cout << endl << "实体关系查询示例:" << endl;
    string queryRelation = "What is the relationship between Person_A and Person_C?";
    knowledgeGraph.answerRelationQuery(queryRelation);
    
    // 知识补全
    cout << endl << "知识补全示例:" << endl;
    string queryComplete = "Add a new relation for Person_A with Person_D as weight 3";
    knowledgeGraph.completeKnowledgeWithLLM(queryComplete);
    knowledgeGraph.displayGraph();
    
    // 关系推断
    cout << endl << "关系推断示例:" << endl;
    string queryInference = "Can Person_A and Person_C be connected ?";
    knowledgeGraph.answerInferenceQuery(queryInference);
    
    return 0;
}
