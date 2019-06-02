#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

#define HANDMAX 11
#define HANDMIN 1

class Deck
{
public:
	vector<int> deckList;
	int myValue;

	Deck()
	{
	
	}

	~Deck()
	{
	}

	//generates the deck with 52 random numbers between 1 and 11, hoping to change this to actual cards with values and suites so we can just have 10 5's laying in the deck.
	void generateDeck()
	{
		srand(static_cast<unsigned int>(time(0)));
		int x;
		//cout << "\n\n\nDeck magically populates with random values... "; <-- Debugging purposes
		for (x = 0; x <= 52; x++)
		{
			myValue = (rand() % (HANDMAX - HANDMIN + 1)) + HANDMIN;
			deckList.push_back(myValue);
		}
	}

	//Functions sole purpose is to debug and verify that the vector is being populated correctly
	void printDeck()
	{
		for (unsigned int d = 0; d <= deckList.size() - 1; d++)
		{
			std::cout << deckList[d] << " ";
			if (d % 10 == 0 && d > 1)
			{
				std::cout << "\n";
			}
		}
		std::cout << "\n Deck size was: " << deckList.size() - 1 << "\n";
	}

	//This takes the last card of the deck (vector) and gives it to the players hand and removes the card from the deck.
	int drawCard()
	{
		int newCard = deckList.back();
		deckList.pop_back();
		return newCard;
	}
	\

		
};