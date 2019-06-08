
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
	dealerTurn = false;
	pOutcome = false;
	pDouble = false;
	pSplit = false;
	running = true;
	pSplitTurn = false;
	pSplitOutcome = false;
	player.SetDeck(&deck);
	player.ChangeWallet(100);
	dealer.SetDeck(&deck);
	deck.generateDeck();
	return;
}

void Game::restartGame()
{
	running = true;
	player.Clear();
	dealer.Clear();
	bet = 0;
	dealerTurn = false;
	pOutcome = false;
	pDouble = false;
	pSplit = false;
	return;
}

void Game::waitTime(int w)
{
	//creates a variable called dura which is an integer represented for seconds
	std::chrono::seconds dura(w);
	//passes the variable that tells the thread to wait for the w amount of seconds
	std::this_thread::sleep_for(dura);
}

//Takes string parameter, checks for any non 0-9 characters.
//If none are found, returns integer version of string, if it contains bad char, returns -1
int StringToIntValidation(std::string pStr)
{
	//First I create a string to hold any valid characters.

	std::string validnumbers;
	//iterate through chars in the string parameter
	for (char x : pStr)
	{
		//decimal representation of ascii chars 48-58 are 0-9.  If the caharacter is within those,
		//add to valid numbers string. Otherwise return -1.
		if (x > 47 && x < 58)
		{
			validnumbers += x;
		}
		else
		{
			return -1;
		}

	}
	//String to Integer conversion
	//Get number of digits to iterate backwards.
	short digitstep = validnumbers.length();
	//Declare variable that we will return that will be our integer version of string.
	int answer = 0;
	//For each character (which corresponds to an integer digit working left to right),
	for (char x : validnumbers)
	{
		//Take the characters decimal representation and subtract 48 to normalize back to decimal value, then multiply it by 10 to the power of the number of digits - 1.
		//We take that and add the previous value of answer to it.
		answer += (((x - 48) * (pow(10, digitstep-- - 1))));
	}
	//return integer values.
	return answer;
}


int Game::GetBet()
{
	string betAmount;
	betStart = true;
	//Betting Loop
	while (betStart)
	{
		cout << "\nPlace Your Bets!" << endl << "Current Balance: $" << player.GetWallet() << endl << "Bet: $";
		cin >> betAmount;
		if (StringToIntValidation(betAmount))
		{
			betValid = StringToIntValidation(betAmount);
			if (betValid <= player.GetWallet() && betValid > 0)
			{
				betStart = false;
				betAmount.clear();
				return betValid;
			}
			else if (betValid > player.GetWallet())
			{
				cout << "\nNot enough! Try Again!\n";
				betValid = 0;
				betAmount.clear();
			}
			
		}
		else
		{
			cout << "\n\nEnter valid number\n";
			cin.clear();
			cin.ignore();
			betValid = 0;
			betAmount.clear();
		}
	}
}
void Game::processBlackjack(int p, int d)
{	//If both get Blackjack
	if (p == 21 && d == 21)
	{
		pOutcome = true;
	}
	//If dealer gets Blackjack
	else if (p != 21 && d == 21)
	{
		pOutcome = true;
	}
	//If player gets Blackjack
	else if (p == 21 && d != 21)
	{
		pOutcome = true;
	}
}

