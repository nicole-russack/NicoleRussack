#include "cmdhandler.h"
#include "util.h"
#include <sstream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <list>
#include "user.h"
#include "twiteng.h"
#include "tweet.h"


using namespace std;
//Quit Handler
QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}




//And Handler
AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{   //string keyword;
    //instr >> keyword;
	int strategy = 0;
	string nextword;
	vector<string> terms;
	while(instr >> nextword){
		terms.push_back(nextword);
		nextword = "";
	}


	eng->search(terms, strategy);
	// eng-> disp
	//call display hits --. need to make member to do this
	return HANDLER_OK;
}


//OR Handler 
OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{   //string keyword;
    //instr >> keyword;
	int strategy = 1;
	string nextword;
	vector<string> terms;
	while(instr >> nextword){
		terms.push_back(nextword);
		nextword = "";
	}


	eng->search(terms, strategy);
	//need to display
	return HANDLER_OK;
}

//TWEET Handler
TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";

}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{

	//can simplify 
    string line;
	getline(instr, line);
	if(instr.fail()){
		return HANDLER_OK;
	}
	stringstream line_temp;
	line_temp.str(line);
	string username;
	string tweet_text;
	
	line_temp.str(line);
	// puts first 2 words into date time, third into user name
	line_temp >>  username;
	// puts the rest of the line into tweet_text
	getline(line_temp, tweet_text);
	if(line_temp.fail()){
		tweet_text ="";
	}
	// puts string datetime into time variable
	DateTime time;
	//check if user exits


	//temp.str(date_time);
	// I hvae this operatior overloaded in datetime as a frined object. How do I get it to work her
	// not an object idk what to call it
	// add a tweet with all of this info 
	///cout << username << " " << time << " " << tweet_text;
	if(!eng->validUser(username)){
		return HANDLER_ERROR;
	}
	
	eng->addTweet(username, time, tweet_text);
	return HANDLER_OK;
}


