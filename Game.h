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
	string splitChoice;
	int choiceValid;
	int splitChoiceValid;

	enum OUTCOMES { BLACKJACK, WIN, LOSE, PUSH };

	enum CHOICE {HIT, STAY, DOUBLE, SPLIT };

protected:
	void InitGame();
	void restartGame();
	int GetBet();
	void processBlackjack(int x, int y);
	void processOutcome(int x, int y, int z);
	void HandleOutcome(OUTCOMES pOC, int pBet);
	void HandleChoice(CHOICE pC);
	//VARS
	Deck deck;
	Player player;
	Dealer dealer;
	Actor actor;
	bool running;
	bool playAgain;
	int bet;
	int splitBet;
	int betValid;
	bool betStart;
	bool betting;
	bool dealerTurn;
	bool pOutcome;
	int y; //Using this to test to make sure you can only split once.
	bool pDouble;
	bool pSplit;
	bool pSplitTurn;
	bool pSplitOutcome;

	
};