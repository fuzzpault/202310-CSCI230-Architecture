/*
Name: Paul Talaga
Date: Sept 13, 2023
Description: Demonstrates storing function pointers in an array.

https://www.geeksforgeeks.org/function-pointer-in-cpp/
*/

#include <chrono>
#include <iostream>

using namespace std;

// Example function
void add(int a, int b) {
  cout << "Add function" << a << " + " << b << " = " << a + b << endl;
}

void subtract(int a, int b) {
  cout << "Sub function" << a << " - " << b << " = " << a - b << endl;
}

void multiply(int a, int b) {
  cout << "Mul function" << a << " x " << b << " = " << a * b << endl;
}

int main() {
    void (*fn[4])(int, int) = {add, subtract, multiply, add};

    for(int i = 0; i < 4; i++){
      (*fn[i])(5, 6);
    }
}