void Game::processOutcome(int p, int d)
{
	if (p == 21 &&d != 21)
	{
		HandleOutcome(WIN, bet);
		cout << "\nPlayer Wins!\n";
		running = false;
		bet = 0;
	}
	else if (p > 21)
	{
		HandleOutcome(LOSE, bet);
		cout << "\nYou Lose!\n";
		running = false;
		bet = 0;
	}
	else if (d > 21)
	{
		HandleOutcome(WIN, bet);
		cout << "\nDealer Bust!\n";
		running = false;
		bet = 0;
	}
	else if (p != 21 && d == 21)
	{
		HandleOutcome(LOSE, bet);
		cout << "\nDealer Wins!\n";
		running = false;
		bet = 0;

	}
	else if (p == d)
	{
		HandleOutcome(PUSH, bet);
		cout << "\nIts a tie!\n";
		running = false;
		bet = 0;
	}
	else if (p < 21)
	{
		if (p > d)
		{
			HandleOutcome(WIN, bet);
			cout << "\nPlayer Wins!\n";
			running = false;
			bet = 0;
		}
		else if (p < d)
		{
			HandleOutcome(LOSE, bet);
			cout << "\nDealer Wins!\n";
			running = false;
			bet = 0;
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
				//HandleOutcome(LOSE, bet);
				cout << "\nPlayer Bust!\n";
				pOutcome = true;
				break;

			}
			if (player.GetHandTotal() == 21 && dealer.GetHandTotal() != 21)
			{
				//HandleOutcome(WIN, bet);
				pOutcome = true;
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
			if(pSplitTurn)
			{
				break;
			}
			else 
			{
				dealerTurn = true;
				break;
			}
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
		//Delete this comment if we can confirm it works
		processBlackjack(player.GetHandTotal(), dealer.GetHandTotal());
		
		//Ask Hit,Stay,Split,Double,Insurance
		while (bet > 0)
		{
			cout << endl << "Would you like to: " << endl;
			cout << "1> Hit\n";
			cout << "2> Stay\n";
			if (player.GetHandTotal() >= 9  || player.GetHandTotal() <= 11)
			{
				cout << "3> Double\n";
				pDouble = true; //input validation for choice 3
			}
			if (player.GetHandCard(0) == player.GetHandCard(1))
			{
				cout << "4> Split\n";
				pSplit = true; //input validation for choice 4
			}
			//Need to implement insurance, but need to understand it first.
			cin >> choice;

			//Process choice selection
			//Checks to make sure choice is a valid int
			if (StringToIntValidation(choice))
			{
				//if the choice was valid it becomes in int and put into choiceValid
				choiceValid = StringToIntValidation(choice);

				if (choiceValid == 1)
				{
					HandleChoice(HIT);
				}

				if (choiceValid == 2)
				{
					HandleChoice(STAY);
				}
				//&& pDouble is there for input validation so the player can't select the option unless conditions are met previously
				if (choiceValid == 3 && pDouble == true)
				{
					HandleChoice(DOUBLE);
					cout << "\nYou are doubling down! Your bet is being doubled!" << endl;
					player.ChangeWallet(-bet);
					waitTime(2);
					bet = bet * 2;
					cout << "\nNew Bet: " << bet;
				}
				//&& pSplit is there for input validation so the player can't select the option unless conditions are met previously
				if (choiceValid == 4 && pSplit == true)
				{
					HandleChoice(SPLIT);
					cout << "\nYou're splitting!\n";
					player.ChangeWallet(-bet);
					bet = bet * 2;
					pSplitTurn = true;

				}

			}
			
			//This is a hot mess, it needs to be fixed.
			if (pSplitTurn)
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
					player.printHand();
					pSplitTurn = false;
					pSplitOutcome = true;
				}
			}
				
			//Dealer Plays
			//While loop start for Dealer
			while (dealerTurn)
			{
				//Dealer turn plays out, will draw until 17 or more then it will stop				
				if (dealer.GetHandTotal() < 17)
				{
					dealer.Draw();
				}
				//Print Dealers Hand
				cout << "\nDealers Hand: ";
				dealer.printHand();
				//print Dealers Hand total
				cout << "\nDealer Hand Total: " << dealer.GetHandTotal();
				//3 second wait between each draw so it doesnt just vomit out all the info at once
				waitTime(3);
				//Ends the dealers turn if it hits 17 or more
				if (dealer.GetHandTotal() >= 17)
				{
					pOutcome = true;
					dealerTurn = false;
					break;
				}	
			}

			//This is to process outcomes if player decides to split
			if (pSplitOutcome && pOutcome)
			{
				while (pSplitOutcome)
				{
					//Function that takes the totals of the player and dealers hand and compares them
					processOutcome(player.GetSplitTotal(), dealer.GetHandTotal());
					processOutcome(player.GetHandTotal(), dealer.GetHandTotal());
					pSplitOutcome == false;
					pOutcome == false;
					break;
				}
				break;
			}
			else
			{
				//Process outcome as normal if no split
				while (pOutcome)
				{
					//Function that takes the totals of the player and dealers hand and compares them
					processOutcome(player.GetHandTotal(), dealer.GetHandTotal());
					pOutcome == false;
					break;					
				}
				break;
			}

		}
		
		//End of round/ask for restart
		while (running == false)
		{
			//Dont think this needs to be a hundreded characters but I thought it would help with some buffer overflow issues
			//I dont think someones gonna accidently type in 100 characters,
			char play[100];
			cout << "\nPlay Again? (y/n): " << endl;
			cin >> play;
			//Checks the first position of the chracter array and checks if its a y, that way anything that goes in that at least starts with a y it will accept it.
			//i.e yes or yse in case of typo...and yes, yeet works too....
			//Will fix that or statement later by creating a function that takes the characters in strings and converts them all to lower case
			if (play[0] == 'y' || play[0] == 'Y')
			{
				restartGame();
				//This nice little if statement will regenerate the deck if it falls below 15 cards
				if (deck.deckList.size() < 15)
					deck.generateDeck();
			}
			else if(play[0] == 'n')
				break;
			else
			{
				cout << "\nWrong input, enter 'y' for yes and 'n' for no.\n";
			}
		}
	}
	return  0;
}