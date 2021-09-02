#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cstdlib>
#include <ctime>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {

        //take each six and make it into an array or vector or something ahhh

        int strlen = k.length();
        int strplace = k.length();

        //what the values will be in
        unsigned long long  w[6];
        int times = 0;
        //do this for as many times as we can
        while(strplace >=6){
            unsigned long long total = 0;
            for(int i = 0; i < 6; i++){
                    total *= 36;
                    total += letterDigitToNumber(k[strplace-6+i]);
                    //strplace-=1;
                    std::cout << k[strlen-6+i] << " " << total << std::endl;
                
            }
            w[times] = total;
            times += 1;
            strplace -= 6;
            
        }
        
        int holderlen = strplace;
        //now for the last didgets we dont know how big they are now
        unsigned long long  total = 0;
        for (int i = 0; i < holderlen; i++)
        {
                total *= 36;
                total += letterDigitToNumber(k[i]);
                //strlen-=1;
                std::cout << k[i] << " " << total << std::endl;
            
        }
        w[times] = total;
        
        

        //takes in w[4] - 0-4
        //some could be 0
        HASH_INDEX_T returnVal = 0;
        for(int i=0; i < times + 1; i++){
            std::cout << w[i] << std::endl;
            returnVal += rValues[4-i] * w[i];

        }
        
        return returnVal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {   
        
        HASH_INDEX_T returnValue = 0;
        //lowercase
        if(letter > 96 && letter < 123){
            returnValue =  letter - 97;
        }
        //caps
        else if(letter > 64 && letter < 91){
            returnValue =  letter - 65;
        }
        //numbers
        else if(letter > 47 && letter < 58){
            returnValue =  letter - 22;
        }
        return returnValue;
    }

    // Add code to generate the random R values
    void generateRValues()
    {
        srand(time(0));
        //HASH_INDEX_T rValues[5];
        for(int i =0; i < 5; i++){
            rValues[i] = rand();
        }




    }

};

#endif
