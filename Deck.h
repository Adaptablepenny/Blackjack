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
	vector<int> ShuffleDeck;
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
		g = 1;

		for (int x = 0; x < 8; ++x)
		{
			++g;
			for (int z = 0; z < 4; ++z)
				deckList.push_back(g);
		}
		for (int x = 0; x < 1; ++x)
		{
			++g;
			for (int z = 0; z < 16; ++z)
				deckList.push_back(g);
		}
		for (int x = 0; x < 1; ++x)
		{
			++g;
			for (int z = 0; z < 4; ++z)
				deckList.push_back(g);
		}
		//Everything below here in this function is old code, prior it would create a random number and place it intot he deck 52 times.
		//This would lead to having incorrect amount of cards (i.e 10 5's) the above code now makes 4 1-9 and 11 and then makes 16 10's
		//A new function has been made to "Shuffle" the deck, keeping the code just in case
		//cout << "\n\n\nDeck magically populates with random values... "; <-- Debugging purposes
		/*
		for (int x = 0; x < 15; ++x)
		{
			
			if (g <= 9)
			{
				for (int z = 0; z < 4; ++z)
				{
					deckList.push_back(g);
					
				}
				g++;
			}
			else if (g == 10)
			{
				for (int z = 0; z < 16; ++z)
				{
					deckList.push_back(g);
					
				}
				g++;
			}
			else if (g == 11)
			{
				for (int z = 0; z < 4; ++z)
				{
					deckList.push_back(g);
					
				}
				++g;
			}
		
				
		}*/



		/*		
		for (x = 0; x <= 52; x++)
		{

			myValue = (rand() % (HANDMAX - HANDMIN + 1)) + HANDMIN;
			deckList.push_back(myValue);
					
		}*/
	}



	void deckShuffle()
	{
		srand(static_cast<unsigned int>(time(0)));
		for (int x = 52; x > 0; --x)
		{
			int randomInt = (rand() % (deckList.size() - 1 + 1));
			ShuffleDeck.push_back(deckList[randomInt]);
			deckList.erase(deckList.begin() + randomInt);
		}
	}

	//Functions sole purpose is to debug and verify that the vector is being populated correctly
	void printDeck()
	{


		for (auto x : ShuffleDeck)
		{
			cout << x << " ";
		}
		cout << ShuffleDeck.size();
		/*
		for (unsigned int d = 0; d <= deckList.size() - 1; d++)
		{
			std::cout << deckList[d] << " ";
			if (d % 10 == 0 && d > 1)
			{
				std::cout << "\n";
			}
		}
		std::cout << "\n Deck size was: " << deckList.size() - 1 << "\n";*/
	}

	//This takes the last card of the deck (vector) and gives it to the players hand and removes the card from the deck.
	int drawCard()
	{
		int newCard = ShuffleDeck.back();
		ShuffleDeck.pop_back();
		return newCard;
	}
private:
	int g;
	
};