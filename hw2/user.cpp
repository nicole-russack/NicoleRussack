// user cpp
//date time cpp
//tweet cpp

//#ifndef USER_CPP
//#define USER_CPP
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "tweet.h"
#include "user.h"

using namespace std;

//using namespace std;

 /**
   * Constructor 
   */
User::User(string name){
    _name = name;
    _followers.empty();
    _following.empty();
    _tweets.empty();
    _feed.empty();
   
  std::set<User*> _followers;
  std::set<User*> _following;
  std::list<Tweet*> _tweets;
  std::vector<Tweet*> _feed;

}
 /**
   * Destructor
   */
User::~User(){

}


/* Gets the name of the user 
   * 
   * @return name of the user 
   */
string User::name() const{
    return _name;


}

/**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
set<User*> User::followers() const{
    return _followers;

}

set<User*> User::following() const{
    return _following;

}


 /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */

  list<Tweet*> User::tweets() const{
      list<Tweet*> to_return;
      for(set<Tweet*>:: iterator it = _tweets.begin(); it != _tweets.end(); ++it){
        to_return.push_back(*it);
      }
      return to_return;

  }


  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */

  void User::addFollower(User* u){
      _followers.insert(u);


  }


   /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */

  void User::addFollowing(User* u){
      _following.insert(u);

  }

   /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void User::addTweet(Tweet* t){
      _tweets.insert(t);

  }

/**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
// we do the acutal work here to get the feed
  vector<Tweet*> User::getFeed(){
      //temp variable to hold the total tweets + how many there are
      //puts all of the tweets that the user posted into this variable
      vector<Tweet*> total_tweets;
      //puts all of the tweets that the user posted into this variable
      for(set<Tweet*>::iterator it = _tweets.begin(); it != _tweets.end(); ++it){
        total_tweets.push_back(*it);
      }
      //for each person that the main user follows
      for(set<User*>::iterator it = _following.begin(); it != _following.end(); ++it){
            // adds all of the tweets that they posted into total_tweets
            //gets all the tweets from each following and puts it into a temp var
           // cout << (*it)->tweets() << endl;
            list<Tweet*> tweet_temp = (*it)->tweets();
            //for each tweet of this follower
            for(list<Tweet*>::iterator its = tweet_temp.begin(); its != tweet_temp.end(); ++its){
                //add it to the total tweets list
                total_tweets.push_back(*its);
      }
      }
    //we have all the tweets in a set, now we need to put them in order of timestamp
    //this is giving me errors, not sure how to do this!!
    TweetComp test;
    sort(total_tweets.begin(), total_tweets.end(), test);


    return total_tweets;

  }





