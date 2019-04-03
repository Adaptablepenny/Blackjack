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
			break;
		}
		case STAY:
		{
			break;
		}

		case DOUBLE:
		{
			//Ask for new bet that is at most half of the orignal bet
			while (true)
			{
				int dBet = GetBet();
				if (dBet > bet / 2); //Well shit, how do I get the orignal bet into here? way to pass an argument like HandOutcome function?
					//bet to much try again
				if (dBet <= bet / 2);
				//Draw one more card
					player.Draw();
					break;

					//also go to figure out how to deal with dollar bets, might have to switch to different integer type to take decimal points.
					
			}
			//break and proceed to outcome
			break;
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
		bool dealerTurn = false;
		bool pOutcome = false;
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
		cout << "\nYour Hand Value: " << player.GetHandTotal();
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
			if(player.GetHandCard(0) == 9 || player.GetHandCard(0) == 10 || player.GetHandCard(0) == 11 || player.GetHandCard(1) == 9 || player.GetHandCard(1) == 10 || player.GetHandCard(1) == 11)
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
				cout << "\nYour Hand Value: " << player.GetHandTotal();
				if (player.GetHandTotal() > 21)
				{
					HandleOutcome(LOSE, bet);
					cout << "\nPlayer Bust!\n";
					running = false;
					break;

				}
				if (player.GetHandTotal() == 21 && dealer.GetHandTotal() != 21)
				{
					HandleOutcome(WIN, bet);
					cout << "\nPlayer Wins!";
					running = false;
					bet = 0;
					break;
				}
			} //END OF CHOICE 1

			if (choice == 2)
			{
				HandleChoice(STAY);
				cout << "\nYour Hand: ";
				player.printHand();
				cout << "\nYour Hand Value: " << player.GetHandTotal();
				dealerTurn = true;
			}//END OF CHOICE 2

			if (choice == 3)
				HandleChoice(DOUBLE);
			//Understand what goes down on a double
			if (choice == 4)
				HandleChoice(SPLIT); // add input validaiton so split cannot be selected when its not there.
				//Understand what goes down on a split.

			//Dealer Plays
			//While loop start for Dealer
			while (dealerTurn)
			{
				//Dealer turn plays out 				
				if (dealer.GetHandTotal() < 17)
					dealer.Draw();
				cout << "\nDealers Hand: ";
				dealer.printHand();
				cout << "\nDealer Hand Total: " << dealer.GetHandTotal();
				if (dealer.GetHandTotal() >= 17)
				{
					pOutcome = true;
					dealerTurn = false;
					break;//exit loop
				}
				
				
				
			}


			while (pOutcome)
			{
				//Process Outcome, do not forget to change running to false to break the loop.
			
				if (dealer.GetHandTotal() > 21)
				{
					HandleOutcome(WIN, bet);
					cout << "\nDealer Bust!\n";
					running = false;
					bet = 0;
					break;
				}
				if (player.GetHandTotal() != 21 && dealer.GetHandTotal() == 21)
				{
					HandleOutcome(LOSE, bet);
					cout << "\nDealer Wins!";
					running = false;
					bet = 0;
					break;

				}
				//Added in the Dealer Turn branch, theres gotta be a better way to process all of these outcomes.
				if (player.GetHandTotal() > dealer.GetHandTotal())
				{
					HandleOutcome(WIN, bet);
					cout << "\nPlayer Wins!";
					running = false;
					bet = 0;
					break;
				}
				if (player.GetHandTotal() < dealer.GetHandTotal())
				{
					HandleOutcome(LOSE, bet);
					cout << "\nDealer Wins!";
					running = false;
					bet = 0;
					break;
				}
				if (player.GetHandTotal() == dealer.GetHandTotal())
				{
					HandleOutcome(PUSH, bet);
					cout << "\nIts a tie!";
					running = false;
					bet = 0;
					break;
				}
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
				player.Clear();
				dealer.Clear();
				bet = 0;
				//How to reset bet? Maybe a clear bet function?
			if(play == 'n')
				break;

		}

	}
	return  0;
}