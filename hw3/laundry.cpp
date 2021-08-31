#include <iostream>
#include <fstream>
#include "stack.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide the input and output filenames" << endl;
    return 1;
  }
  // Add your code here

  //use input file to get
  ifstream ifile(argv[1]);
  if (ifile.fail()) {
    cerr << "Unable to open " << argv[1] << endl;
    return true;
  }
  string line_one;
  getline(ifile, line_one);
  stringstream line_ss;
  line_ss.str(line_one);
  int next_num;
  Stack<int> stack;
  ofstream outputfile(argv[2]);
  while(line_ss >> next_num){
    if(next_num < 1){
      stack.push(next_num);
    }
    else{
      while(next_num > 0 && stack.size() != 0){
        if(stack.top() == -1){
            outputfile << "gray ";      
    }
    else if(stack.top() == 0){
            outputfile << "black ";
       }
        stack.pop();
        next_num --;
      }
      outputfile << endl;
    }
    
  }

  /*ofstream outputfile(argv[2]);
  while(stack.size() != 0){
    if(stack.top() == -1){
     outputfile << "grey towl";      
    }
    else if(stack.top() == 0){
      outputfile << "black towl";
    }
    stack.pop();
  }*/
  return 0;
}
