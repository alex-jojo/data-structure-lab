#include <iostream>
using namespace std;

template <class T>

class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(const T&value):data(value),next(nullptr),prev(nullptr){}
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    DoublyLinkedList():head(nullptr),tail(nullptr),listSize(0){}

    ~DoublyLinkedList()
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

    bool insert(int pos, const T& value)//在指定节点处插入：时间复杂度O(n)
    {
        if (pos<0 || pos>listSize)
        {
            cout << "invalid position" << endl;
            return false;
        }

        Node* newNode = new Node(value);
        if (listSize == 0)
        {
            head = newNode;
            tail = newNode;
        }

        else if (pos == 0)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        else if (pos == listSize)
        {
            tail->next = newNode;
            newNode->prev = tail;
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
            newNode->prev = current;
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
            head->prev = nullptr;
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

    void printForward()//正向遍历打印链表：时间复杂度O(n)
    {
        Node* current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printBackward()//反向遍历打印链表：时间复杂度O(n)
    {
        Node* current = tail;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    static void testDoublyLinkedList()
    {
        DoublyLinkedList list;

        list.init("SID1");

        list.insert(1, "SID2");
        list.insert(2, "SID3");
        list.insert(3, "SID4");

        cout << "Forward Traversal: ";
        list.printForward();

        cout << "BackWard Traversal: ";
        list.printBackward();

        list.insert(2, "SID5");
        cout << "After Insert: ";
        list.printForward;

        cout << "Element at index 2: " << list.find(2) << endl;

        list.update(2, "SID6");
        cout << "After Update: ";
        list.printForward();

        list.remove(1);
        cout << "After Remove: ";
        list.printForward();
    }
};

int main()
{
    DoublyLinkedList<string> list;

    list.init("SID1");

    list.insert(1, "SID2");
    list.insert(2, "SID3");
    list.insert(3, "SID4");

    cout << "Forward Traversal: ";
    list.printForward();

    cout << "BackWard Traversal: ";
    list.printBackward();

    list.insert(2, "SID5");
    cout << "After Insert: ";
    list.printForward();

    cout << "Element at index 2: " << list.find(2) << endl;

    list.update(2, "SID6");
    cout << "After Update: ";
    list.printForward();

    list.remove(1);
    cout << "After Remove: ";
    list.printForward();

}
