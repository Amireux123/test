#include "myarray.hpp"

int main()
{
    try
    {
        MyArray<int> arr;
        cout << arr.capcaity() << endl;
    
        while (1)
        {
            int data;
            cin >> data;
            if(data == -666)
            {
                break;
            }

            arr.push(data);
        }

        arr.at(4) = 1024;
        // arr.delete_pos(13);
        
        //通过迭代器来访问数组中的元素
        for (MyArray<int>::iterator it = arr.begin(); it != arr.end(); ++it)
        {
            cout << *it << " ";
        }
        cout << endl;

        cout << arr.capcaity() << endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
   
    return 0;
}