#include<iostream>
using namespace std;

template<class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& value) :data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    LinkedList() :head(nullptr), tail(nullptr), listSize(0) {}

    ~LinkedList()
    {
        clear();
    }

    void init(T value)//初始化：时间复杂度O(1)
    {
        clear();

        head = new Node(value);
        tail = head;
        listSize = 1;
    }

    bool insert(int pos, const T& value)//特定位置插入：时间复杂度O(n)
    {
        if (pos<0 || pos>listSize)
        {
            cout << "invalid position" << endl;
            return false;
        }

        Node* newNode = new Node(value);

        if (pos == 0)
        {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr)
            {
                tail = newNode;
            }
        }

        else if (pos == listSize)
        {
            tail->next = newNode;
            tail = newNode;
        }

        else
        {
            Node* current = head;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }

        listSize++;
        return true;
    }

    bool remove(int pos)//特定位置删除：时间复杂度O(n)
    {
        if (pos<0 || pos>listSize || head == nullptr)
        {
            cout << "invalid position" << endl;
            return false;
        }

        Node* temp = nullptr;

        if (pos == 0)
        {
            temp = head;
            head = head->next;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }

        else
        {
            Node* current = head;
            for (int i = 0; i < pos - 1; i++)
            {
                current = current->next;
            }

            temp = current->next;
            current->next = temp->next;

            if (temp == tail)
            {
                tail = current;
            }
        }

        delete temp;
        listSize--;
        return true;
    }

    T find(int pos) const//特定位置查找：时间复杂度O(n)
    {
        if (pos < 0 || pos >= listSize)
        {
            throw out_of_range("invalid position");
        }

        Node* current = head;
        for (int i = 0; i < pos && current != nullptr; i++)
        {
            current = current->next;
        }

        if (current)
        {
            return current->data;
        }

        throw out_of_range("invalid position");
    }

    bool update(int pos, const T& value)//特定位置更新：时间复杂度O(n)
    {
        if (pos < 0 || pos >= listSize)
        {
            cout << "invalid position." << endl;
            return false;
        }

        Node* current = head;
        for (int i = 0; i < pos && current != nullptr; i++)
        {
            current = current->next;
        }

        if (current)
        {
            current->data = value;
            return true;
        }

        cout << "invalid position." << endl;
        return false;
    }

    void clear()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        listSize = 0;
    }

    void print()//输出：时间复杂度O(n)
    {
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    LinkedList<string> list;
    list.init("SID1");
    list.insert(1, "SID2");
    list.insert(2, "SID3");

    cout << "Initial List: ";
    list.print();

    list.insert(2, "SID4");
    cout << "After Insert: ";
    list.print();

    list.remove(1);
    cout << "After Remove: ";
    list.print();

    cout << "Find at index 1: " << list.find(1) << endl;

    list.update(0, "SID0");
    cout << "After Update Location 0: ";
    list.print();

    return 0;
}
