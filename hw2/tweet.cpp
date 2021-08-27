#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
#include "tweet.h"
#include "util.h"
#include "user.h"


using namespace std;

  /**
   * Default constructor 
   */
  Tweet::Tweet(){

  }

  /**
   * Constructor 
   */
  Tweet::Tweet(User* user, const DateTime& time, const string& text){
    _user = user;
    _time = time;
    _text = text;


  }

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & Tweet::time() const{
    return _time;


  }

string Tweet::user_name() const{
    string temp = _user->name();
    return temp;

}

  /**
   * Gets the user of this tweet
   *
   * @return user of the tweet
   */

  User* Tweet::user() const{
    return _user;


  }

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  string const & Tweet::text() const{
    return _text;

  }

  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */

  // need to define what less than is
  // YYYY-MM-DD HH:MM:SS
  bool Tweet::operator<(const Tweet& other) const{
       if(this->_time < other._time){
          return true;
        }
        return false;

  }

  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * '?'
   * @return the ostream passed in as an argument
   */

  // cout the info
  ostream& operator<<(ostream& os, const Tweet& t){


      os << t._time.year << '-' ;
    if(t._time.month < 10){
        os << "0";
        }
    os << t._time.month << '-';
    //if(t._time.day < 10){
      //  os << "0";
    //}
    os << t._time.day << ' ';
    if(t._time.hour < 10){
        os << "0";
    }
    os  << t._time.hour << ':';
    if(t._time.min < 10){
        os << "0";
    }
    os << t._time.min << ':';
    if(t._time.sec < 10){
        os << "0";
    }
    os << t._time.sec;

    os << " " << t.user_name() << " " << t.text();
    
    return os;
    



  }


   /**
   * Returns the hashtagged words without the '#' sign
   *
   */
  set<string> Tweet::hashTags() const{
    set<string> temp;
    stringstream tweet_temp;
    tweet_temp.str(_text);
    string word_temp;
    while(getline(tweet_temp, word_temp, '#')){
      string next_word;
      tweet_temp >> next_word;
      convLower(next_word);
      temp.insert(next_word);

    }

    
    return temp;
  }

  
  


