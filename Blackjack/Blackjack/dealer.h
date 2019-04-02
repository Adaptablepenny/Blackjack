#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Deck.h"


class Dealer : public Actor
{
public:

	Dealer()
	{
		deck = nullptr;
	}

	Dealer(Deck* ptrDeck)
	{
		deck = ptrDeck;
	}

	~Dealer()
	{
		Clear();
	}

	int ShowFirstCard()
	{
		return hand[1];
	}

protected:
	
};