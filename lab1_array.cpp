#include<iostream>
#include<vector>
using namespace std;

template<class T>
class List
{
private:
    vector<T> data;
    int curr;
    int listSize;
    int maxSize;

    void resize(int newSize)  
    {
        data.resize(newSize);
        maxSize = newSize;
    }

public:
    List(int max) :maxSize(max + 10), listSize(0)
    {
        data.resize(max + 10);
        curr = 0;
    }

    void init(vector<T> init)//初始化数组：时间复杂度O(n)
    {
        for (int i = 0; i < init.size(); i++)  
        {
            data[i] = init[i];
            listSize++;
        }
    }

    void insert(int pos, T value)//在给定位置插入元素：时间复杂度O(n)
    {
        if (listSize >= maxSize)
        {
            resize(maxSize + 10);
        }

        for (int i = listSize; i > pos; i--)
        {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        listSize++;
    }

    T remove(int pos)//在给定位置删除元素：时间复杂度O(n)
    {
        if (pos < 0 || pos >= listSize)
        {
            return T();
        }

        T temp = data[pos];
        for (int i = pos; i < listSize - 1; i++)
        {
            data[i] = data[i + 1];
        }
        listSize--;
        return temp;
    }

    T find(int num)
    {
        if (num >= 0 && num < listSize)
        {
            return data[num];
        }
        else
        {
            cout << "invalid number!" << endl;
            return T();
        }
    }

    void clear()
    {
        data.clear();
        listSize = 0;
        curr = 0;
        data.resize(10);
        maxSize = 10;
    }

    void ForwardTraversal()
    {
        for (int i = 0; i < listSize; i++)
        {
            cout << data[i] << " ";
        }
    }

    void BackwardTraversal()
    {
        for (int i = listSize - 1; i >= 0; i--)
        {
            cout << data[i] << " ";
        }
    }

    T update(int pos, T value)//在给定位置更新元素：时间复杂度O(1)
    {
        if (pos < 0 || pos >= listSize)  
        {
            return T();
        }
        T temp = data[pos];
        data[pos] = value;
        return temp;
    }

    void print()//输出元素：时间复杂度O(n)
    {
        for (int i = 0; i < listSize; i++)
        {
            cout << data[i] << " ";
        }
    }

    static void testList()  
    {
        List<string> list(10);  
        vector<string> data = { "SID1","SID2","SID3","SID4" };
        list.init(data);

        cout << "Initial List: ";
        list.print();

        list.insert(2, "SID5");
        cout << "After Insert: ";
        list.print();

        list.remove(1);
        cout << "After Remove: ";
        list.print();

        cout << "Find at index 2: " << list.find(2) << endl;

        list.update(0, "SID0");
        cout << "After Update Location 0: ";
        list.print();
    }
};

int main()
{
    List<string>::testList();
}
