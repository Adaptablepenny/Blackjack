#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

int Game::Start()
{
	InitGame();
	return GameLoop();
}

Actor* Game::GetActorPoint()
{
	return &actor;
}

Player* Game::GetPlayerPointer()
{
	return &player;
}

Dealer* Game::GetDealerPointer()
{
	return &dealer;
}


bool Game::GetRunning()
{
	return running;
}

void Game::SetRunning(bool pRunning)
{
	running = pRunning;
}

void Game::InitGame()
{
	running = true;
	player.SetDeck(&deck);
	player.ChangeWallet(100);
	dealer.SetDeck(&deck);
	deck.generateDeck();
	return;
}

int Game::GetBet()
{
	int betAmount = 0;
	//Betting Loop
	while (betAmount <= 0)
	{
		cout << "Place Your Bets!" << endl << "Current Balance: $" << player.GetWallet() << endl << "Bet: ";
		cin >> betAmount;
		if (betAmount <= player.GetWallet())
		{
			return betAmount;
		}
		else if (betAmount > player.GetWallet())
		{
			cout << "Not enough! Try Again!";
			betAmount = 0;
		}
	}
}



void Game::HandleOutcome(OUTCOMES pOC, int pBet)
{
	switch (pOC)
	{
		case BLACKJACK: player.ChangeWallet(pBet * 2.5);
			break;
		case WIN: player.ChangeWallet(pBet*2);
			break;
		case PUSH: player.ChangeWallet(pBet);
			break;
		default: break;
	}
}

void Game::HandleChoice(CHOICE pC)
{
	switch (pC)
	{
		case HIT: 
		{
			player.Draw();
			//player.printHand();
			dealer.Draw();
			//dealer.printHand();
			break;
		}
		case STAY:
		{
			dealer.Draw();
			dealer.printHand();
			break;
		}

		case DOUBLE:
		{
			//What to do
		}

		case SPLIT:
		{
			//What to do
		}
	}
}

int Game::GameLoop()
{
	//Welcome Message
	//---TypeHere

	//We have initialized
	InitGame();

	while (running)
	{
		
		//Welcome the  player
		//Setup player and dealer
		//Begin Game Loop
		//Place Bet
		int bet = GetBet();
		player.ChangeWallet(-bet);
		//deal cards
		player.Draw(2);
		dealer.Draw(2);
		//Display Dealers second card
		cout << "Dealer Shows: " << dealer.ShowFirstCard() << endl;
		//Display Players hand
		cout << "Your Hand: ";
		player.printHand();
		//Handle BlackJacks
		if (player.GetHandTotal() == 21 && dealer.GetHandTotal() == 21)
			HandleOutcome(PUSH, bet);
		else if (player.GetHandTotal() != 21 && dealer.GetHandTotal() == 21)
			HandleOutcome(LOSE, bet);
		else if (player.GetHandTotal() == 21 && dealer.GetHandTotal() != 21)
			HandleOutcome(BLACKJACK, bet);
		
		//Ask Hit,Stay,Split,Double,Insurance
		while (bet > 0)
		{
			cout << endl << "Would you like to: " << endl;
			cout << "1> Hit\n";
			cout << "2> Stay\n";
			cout << "3> Double\n";
			if (player.GetHandCard(0) == player.GetHandCard(1))
				cout << "4> Split\n";
			//Need to implement insurance, but need to understand it first.
			cin >> choice;


			//Process these actions
			if (choice == 1)
			{
				HandleChoice(HIT);
				cout << "Your Hand: ";
				player.printHand();
				cout << "\nDealers Hand: ";
				dealer.printHand();
			} //END OF CHOICE 1
			if (choice == 2)
				HandleChoice(STAY);
			//Dealer hits here, but isnt there a rule where they cant hit pass 17?
			if (choice == 3)
				HandleChoice(DOUBLE);
			//Understand what goes down on a double
			if (choice == 4)
				HandleChoice(SPLIT); // add input validaiton so split cannot be selected when its not there.
				//Understand what goes down on a split.

			//Dealer Plays not sure what to do here? Couldnt it just play out when process actions?

			//Process Outcome, do not forget to change running to false to break the loop.
						//**** DRAFT CODE ****
			if (player.GetHandTotal() == 21 && dealer.GetHandTotal() != 21)
			{
				HandleOutcome(WIN, bet);
				running = false;
				bet = 0;
				player.Clear();
				dealer.Clear();
			}
			if (player.GetHandTotal() > 21)
			{
				HandleOutcome(LOSE, bet);
				cout << "\nPlayer Bust!\n";
				running = false;
				bet = 0;
				player.Clear();
				dealer.Clear();
			}
			if (dealer.GetHandTotal() > 21)
			{
				HandleOutcome(WIN, bet);
				cout << "\nDealer Bust!\n";
				running = false;
				bet = 0;
			}
			if (player.GetHandTotal() != 21 && dealer.GetHandTotal() == 21)
			{
				HandleOutcome(LOSE, bet);
				running = false;
				bet = 0;
				player.Clear();
				dealer.Clear();
			}
			
		}
		

		//Ask for the follow on bet/end. Just need to create a function that resets the whole loop, shouldnt be to hard....right

		//   **** DRAFT CODE ****
		while (running == false)
		{
			char play;
			cout << "\nPlay Again? " << endl;
			cin >> play;

			if (play == 'y')
				running = true;
				
			if(play == 'n')
				break;

		}

		





	}
	return  0;
}