#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        // Add your code here
				unsigned long long w[5] = {0,0,0,0,0};
			//	std::string comp = k;

				for(int i = 0; i < k.size()/6 + 1; i++) //goes thru w reverse
				{
					unsigned long long int result = 0;
					for(int j = 0; j < 6; j++)
					{
						if(k.size()-(i+1)*6+j < 0)
							result += 0;
						else 
							result = result * 36 +letterDigitToNumber(k[(k.size())-(i+1)*6+j]);
					}

					w[5-i-1] = result;
				}

				size_t answer = ((rValues[0]*w[0])
					 + (rValues[1]*w[1])
					 + (rValues[2]*w[2])
					 + (rValues[3]*w[3])
					 + (rValues[4]*w[4]));

				return answer;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(letter >= 'A' && letter <= 'Z')
				{
					return letter - 65;
				}

				if(letter >= '0' && letter <= '9')
				{
					return letter - 22;
				}

				if(letter >= 'a' && letter <= 'z')
				{
					return letter - 97;
				}

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
