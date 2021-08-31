#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rem_dup_lib.h"

using namespace std;

void deleteList(Item* head);
// helper function for debugging
void outputList(ostream& os, Item* head);


// Add implementation of a readlists function such as:
void readLists(const char* filename, Item*& head1, Item*& head2);
// or
// void readLists(char* filename, Item** head1, Item** head2);






// Output function for debug or writing output
void outputList(ostream& os, Item* head)
{
  for(Item* temp = head; temp; temp=temp->next){
    os << temp->val << " ";
  }
  os << endl;
}

// Deallocate memory for a list
void deleteList(Item* head)
{
  if(head==nullptr) return;
  else {
    deleteList(head->next);
    delete head;
  }
}

void readLists(const char* filename, Item*& head1, Item*& head2){
  string lineone;
  string linetwo;
  ifstream ifile(filename);
  getline(ifile, lineone);
  getline(ifile, linetwo);
  if(lineone.length() == 0){
    head1 = NULL;
  }
  else{
  stringstream lineone_ss;
  lineone_ss.str(lineone);
  int temp;
  lineone_ss >> temp;
  Item *newItem = new Item(temp, NULL);
  head1 = newItem;
  Item * tail =  newItem;
  while(lineone_ss >> temp){
    //cout << temp << " ";
    //new item with value temp
    Item *newItem = new Item(temp, NULL);
    //sets the old next value to the new ite,
    tail->next = newItem;
    //cout << temp_item_one->val << " ";
    //makes the tmep the new item
    tail = tail->next;
    //cout << temp_item_one->val << endl;

  }
  }
  stringstream linetwo_ss;
  if(linetwo.length() == 0){
    head2 = NULL;
  }
  else{
  int temp;
  linetwo_ss.str(linetwo);
  linetwo_ss >> temp;
  Item *newItem2 = new Item(temp, NULL);
  Item* temp_item = newItem2;
  head2 = temp_item;
  while(linetwo_ss >> temp){
    Item *newItem2 = new Item(temp, NULL);
    temp_item->next = newItem2;
    temp_item = temp_item ->next;
  }
  }

}


// Main test driver
int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage: ./remdup input_file output_file" << endl;
    return 1;
  }
  Item* head1, *head2;
  readLists(argv[1], head1, head2);

  // Uncomment to verify you read in the right values
    

  outputList(cout, head1);
  outputList(cout, head2);

  ofstream ofile(argv[2]);
  if(ofile.fail()){
    cerr << "Couldn't open output file " << argv[2] << endl;
  }
  
  removeConsecutive(head1);

  outputList(ofile, head1);


  // Uncomment to see intermediate results after removeConsecutive
  //outputList(ofile, head1);
  
  Item* head3 = concatenate(head1, head2);
  outputList(ofile, head3);
  
  ofile.close();

  // cleanup memory
  deleteList(head1);
  deleteList(head2);
  deleteList(head3);
  return 0;
}
