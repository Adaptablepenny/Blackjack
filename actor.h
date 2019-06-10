#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Deck.h"

class Actor
{
public:
	Actor()
	{
		deck = nullptr;

	
	}

	Actor(Deck* ptrDeck)
	{
		deck = ptrDeck;
	}

	~Actor()
	{

	}

	//Erases the players hand.
	void Clear()
	{
		hand.erase(hand.begin(), hand.end());
	}

	//prints the hand of the player
	int printHand()
	{
		//std::string handString = "";
		
		for (auto h = hand.begin(); h != hand.end(); ++h)
		{
			cout << *h << " ";
			
		};
		return 0;
		
		
	}

	void Draw(int pCards = 1)
	{
		for (int x = 0; x < pCards; ++x)
		{
			hand.push_back(deck->drawCard());
		}

	}

	void SetDeck(Deck* pDeckPtr)
	{
		deck = pDeckPtr;
	}

	int GetHandTotal()
	{
		int handTotal = 0;
		int aces = 0;
		for (auto x = hand.begin(); x != hand.end(); x++)
		{
			handTotal += *x;
			if (*x == 11)
				++aces;
		}
		if (handTotal > 21 && aces > 0)
		{
			while (aces > 0 && handTotal > 21)
			{
				handTotal -= 10;
				--aces;
			}
		}
		return handTotal;
	}

	int GetHandCard(int x)
	{
		if (x <= hand.size())
			return hand[x];
		else
			return -1;
	}

protected:
	std::vector<int> hand;
	Deck* deck;
};