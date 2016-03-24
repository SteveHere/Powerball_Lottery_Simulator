/*
 * Required_Components.hpp
 *
 *  Created on: Mar 24, 2016
 *      Author: User
 *      Goal: put required.cpp in here
 */

#ifndef REQUIRED_COMPONENTS_HPP_
#define REQUIRED_COMPONENTS_HPP_

#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>

template <typename Type>
void quick_sort(Type *array, int n);

class Lottery
{
private:
	unsigned char white[5];
	unsigned char red;

public:
	Lottery(): white{0}, red(0){}
	~Lottery(){}

	//lottery generation
	void generate(void){
		//for purging of previous data
		memset(white, 0, 5*sizeof(*white));
		red = 0;

		//generate white balls
		bool same;
		for(int i =	0;	i < 5; i++){
			do{
				same = false;
				white[i]	= (rand() %	69) +	1;
				for(int j =	0;	j < i; j++){
					same = (white[i] == white[j]);
					if(same) break;
				}
			}while(same);
		}

		//sort white balls
		quick_sort(white,	5);

		//generate red	ball
		red =	(rand() % 26) + 1;
	}

	//lottery verification
	int verifyWhite(Lottery result){
		//count number of matches for white balls
		int match =	0;
		for(int i =	0;	i <= 4; i++)
			for(int j =	0;	j <= 4; j++)
				if(white[i]	==	result.white[j]) match++;
		return match;
	}

	//lottery verification (red ball)
	bool verifyRed(Lottery result){
		return red == result.red;
	}

	//lottery combination printing
	void print(void){
		for(int i =	0;	i < 5; i++)
			std::cout << " " << (int)white[i];
		std::cout << " ["	<<	(int)red	<<	"]" << std::endl;
	}

};

class Match{
	private:
		int withRed[6];
		int withoutRed[6];

	public:
		Match(): withRed{0}, withoutRed{0}{}
		~Match(){
			//For debug purposes only
			//std::cout << "Destructing Match object" << std::endl;
		}

		void recordResult(int wb, bool rb){
			if(rb) withRed[wb]++;
			else	 withoutRed[wb]++;
		}

		int result(int wb, bool rb){
			if(rb) return withRed[wb];
			else   return withoutRed[wb];
		}

		int calculateWinnings(int tickets){
			return ( (withRed[0] * 4) + (withRed[1] * 4) + (withRed[2] * 7)
					+ (withoutRed[3] * 7) +	(withRed[3]	* 100)
					+ (withoutRed[4] * 100)	+ (withRed[4] * 50000)
					+ (withoutRed[5] * 1000000)
					+ ((withRed[5]	> 0)? (tickets + 250000000) : 0) );
		}
};

void welcome(void){
	std::cout
	<<	"=====================================================\n"
	<<	"|    Welcome to the Powerball Lottery Simulator!    |\n"
	<<	"|        At least $250,000,000 up for grabs!        |\n"
	<<	"| Every ticket you buy increases the jackpot by $1! |\n"
	<<	"|                 Ticket price: $2                  |\n"
	<<	"=====================================================\n"
	<<	std::endl;
}

void clearBuffer(void){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Quick Sort function for arrays only.
//Do not use it for anything else unless modified
template <typename Type>
void quick_sort(Type *array, int n){
	int i, j;
	Type mid;
	if(n < 2)
		return;
	mid = array[n / 2];
	for(i = 0, j = n - 1;; i++, j--){
		while (array[i] < mid)
			i++;
		while (mid < array[j])
			j--;
		if (i >= j)
			break;
		std::swap(array[i], array[j]);
	}
	quick_sort(array, i);
	quick_sort(array + i, n	- i);
}



#endif /* REQUIRED_COMPONENTS_HPP_ */
