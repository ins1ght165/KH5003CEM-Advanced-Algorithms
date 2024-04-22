#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    // Duplicate character array
    char arr[] = { 'X', 'Y', 'Y', 'X', 'Z', 'X' };
    int Size = sizeof(arr) / sizeof(arr[0]);

    // Sorting the array before applying the unique function
    sort(arr, arr + Size);

    // Using unique to remove duplicate characters.
    auto End = unique(arr, arr + Size);

    // Calculating the new size of the array.
    int Size2 = End - arr;

    // Check if there were duplicate values.
    bool duplicates = Size2 < Size;

    // Printing the array before removing duplicates
    cout << "Character array before removing duplicates: ";
    for (int i = 0; i < Size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // If there were duplicates
    if (duplicates == true) {
        cout << "There were duplicate values in the array." << endl;

        // Creating a new vector to hold the unique elements (We have to use vectors since we cannot use a non static variable like size 2. Vectors allow us to change the size in runtime)
        vector<char> newArr(arr, arr + Size2);

        // Printing the results after removing duplicate characters
        cout << "Character array after removing duplicate characters: ";
        for (char c : newArr) {
            cout << c << " ";
        }
        cout << endl;
    }
    // In case there were no duplicate characters
    else {
        cout << "There were no duplicate characters in the array." << endl;
    }

    return 0;
}
