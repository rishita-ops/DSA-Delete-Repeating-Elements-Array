#include <iostream>
using namespace std;
int main()
{   
    int arr[5] = {10, 20, 30, 20, 40};
    int n = 5; 
    int newArr[5];
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }
        if (count == 1)
        {
            newArr[newSize] = arr[i];
            newSize++;
        }
    }

    for (int i = 0; i < newSize; i++)
    {
        cout << newArr[i] << " ";
    }
    cout << endl;
    return 0;
}