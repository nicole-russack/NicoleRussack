#include <iostream>
#include <fstream>
#include "stack.h"
#include <sstream>

using namespace std;

int main(){

   
    Stack<int> myStack;
   
    cout << myStack.empty() << endl;
    myStack.push(7);
    myStack.push(8);
    myStack.push(9);
    cout << "is empty "<< myStack.empty() << endl;

    cout <<  myStack.top() << endl;
    cout << "there are " << myStack.size() << " items" << endl;
    myStack.pop();
    cout <<  myStack.top() << endl;
    cout << "there are " << myStack.size() << " items" << endl;
    myStack.pop();
    cout <<  myStack.top() << endl;
    cout << "there are " << myStack.size() << " items" << endl;
    myStack.pop();
    cout << "is empty "<< myStack.empty() << endl;
    //myStack.pop();
    cout << "there are " << myStack.size() << " items" << endl;





    myStack.push(9);
    cout <<  myStack.top() << endl;
    cout << myStack.empty() << endl;
    cout << "there are " << myStack.size() << " items" << endl;
    myStack.push(10);
    cout << "there are " << myStack.size() << " items" << endl;
    //myStack.pop();
    cout << "there are " << myStack.size() << " items" << endl;



    //cout << "helloooo" << endl;
    //cout << "Make file is correct" << endl;




    return 1;
}
