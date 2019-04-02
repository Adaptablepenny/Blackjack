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
		deck = nullptr;
	}

	Player(Deck* ptrDeck)
	{
		deck = ptrDeck;
	}

	~Player()
	{
		Clear();
	}

	// losing function to replay the game
	void Lose()
	{
		cout << "losing stuff here";
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
};