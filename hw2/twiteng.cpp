#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "twiteng.h"
#include "user.h"
#include <map>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "tweet.h"
#include "util.h"
// Add other header files


using namespace std;


// Update as needed
TwitEng::TwitEng()
{


}

// Update as needed
TwitEng::~TwitEng()
{
   
   for(list<Tweet*>::iterator it = _tweets.begin(); it!= _tweets.end(); it++){
     delete *it;
   }

  for(map<std::string, User*>::iterator it = _users.begin(); it!= _users.end(); it++){
     delete it->second;
    // delete it->first;
   }


}

  /** 
   * Returns true if the given name corresponds to an
   * existing User, and false otherwise 
   */

  bool TwitEng::validUser(const string& name) const{
    return(_users.find(name) != _users.end());


  }

// assume that all users exist (says 4 there is 4)
// Complete this function

//not sure when else this function needs to fail 

bool TwitEng::parse(char* filename)
{
  bool incorrect_format = false; 
  ifstream ifile(filename);
  if (ifile.fail()) {
    cerr << "Unable to open " << filename << endl;
    return true;
  }
  int numUsers;
  ifile >> numUsers;
  if (ifile.fail()) {
    cerr << "Unable to read number of users " << endl;
    ifile.close();
    return true;
  }
  // Finish the parsing of the input file. Return false if successful,
  // true otherwise.

//that there are 4 lines 
// create user
// for each and add to followers

string temp;
getline(ifile, temp);
for(int i = 0; i < numUsers ; i++){
  string line;
  getline(ifile, line);
  //if able to get each line
  if (ifile.fail()) {
    cerr << "Unable to get username " << endl;
    ifile.close();
    return true;
  }
  // has line, puts first user in user_name string
  stringstream holder;
  holder.str(line);
  string user_name;
  //user is in username
  holder >> user_name;
  // if user does not exist create user with this anem
  if(!validUser(user_name)){
      //not sure what to call each user and if it even matters
      User *user_pointer = new User(user_name);
      //ads to list of user so we know if we need to make a new one or not
      new_user(user_pointer);

  }
// gets the pointer to user_name 
User* pointer_user_name = get_user(user_name);


  //one of followers are in temp 
  string folowers_temp;
  // while there are users after username
  while(holder >> folowers_temp){
    // if they do not exist create them
 if(!validUser(folowers_temp)){
      User *user_pointer = new User(folowers_temp);
      new_user(user_pointer);
  }


  // gets the pointer to folower_temp 
User* pointer_follower = get_user(folowers_temp);



//add each follower + following to list
// a follows b and b follow a
// I think i need to make this a map??????????
// for now I will keep it a list bc that makes sense to me and i dont think it will be do hard to switch out


  pointer_user_name->addFollowing(pointer_follower);
  pointer_follower->addFollower(pointer_user_name);

  }
}



//now parcing throught the tweets
string line;
//while there are lines to get 
while(getline(ifile, line)){
// creates strings for each item to go into 
string username;
string date;
string time_string;
string date_time;
string tweet_text;
stringstream line_temp;
if(line == ""){
  continue;
}
line_temp.str(line);
// puts first 2 words into date time, third into user name
line_temp >>  date;
line_temp >>  time_string;
line_temp >>  username;
if(!validUser(username)){
  incorrect_format = true;

}
date_time = date + " " + time_string;
// puts the rest of the line into tweet_text
getline(line_temp, tweet_text);
trim(tweet_text);
// puts string datetime into time variable
DateTime time;
stringstream temp(date_time);

//temp.str(date_time);
// I hvae this operatior overloaded in datetime as a frined object. How do I get it to work her
// not an object idk what to call it
temp >> time;
stringstream iscorrect;
iscorrect << time;
string test_date;
string test_time;
string test_both;


iscorrect >> test_date;
iscorrect >> test_time;
test_both = test_date + " " + test_time;


//cout << test_both << " " << date_time;
if(test_both != date_time){
  incorrect_format = true;
}

// add a tweet with all of this info 
addTweet(username, time, tweet_text);
line = "";
}
ifile.close();

return incorrect_format;
}

//used to have a list of users so we know if one exists or not

void TwitEng::new_user(User * u){
 
  _users.insert(make_pair(u->name(), u));

}

//given a string will return a pointer to the user
  User* TwitEng::get_user(string name){
    if( _users.find(name) == _users.end()){
    }
     map<string, User*> :: iterator it =  _users.find(name);
     User* temp = it->second;
     return temp;

  }


