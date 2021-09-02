#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;
int main()
{
    HashTable<int, int, QuadraticProber, hash<int>, equal_to<int> > ht(0.8);
    //HashTable<int, int, QuadraticProber, IntHash2, equal_to<int> > ht(0.8, QuadraticProber(), IntHash2());

    //set<pair<int, int>> items;
    pair<int,int> pair1(1,1);
    pair<int,int> pair2(2,1);
    pair<int,int> pair3(12,11);
    pair<int,int> pair4(23,23);
    pair<int,int> pair5(6,6);
    pair<int,int> pair6(34,34);
    pair<int,int> pair7(45,45);
    /*
    items.insert(pair1);
    items.insert(pair2);
    items.insert(pair3);
    items.insert(pair4);
    items.insert(pair5);
    items.insert(pair6);*/
    //first item = loc = 1
    ht.insert(pair1);
    //EXPECT_EQ(ht.probe(pair1.first),1);
    //first item = loc = 2
    ht.insert(pair2);
    //EXPECT_EQ(ht.probe(pair2.first),2);
    //same hash as pair1, loc = h(k)+1^2 = 2 (collision! pair2) -> h(k)+2^2 = 5
    ht.insert(pair3);
   // EXPECT_EQ(ht.probe(pair3.first),5);
    //same hash as pair1, quadratic should give loc = h(k)+3^2 = 10
    ht.insert(pair4);
    //EXPECT_EQ(ht.probe(pair4.first),10);
    //first item = loc = 6
    ht.insert(pair5);
    //EXPECT_EQ(ht.probe(pair5.first),6);
    //same hash as pair1, loc = h(k)+4^2 mod 11 = 6 (collision! pair5) = h(k)+5^2 mod 11 = 4
    ht.insert(pair6);
    //EXPECT_EQ(ht.probe(pair6.first),4);
    //try{
    ht.insert(pair7);//try to insert pair7, shouldn't be able to
    //}
   // catch(std::logic_error const & err){
     //   correctThrow = true;
    //}
    //catch(...) {
    //    correctThrow = false;
    //}
    //EXPECT_EQ(ht.size(),6);
    /*
    for(size_t i = 0; i < 12; i++){
        std::stringstream ss;
        ss << "hi" << i;
        ht.insert({ss.str(), i});
    }
    
    if( ht.find("hi1") != nullptr ){
        cout << "Found hi1" << endl;
    }
    else{
        cout << "did not find  hi1 :(" << endl;
    }
    if( ht.find("doesnotexist") == nullptr ){
        cout << "Did not find: doesnotexist" << endl;
    }
    cout << "HT size: " << ht.size() << endl;
    ht.remove("hi7");
    ht.remove("hi9");
    cout << "HT size: " << ht.size() << endl;
    if( ht.find("hi9") != nullptr ){
        cout << "Found hi9" << endl;
    }
    else {
        cout << "Did not find hi9" << endl;
    }
    cout << "here" << endl;
    ht.insert({"hi7",17});
        cout << "inserted" << endl;

    cout << "size: " << ht.size() << endl;


*/
    

    return 0;
}
