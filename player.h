#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Deck.h"
#include "actor.h"

class Player : public Actor
{
public:
	

	Player()
	{
		Wallet = 0;
		deck = nullptr;
	}

	Player(Deck* ptrDeck)
	{
		Wallet = 0;
		deck = ptrDeck;
	}

	~Player()
	{
		Clear();
	}

	//Function for betting can this go away?
	void Betting()
	{
		cout << "How much do you want to bet? ";
		cin >> betCash;
		
		if (betCash <= Wallet)
		{
			Wallet -= betCash;
			//cout << "New Wallet: " << pWallet;
		}
		else if (betCash > Wallet)
		{
			cout << "Not enough";
			betCash = 0;
		}
		
	}
	void splitDraw()
	{
		splitHand.push_back(deck->drawCard());
		deck->deckList.pop_back();
	}

	int GetSplitTotal()
	{
		int handTotal = 0;
		int aces = 0;
		for (auto x = splitHand.begin); x != splitHand.end(); x++)
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

	int printSplitHand()
	{

		for (auto h = splitHand.begin(); h != splitHand.end(); ++h)
		{
			cout << *h << " ";

		};
		return 0;


	}

	int GetWallet()
	{
		return Wallet;
	}

	void ChangeWallet(int pX)
	{
		Wallet += pX;
	}
protected:
	int Wallet;
	int betCash = 0;
	vector<int> splitHand;
};