/**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */

  ///
  void TwitEng::addTweet(const string& username, const DateTime& time, const string& text){
    User* currentuser = get_user(username);
    //Tweet(User* user, const DateTime& time, const std::string& text);
    //I thinkkkk these errors havet ot do with the tweet.cpp file because something is off with the coloring/decloration in those files
    Tweet *tweet_pointer = new Tweet(currentuser, time, text);
    if(_users.find(username) == _users.end()){
      return;
    }
    currentuser->addTweet(tweet_pointer);
    
    //add tweets and hashtags to the map
    set<string> tweet_hashtags = tweet_pointer->hashTags();

    //make a tweet pointer
    _tweets.push_back(tweet_pointer);
    
    //itterate thorught hastags that this new tweet has
    for(set<string>::iterator it = tweet_hashtags.begin(); it != tweet_hashtags.end(); ++it){
    //check if hastag is on the map
    map<string, set<Tweet*> >::iterator its = _hashtag_map.find(*it);
    if(its == _hashtag_map.end()){
      //hashtag is not on map yet add to map
      string string_temp = *it;
      set<Tweet*> temp_tweets;
      temp_tweets.insert(tweet_pointer);
      _hashtag_map.insert(make_pair(string_temp, temp_tweets));
    }
    else{
      //if the hashtag does exist, add this tweet to list
      (its)->second.insert(tweet_pointer);

    }
    }
      cout << endl;
  }



//finds the untion betweet two sets
//adds them together
set<Tweet*> TwitEng::_union(set<Tweet*> list_one, set<Tweet*> list_two){
  set<Tweet*> _return = list_one;
  for(set<Tweet*>::iterator it = list_two.begin(); it!= list_two.end(); ++it ){
  //if the item from list two is not on list one
        if(list_one.find(*it) == list_one.end()){
          _return.insert(*it);
        }
  }

  return _return;


}



set<Tweet*> TwitEng::_intersection(set<Tweet*> list_one, set<Tweet*> list_two){
  set<Tweet*> _return;
  //for each item on list 2
  for(set<Tweet*>::iterator it = list_two.begin(); it!= list_two.end(); ++it ){
  // if its on list 1 too add it to the list
        if(list_one.find(*it) != list_one.end()){
          _return.insert(*it);
        }
  }
  return _return;

}









  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy){
    //does it searcgh all tweets or only the ones that the user follows?

    // return a vector for all tweets that match the serch
    //assume that the hashtag parse things works right (I'm not sure if it does tbh)
    
    // asume we have correct map  std::map<std::string, std::set<Tweet*> > _hashtag_map;

    set<Tweet*> to_return;
    vector<Tweet*> vector_return;
    // or
    
    int nums = 0;
    int tweet_count = 0;
    string serch_word;
    //repeats this for each term on the list

    for(vector<string>::iterator it = terms.begin(); it!= terms.end(); ++it ){
      //test if the hashtag we are looking for belongs to any hashtags period
      convLower(*it);
      if(_hashtag_map.find(*it) != _hashtag_map.end()){
        //for each hastag on the list
        if(nums == 0){
           to_return = _hashtag_map.find(*it) -> second;
        }
        else{
          set<Tweet*> temp = _hashtag_map.find(*it) -> second;
          //or --> untion
          if(strategy == 1){
            to_return = _union(to_return, temp);

          }
          // and --> intersection
          else if(strategy == 0){
            to_return = _intersection(to_return, temp);

          }
        }
      nums++;
    }
    

    
    }

    for(set<Tweet*>::iterator it = to_return.begin(); it!= to_return.end(); ++it ){
      tweet_count ++;
      vector_return.push_back(*it);
    }
    TweetComp temp;
    displayHits(vector_return);
    return vector_return;

  }



     
  


  /**
   * Dump feeds of each user to their own file
   * HOW DO I GET ANOTHER FILE
   */
  void TwitEng::dumpFeeds(){
    //go through each user
    //make a file for that user
    //error bc its a map 
     //map<string, User*> :: iterator it =  _users.find(name);
     //User* temp = it->second;
     //return temp;

    for(map<string, User*> :: iterator it = _users.begin(); it != _users.end(); ++it){
        //names file username.txt
        string file_name = it->first + ".feed";
        ofstream MyFile(file_name);
        //puts username in the first line of the file
        MyFile << it->first << endl;
      //gets feed from user
      vector<Tweet*> user_tweets = (it->second)->getFeed();
      //puts the feed into the file
      for(vector<Tweet*>::iterator it = user_tweets.begin(); it != user_tweets.end(); ++it){
      MyFile << (*it)->time() << " " << (*it)->user_name() << (*it)->text() << endl;

      }
     }
    }






