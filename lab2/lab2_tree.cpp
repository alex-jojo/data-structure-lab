#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

// 节点结构
struct TreeNode
{
    string s;
    TreeNode* left;
    TreeNode* right;
    int signed_hash;  // 哈希值成员变量

    // 构造函数：在创建节点时计算哈希值
    TreeNode(string x) : s(x), left(nullptr), right(nullptr) {
        std::hash<std::string> hash_fn;
        size_t hash_value = hash_fn(x);
        signed_hash = static_cast<int>(hash_value);
    }
};

class KnowledgeBaseBST
{
private:
    TreeNode* root;

    // 修改：按照哈希值比较而不是字符串比较
    TreeNode* insertHelper(TreeNode* node, string s)
    {
        if (node == nullptr)
        {
            return new TreeNode(s);
        }

        // 计算当前插入字符串的哈希值
        std::hash<std::string> hash_fn;
        int current_hash = static_cast<int>(hash_fn(s));
        int node_hash = node->signed_hash;

        // 按照哈希值比较
        if (current_hash < node_hash)
        {
            node->left = insertHelper(node->left, s);
        }
        else if (current_hash > node_hash)
        {
            node->right = insertHelper(node->right, s);
        }
        else
        {
            // 哈希冲突时按字符串比较（理论上很少发生）
            if (s < node->s)
            {
                node->left = insertHelper(node->left, s);
            }
            else
            {
                node->right = insertHelper(node->right, s);
            }
        }

        return node;
    }

    TreeNode* findHelper(TreeNode* node, string s)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->s == s)
        {
            return node;
        }

        // 在BST中查找，需要同时检查左右子树
        TreeNode* leftResult = findHelper(node->left, s);
        if (leftResult != nullptr)
        {
            return leftResult;
        }

        return findHelper(node->right, s);
    }

    TreeNode* findMin(TreeNode* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    TreeNode* removeHelper(TreeNode* node, string s)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        // 先找到要删除的节点
        if (s < node->s)  // 这里按字符串查找要删除的节点
        {
            node->left = removeHelper(node->left, s);
        }
        else if (s > node->s)
        {
            node->right = removeHelper(node->right, s);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                TreeNode* minNode = findMin(node->right);
                node->s = minNode->s;
                node->signed_hash = minNode->signed_hash;
                node->right = removeHelper(node->right, minNode->s);
            }
        }
        return node;
    }

    // 中序遍历输出哈希值
    void inOrderHashHelper(TreeNode* node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderHashHelper(node->left);
        cout << node->signed_hash << " ";
        inOrderHashHelper(node->right);
    }

    // 中序遍历输出字符串
    void inOrderStringHelper(TreeNode* node)
    {
        if (node == nullptr)
        {
            return;
        }
        inOrderStringHelper(node->left);
        cout << node->s << " ";
        inOrderStringHelper(node->right);
    }

public:
    KnowledgeBaseBST() : root(nullptr) {}

    void insertEntry(string s)
    {
        root = insertHelper(root, s);
        cout << "Inserted entry: " << s << " with hash value: "
            << static_cast<int>(std::hash<std::string>{}(s)) << endl;
    }

    void findEntry(string s)
    {
        TreeNode* result = findHelper(root, s);
        if (result != nullptr)
        {
            cout << "Entry: " << s << " (" << result->signed_hash << ") Found" << endl;
        }
        else
        {
            cout << "Entry: " << s << " Not Found" << endl;
        }
    }

    void removeEntry(string s)
    {
        TreeNode* target = findHelper(root, s);
        if (target != nullptr)
        {
            cout << "Removed entry: " << s << " with hash value: " << target->signed_hash << endl;
            root = removeHelper(root, s);
        }
        else
        {
            cout << "Entry: " << s << " Not Found, cannot remove" << endl;
        }
    }

    void displayEntriesByHash()
    {
        cout << "In-order traversal of entries (sorted by hash value): ";
        inOrderHashHelper(root);
        cout << endl;
    }

    void displayEntriesByString()
    {
        cout << "In-order traversal of entries (sorted by string): ";
        inOrderStringHelper(root);
        cout << endl;
    }

public:
    static void testKnowledgeBaseBST()
    {
        cout << "===知识库管理示例===" << endl;
        KnowledgeBaseBST knowledgeBase;

        knowledgeBase.insertEntry("Artificial Intelligence");
        knowledgeBase.insertEntry("Machine Learning");
        knowledgeBase.insertEntry("Deep Learning");
        knowledgeBase.insertEntry("Neural Networks");
        knowledgeBase.insertEntry("Natural Language Processing");

        // 显示按哈希值排序的中序遍历
        knowledgeBase.displayEntriesByHash();

        knowledgeBase.findEntry("Machine Learning");
        knowledgeBase.removeEntry("Deep Learning");

        // 删除后的显示
        knowledgeBase.displayEntriesByHash();

        return;
    }
};

int main()
{
    KnowledgeBaseBST::testKnowledgeBaseBST();
}
