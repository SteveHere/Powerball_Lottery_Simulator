/*
 * PLS.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: SteveHere
 *      TODO:
 *      - use pthread to multithread the program
 */
#include "Required_Components.hpp"

int main(int argc, char *argv[]) {
	//Random seeding
	std::srand((unsigned) std::time( NULL));

	//Welcome screen
	welcome();

	char cont = 'y';

	do {
		//place for	number of tickets, set to -1 as default
		int number = -1;
		int block = 0;
		int remainder = 0;

		//for storage of number	of matched lottery tickets
		Match match;

		//request number of tickets
		//will keep	requesting tickets if outside	range
		do {
			std::cout << "Buy tickets [1 - 300,000,000]: ";
			std::cin >> number;
			clearBuffer();
			if ((number < 0) || (number > 300000000))
				std::cout
					<< "Number entered is outside of range. Please try again\n";
			std::cout << std::endl;
		} while ((number < 0) || (number > 300000000));

		//calculate	number of blocks and remainder tickets
		block = number / 10000000;
		remainder = number % 10000000;

		//relay selected input
		//use commented lines for debugging
		std::cout
			<< "Tickets wanted: " << number << "\n"
		//<<	"10,000,000 ticket blocks ordered: " << block << "\n"
		//<<	"Remaining tickets ordered: "	<<	remainder << "\n"
			<< std::endl;

		//Create space for result and generate it
		Lottery result;
		result.generate();

		//Print result
		std::cout << "Result:";
		result.print();
		std::cout << std::endl;

		//Create space for tickets (max: 10,000,000)
		Lottery *ticket = new Lottery[(number > 10000000) ? 10000000 : number];

		for (int i = 0; i <= block; i++) {
			//checks if	it's the last block. If so, use remainder.
			//can use != operator since for loop exits when i > block
			int loop_max = (i != block) ? 10000000 : remainder;

			//exits if none in remainder after blocks
			if (i == block && remainder == 0)
				break;

			//ticket	generation within	block
			for (int j = 0; j < loop_max; j++)
				ticket[j].generate();

			for (int j = 0; j < loop_max; j++) {
				//determine number of matches
				int wb = ticket[j].verifyWhite(result);
				bool rb = ticket[j].verifyRed(result);
				//record match	into records
				match.recordResult(wb, rb);
				//notable results	printing
				if (i == 0 && j == 0)
					std::cout << "Notable results:\n" << std::endl;
				if ((wb > 4) || ((wb > 3) && rb)) {
					std::cout
						<< "Ticket No." << (i * 10000000) + (j + 1)
						<< " combination: ";
					ticket[j].print();
					std::cout
						<< "Matches (white, red): " << wb << " ["
						<< (rb ? "Yes" : "No") << "] "
						<< ((wb == 5 && rb) ? "We have a winner!!!" : "")
						<< "\n" << std::endl;
				}
			}
		}

		//printing matches made	overall
		std::cout << "Matches made:\n\n";

		for (int i = 0; i < 6; i++) {
			std::cout
				<< i << " white balls, no red: " << match.result(i, false)
				<< "\n" << i << " white balls, with red: "
				<< match.result(i, true) << "\n" << std::endl;
		}

		//cash used, cash won, net cash winnings
		int winnings = match.calculateWinnings(number);

		std::cout
			<< "Total cash used: $" << number * 2 << "\n" << "Cash won: $"
			<< winnings << "\n" << "Net cash: $" << winnings - (number * 2)
			<< "\n" << std::endl;

		//free allocated ticket	heap
		delete[] ticket;

		std::cout
			<< "=====================================================\n"
			<< std::endl;

		//ask if they want to continue
		do {
			std::string buffer;
			std::cout << "Continue? [y/n]: ";
			std::getline(std::cin, buffer);
			cont = buffer[0];
			if (cont != 'y' && cont != 'n')
				std::cout << "Invalid option. Please try again\n";
			std::cout
				<< "=====================================================\n"
				<< std::endl;
		} while (cont != 'y' && cont != 'n');

	} while (cont == 'y');

	if (cont == 'n')
		std::cout << "Bye!" << std::endl;
	return 0;
}

