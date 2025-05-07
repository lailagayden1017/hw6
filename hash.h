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
		const int groupMax = 5;
		const int size = 6; 
		unsigned long long w[groupMax] = {0};

		std::string lower; 
		for(char ch : k){
			lower += std::tolower(ch);
		}

		int strLen = lower.length();
		int cnt = (strLen + size - 1)/ size;

		for(int i = 0; i < cnt; ++i){
			unsigned long long v = 0;
			int start = strLen - (i+ 1) * size;
			int end = strLen - i * size; 

			if(start < 0) start = 0;

			std::string group = lower.substr(start, end - start);



			for(std::size_t j = 0; j < group.length(); ++j){
				v = v * 36 + letterDigitToNumber(group[j]);
			}

			w[groupMax - 1 - i] = v;
		}
		unsigned long long hash = 0; 
		for(int i = 0; i < groupMax; ++i){
			hash += rValues[i] * w[i];
		}		
		return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
		letter = std::tolower(letter);
		if(letter >= 'a' && letter <= 'z'){
			return letter - 'a';
		}
		else if(letter >= '0' && letter <= '9'){
			return letter - '0' + 26;
		}
		return 0;

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
