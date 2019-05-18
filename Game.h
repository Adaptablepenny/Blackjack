#pragma once
#include "player.h"
#include "dealer.h"
#include "Deck.h"
#include "actor.h"


class Game
{

public:
	Game();
	~Game();
	int Start();
	int GameLoop();
	Player* GetPlayerPointer();
	Dealer* GetDealerPointer();
	Actor* GetActorPoint();
	bool GetRunning();
	void SetRunning(bool pRunning);
	int choice;

	enum OUTCOMES { BLACKJACK, WIN, LOSE, PUSH };

	enum CHOICE {HIT, STAY, DOUBLE, SPLIT };

protected:
	void InitGame();
	int GetBet();
	void HandleOutcome(OUTCOMES pOC, int pBet);
	void HandleChoice(CHOICE pC);
	//VARS
	Deck deck;
	Player player;
	Dealer dealer;
	Actor actor;
	bool running;
	int bet;
	bool dealerTurn;
	bool pOutcome;
	bool pDouble;
	bool pSplit;

	
};