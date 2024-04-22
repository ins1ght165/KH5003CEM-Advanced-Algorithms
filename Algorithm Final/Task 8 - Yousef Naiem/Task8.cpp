#include <iostream>  
#include <thread>    
#include <vector>    
#include <iomanip>   
using namespace std; 

// This function here will multiply two numbers of both rows and then store the results in a seperate row
void add_multipication_matrix_row(int* mat1, int* mat2, int* result, int cols) {
    for (int c = 0; c < cols; c++) {  
        result[c] = mat1[c] * mat2[c];  
    }
}

// Function to print a matrix with a label
void printMatrix(int* matrix, int rows, int cols, const string& label) {
    cout << label << endl;  // Print the label for the matrix
    for (int r = 0; r < rows; r++) {  // Loop through each row
        for (int c = 0; c < cols; c++) {  // Loop through each column in the row
            cout << setw(4) << matrix[r * cols + c] << " ";  // Print each element with formatted width
        }
        cout << endl;  // New line after each row
    }
}

int main() {
    // Declaring a variable to hold the number of rows
    int rows = 3;  
    // Declaring a variable to hold the number of columns 
    int cols = 4;  
    // Then we will create both of our matrices and one to store all of the results. 
    int array1[3][4] = { {100, 20, 3, 50}, {40, 33, 56, 2}, {150, 23, 17, 22} };  
    int array2[3][4] = { {56, 13, 9, 100}, {22, 15, 55, 60}, {19, 200, 27, 14} };  
    int result[3][4]; 

    // Now we declare a vector to store the threads
    vector<thread> threads;  

    // This for loop will start a thread for each calculation that is done 
    for (int r = 0; r < rows; r++) {
        threads.push_back(thread(add_multipication_matrix_row, array1[r], array2[r], result[r], cols));
    }

    // This for loop will iterate over every thread and wait for all of the threads to finish so we can display all of the results
    // Since some threads may finish sooner we need to wait for all of them to finish
    for (auto& th : threads) {  
        th.join();  
    }

    // Now will will print out the all the rows including the result row.
    printMatrix(&array1[0][0], rows, cols, "Matrix 1:"); 
    cout << "         *\n";  
    printMatrix(&array2[0][0], rows, cols, "Matrix 2:");  
    cout << "         =\n";  
    printMatrix(&result[0][0], rows, cols, "Result:");  


}
