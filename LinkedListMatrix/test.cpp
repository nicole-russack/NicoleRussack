
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "spmat.h"
using namespace std;

struct Node {
    int val;
    Node*  next;
};

Node* llrec(Node* in1, Node* in2)
{
    if(in1 == nullptr) {
        return in2;
    }
    else if(in2 == nullptr) {
        return in1;
    }
    else {
        in1->next = llrec(in2, in1->next);
        return in1;
    }
}

int main()
{
Node* in1 = nullptr;
Node in2;
Node* ptr = &in2;
in2.val = 2;
in2.next = nullptr;
cout << llrec(in1, ptr) << endl;
return;


}
