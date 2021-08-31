CXX=g++
CXXFLAGS=-g -Wall -std=c++11

all: twitter

# Finish this target by adding other dependencies and 
# the action to compile the final twitter executable
twitter: twitter.o cmdhandler.o datetime.o handler.o tweet.o  user.o util.o twiteng.o
	$(CXX) $(CXXFLAGS) twitter.o cmdhandler.o datetime.o handler.o tweet.o  user.o util.o twiteng.o -o twitter

# Complete	
twitter.o: twitter.cpp twiteng.h cmdhandler.h user.h util.h datetime.h handler.h tweet.h
	$(CXX) $(CXXFLAGS) -c twitter.cpp -o twitter.o

cmdhandler.o: cmdhandler.cpp cmdhandler.h
	g++ -g -Wall -c cmdhandler.cpp -o cmdhandler.o

datetime.o: datetime.cpp datetime.h
	g++ -g -Wall -c datetime.cpp -o datetime.o

handler.o: handler.cpp handler.h
	g++ -g -Wall -c handler.cpp -o handler.o

tweet.o: tweet.cpp tweet.h
	g++ -g -Wall -c tweet.cpp -o tweet.o

user.o: user.cpp user.h
	g++ -g -Wall -c user.cpp -o user.o

util.o: util.cpp util.h
	g++ -g -Wall -c util.cpp -o util.o

twiteng.o: twiteng.cpp twiteng.h
	g++ -g -Wall -c twiteng.cpp -o twiteng.o

# Add other rules/targets

clean:
	rm -f *.o twitter *.feed
