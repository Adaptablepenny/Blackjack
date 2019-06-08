#pragma once
#include "player.h"
#include "dealer.h"
#include "Deck.h"
#include "actor.h"
#include <thread>
#include <chrono>


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
	void waitTime(int w);
	string choice;
	int choiceValid;

	enum OUTCOMES { BLACKJACK, WIN, LOSE, PUSH };

	enum CHOICE {HIT, STAY, DOUBLE, SPLIT };

protected:
	void InitGame();
	void restartGame();
	int GetBet();
	void processBlackjack(int x, int y);
	void processOutcome(int x, int y);
	void HandleOutcome(OUTCOMES pOC, int pBet);
	void HandleChoice(CHOICE pC);
	//VARS
	Deck deck;
	Player player;
	Dealer dealer;
	Actor actor;
	bool running;
	int bet;
	int betValid;
	bool betStart;
	bool dealerTurn;
	bool pOutcome;
	bool pDouble;
	bool pSplit;
	bool pSplitTurn;
	bool pSplitOutcome;

	
};