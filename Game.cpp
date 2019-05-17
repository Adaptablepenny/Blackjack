
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
		cout << "Place Your Bets!" << endl << "Current Balance: $" << player.GetWallet() << endl << "Bet: $";
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
			cout << "Your Hand: ";
			player.printHand();
			cout << "\nYour Hand Value: " << player.GetHandTotal();
			if (player.GetHandTotal() > 21)
			{
				HandleOutcome(LOSE, bet);
				cout << "\nPlayer Bust!\n";
				running = false;
				bet = 0;
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
			break;
		}
		case STAY:
		{
			cout << "\nYou're deciding to stay!";
			cout << "\nYour Hand: ";
			player.printHand();
			cout << "\nYour Hand Value: " << player.GetHandTotal();
			dealerTurn = true;
			break;
		}

		case DOUBLE:
		{
			
			
			//Only draw one card
			player.Draw();
			cout << "\nYour Hand: ";
			player.printHand();
			cout << "\nYour Hand Value: " << player.GetHandTotal();
			dealerTurn = true;
									
			
			//break and proceed to outcome
			break;
		}

		case SPLIT:
		{
			//Create a new hand starting with one of the cards from the orignal hand
			player.Split();
			player.splitDraw();
			player.Draw();
			cout << "\nSplit Hand: ";
			player.printSplitHand();
			cout << "\nHand: ";
			player.printHand();
			break;
			
			//Seperate both hands into their own HandleChoice loop
			//Process outcome for each hand individually
		}
	}
}

int Game::GameLoop()
{
	//Welcome Message
	//---TypeHere

	//We have initialized
	InitGame();

	//Begin Game Loop
	while (running)
	{
		
		//Welcome the  player
		
		dealerTurn = false;
		bool pOutcome = false;
		
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
			if(player.GetHandTotal() == 9 || player.GetHandTotal() == 10 || player.GetHandTotal() == 11)
				cout << "3> Double\n";
				//bool pDouble; //input validation for choice 3
			if (player.GetHandCard(0) == player.GetHandCard(1))
				cout << "4> Split\n";
				//bool pSplit//input validation for choice 4
			//Need to implement insurance, but need to understand it first.
			cin >> choice;

			//Process choice selection
			if (choice == 1)
			{
				HandleChoice(HIT);		
			}

			if (choice == 2)
			{
				HandleChoice(STAY);				
			}

			if (choice == 3 /*&& pDouble*/)
			{
				HandleChoice(DOUBLE);//add input validation so it cannot be selected while its not there
				cout << "\nYou are doubling down! Your bet is being doubled!" << endl;
				player.ChangeWallet(-bet);
				bet = bet * 2;
				cout << "\nNew Bet: " << bet;
			}
			
			if (choice == 4/*&& pSplit*/)
			{
				HandleChoice(SPLIT);
				cout << "\nYou're splitting!\n";
				player.ChangeWallet(-bet);
				bet = bet * 2;
			}

			if (player.GetSplitTotal() > 0)
			{
				int splitchoice;
				cout << "\n\nSplit Hand: ";
				player.printSplitHand();
				cout << "\nWhat would you like to do for the splitted hand? ";
				cout << "\n1> Hit \n";
				cout << "2> Stay \n";
				cin >> splitchoice;
				if (splitchoice == 1)
				{
					player.splitDraw();
					cout << "\nSplit Hand: ";
					player.printSplitHand();
					cout << "\n\nYour Hand: ";
					player.printHand();
				}
				if (splitchoice == 2)
				{
					cout << "\n\nSplit Hand: ";
					player.printSplitHand();
					cout << "\n\n";
				}
					
				
			}
				
			// add input validaiton so split cannot be selected when its not there.
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
				//Theres got to be a better way to process all the outcomes.			
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
		
		//End of round/ask for restart
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