#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

//Define how a deck looks
//


constexpr int HANDMAX = 11;
constexpr int HANDMIN = 1;

enum SUITS { SPADE, HEART, DIAMOND, CLUB };
enum CARDS { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };



class Card
{
public:
	Card()
	{
		value = 255;
		symbol = '?';
	};
	Card(int pV, char pS, int pSuit)
	{
		value = pV;
		symbol = pS;
		if (pSuit = SPADE)
			suit = 'S';
		else if (pSuit = HEART)
			suit = 'H';
		else if (pSuit = DIAMOND)
			suit = 'D';
		else if (pSuit = CLUB)
			suit = 'C';

	};
	~Card() {};
	unsigned short int value;
	char symbol;
	char suit;

	std::string GetCardString()
	{
		std::string outStr = "" + symbol + suit;
		return outStr;
	}
};

class Deck
{
public:
	vector<Card> deckList;
	int myValue;

	Deck()
	{
		//generateDeck();
	}

	~Deck()
	{
	}

	int RandomNumber(int i)
	{
		return std::rand() % i;
	}

	unsigned short int GetCardValue(unsigned short int pCard)
	{
		unsigned short int values[13] = { 11,2,3,4,5,6,7,8,9,10,10,10,10 };
		return values[pCard];
	}

	char GetCardSymbol(unsigned short int pCard)
	{
		unsigned short int symbols[13] = { 'A','2','3','4','5','6','7','8','9','10','J','Q','K'};
		return symbols[pCard];
	}

	//generates the deck with 52 random numbers between 1 and 11, hoping to change this to actual cards with values and suites so we cant just have 10 5's laying in the deck.
	void GenerateDeck(unsigned short int decks)
	{
		std::srand(static_cast<unsigned>(std::time(0)));
		for (int x = 0; x < decks; ++x)
			for (int y = 0; y < 4; ++y)
				for (int z = 0; z < 13; ++z)
				{
					deckList.push_back(Card(GetCardValue(z), GetCardSymbol(z), y));
				}

		//shuffle available cards
		std::random_shuffle(deckList.begin(), deckList.end(), &RandomNumber);
		

		/* Probably deprecated

		srand(static_cast<unsigned int>(time(0)));
		int x;
		//cout << "\n\n\nDeck magically populates with random values... "; <-- Debugging purposes
		for (x = 0; x <= 52; x++)
		{
			myValue = (rand() % (HANDMAX - HANDMIN + 1)) + HANDMIN;
			deckList.push_back(myValue);
		}
		*/ 
	}

	//Functions sole purpose is to debug and verify that the vector is being populated correctly
	void printDeck()
	{
		for (unsigned int d = 0; d <= deckList.size() - 1; d++)
		{
			std::cout << deckList[d].GetCardString() << " ";
			if (d % 10 == 0 && d > 1)
			{
				std::cout << "\n";
			}
		}
		std::cout << "\n Deck size was: " << deckList.size() - 1 << "\n";
	}

	//This takes the last card of the deck (vector) and gives it to the players hand and removes the card from the deck.
	Card drawCard()
	{
		Card newCard = deckList.back();
		deckList.pop_back();
		return newCard;
	}
};