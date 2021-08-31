#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
// for pair
#include <functional>
#include <string>

using namespace std;

// typedef for X,Y pair
typedef std::pair<size_t, size_t> XYPair;

// Utility Prototypes
bool operator==(const XYPair& p1, const XYPair& p2);
void printPaths(const std::vector<std::vector<XYPair> >& results);

// Utility function to compare XY points
bool operator==(const XYPair& p1, const XYPair& p2)
{
  return p1.first == p2.first && p1.second == p2.second;
}


// Primary street grid function prototype
std::vector<std::vector<XYPair> > gridpaths(const XYPair& inter, const XYPair& final);

// Prototype any helper functions here
void nextNode (const XYPair& current, const XYPair& intern, const XYPair& final, vector<XYPair>& list_one, std::vector<std::vector<XYPair> >& final_set);

void getToFinal(const XYPair& current, const XYPair& final, vector<XYPair>& list_one, std::vector<std::vector<XYPair> >& final_set);



// Returns a list of lists
std::vector<std::vector<XYPair> > gridpaths(
    const XYPair& inter, 
    const XYPair& final)
{
  vector<vector<XYPair> > start_set;
  vector<vector<XYPair> > finishing_set;
  vector<XYPair> blank_list;

  XYPair startNode;
  startNode.first = 0;
  startNode.second = 0;
  nextNode (startNode, inter, final, blank_list, start_set);
  //nextNode (inter, final, list_one, final_set);

  
  return start_set;
  
  


}


//returns a single node
void nextNode (const XYPair& current, const XYPair& intern, const XYPair& final, vector<XYPair>& list_one, std::vector<std::vector<XYPair> >& final_set){
  
  //if we are done with this set then we add the last element and return it.
  if(current == intern && intern != final){
    nextNode(current, final, final, list_one, final_set);
    return;

  }
  else if(current == intern && intern == final){
    if(final.first != 0 || final.second != 0){
      list_one.push_back(current);
    final_set.push_back(list_one);
    }
    return;

  }
  //Can only go up 
  // x values are the same and update y
  else if(current.first == intern.first){
    //add curent value to the set
    list_one.push_back(current);
    //recurse only 1 time on new set
    //only 1 time because there is only one way, two sets are not being made
    XYPair newNode;
    newNode.first = current.first;
    newNode.second = current.second + 1;
    nextNode (newNode, intern, final, list_one, final_set);
    return;

  }
  //can only go right
  // y values are the same and update x
  else if(current.second == intern.second){
    //add curent value to the set
    list_one.push_back(current);
    //recurse only 1 time on new set
    //only 1 time because there is only one way, two sets are not being made
    XYPair newNode;
    newNode.first = current.first + 1;
    newNode.second = current.second;
    nextNode (newNode, intern, final, list_one, final_set);
    return;

  }
  //can go both
  //must make 2 new lists and recurse twice now
  else{
    //add curent value to the set
    list_one.push_back(current);
    //recurse only 1 time on new set
    //only 1 time because there is only one way, two sets are not being made
    XYPair newNode1;
    newNode1.first = current.first + 1;
    newNode1.second = current.second;
    XYPair newNode2;
    newNode2.first = current.first;
    newNode2.second = current.second + 1;

    vector<XYPair> list_two = list_one;
    nextNode (newNode1, intern, final, list_one, final_set);
    nextNode (newNode2, intern, final, list_two, final_set);
    return;

  }
  return;
}




// Complete - but can be changed for debugging purposes
int main(int argc, char* argv[])
{
  // Default to intermediate point of 2,3 and final location of 3,4
  size_t ix = 0, iy = 0, fx = 0, fy = 0;
  if(argc >= 5) {
    ix = atoi(argv[1]);
    iy = atoi(argv[2]);
    fx = atoi(argv[3]);
    fy = atoi(argv[4]);
  }
  vector<vector<XYPair> > results;
  results = gridpaths({ix,iy},{fx,fy});  
  printPaths(results);

  return 0;
}

// Prints the results in a clean fashion for human consumption / debugging
void printPaths(const vector<vector<XYPair> >& results)
{
  for( const auto& path : results) {
    for( size_t i = 0; i < path.size()-1; i++ ) 
    {      
      cout << path[i].first << "," << path[i].second << " -> ";
    }
    cout << path.back().first << "," << path.back().second << endl;
  }
  cout << results.size() << " solutions." << endl;

}
