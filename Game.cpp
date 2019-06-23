
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
	betting = true;
	pOutcome = false;
	pDouble = false;
	pSplit = false;
	running = true;
	pSplitTurn = false;
	pSplitOutcome = false;
	playAgain = false;
	player.SetDeck(&deck);
	player.ChangeWallet(100);
	dealer.SetDeck(&deck);
	deck.generateDeck();
	return;
}

void Game::restartGame()
{
	y = 0;
	running = true;
	betting = true;
	player.Clear();
	dealer.Clear();
	player.ClearSplit();
	bet = 0;
	dealerTurn = false;
	pOutcome = false;
	pDouble = false;
	pSplit = false;
	playAgain = false;
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
		cout << "Place Your Bets!" << endl << "Current Balance: $" << player.GetWallet() << endl << "Bet: $";
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
				cout << "\nYou don't have that much in your wallet!\n";
				betValid = 0;
				betAmount.clear();
			}
			else
			{
				cout << "\n\nPlease enter valid number.\n";
			}			
		}
	}
}

//This doesnt do jack shit, need to work on it
void Game::processBlackjack(int p, int d)
{	//If both get Blackjack
	if (p == 21 && d == 21)
	{
		betting = false;
		processOutcome(player.GetHandTotal(), dealer.GetHandTotal(), bet);
		playAgain = true;
	}
	//If dealer gets Blackjack
	else if (p != 21 && d == 21)
	{
		betting = false;
		processOutcome(player.GetHandTotal(), dealer.GetHandTotal(), bet);
		playAgain = true;
	}
	//If player gets Blackjack
	else if (p == 21 && d != 21)
	{
		betting = false;
		processOutcome(player.GetHandTotal(), dealer.GetHandTotal(), bet);
		playAgain = true;
	}
}


//Takes in the total handsize of the (p)layers hand, (d)ealers hand and the current (b)et
//Still gotta be a better way to process outcomes, maybe a switch? So it looks cleaner?
void Game::processOutcome(int p, int d, int b)
{
	if (p == 21 &&d != 21)
	{
		HandleOutcome(WIN, b);
		cout << "\n\nPlayer Wins!\n";
	}
	else if (p > 21)
	{
		HandleOutcome(LOSE, b);
		cout << "\n\nYou Lose!\n";	
	}
	else if (d > 21)
	{
		HandleOutcome(WIN, b);
		cout << "\n\nDealer Bust!\n";
	}
	else if (p != 21 && d == 21)
	{
		HandleOutcome(LOSE, b);
		cout << "\n\nDealer Wins!\n";
	}
	else if (p == d)
	{
		HandleOutcome(PUSH, b);
		cout << "\n\nIts a tie!\n";
	}
	else if (p < 21)
	{
		if (p > d)
		{
			HandleOutcome(WIN, b);
			cout << "\n\nPlayer Wins!\n";
		}
		else if (p < d)
		{
			HandleOutcome(LOSE, b);
			cout << "\n\nDealer Wins!\n";
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

//Anyway to make this universal? So it can be applied to splits as well?
void Game::HandleChoice(CHOICE pC)
{
	switch (pC)
	{
		case HIT: 
		{
			cout << "\n\nYou are deciding to hit!";
			waitTime(2);
			player.Draw();
			cout << "\n\nYour Hand: ";
			player.printHand();
			cout << "\nYour Hand Value: " << player.GetHandTotal();
			waitTime(2);
			if (player.GetHandTotal() > 21)
			{
				cout << "\nPlayer Bust!\n";
				pOutcome = true;
				betting = false;
				playAgain = true;
				break;
			}
			if (player.GetHandTotal() == 21 && dealer.GetHandTotal() != 21)
			{
				pOutcome = true;
				betting = false;
				break;
			}
			break;
		}

		case STAY:
		{
			cout << "\nYou are deciding to stay!";
			waitTime(2);
			cout << "\n\nYour Hand: ";
			player.printHand();
			cout << "\nYour Hand Value: " << player.GetHandTotal() << endl;
			waitTime(2);
			if(pSplitTurn)
			{
				break;
			}
			else 
			{
				dealerTurn = true;
				betting = false;
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
		cout << "\nDealer Shows: " << dealer.ShowFirstCard() << endl;
		//Display Players hand
		cout << "\nYour Hand: ";
		player.printHand();
		cout << "\nYour Hand Value: " << player.GetHandTotal();
		//Handle BlackJacks
		//This needs to be worked on doesnt really do shit but the idea is there
		//Delete this comment if we can confirm it works
		processBlackjack(player.GetHandTotal(), dealer.GetHandTotal());
		
		//Ask Hit,Stay,Split,Double,Insurance
		while (betting)
		{
			cout << endl << "\nWould you like to: " << endl;
			cout << "1> Hit\n";
			cout << "2> Stay\n";
			//Had to add player.GetWallet() > 0 at the end because you were able to double your bet even though you had no money
			if (player.GetHandTotal() >= 9  && player.GetHandTotal() <= 11 && player.GetWallet() > 0 && y == 0)
			{
				cout << "3> Double\n";
				pDouble = true; //input validation for choice 3
			}
			if (player.GetHandCard(0) == player.GetHandCard(1) && y == 0)//should only allow you to split once.
			{
				cout << "4> Split\n";
				pSplit = true; //input validation for choice 4
			}
			//Need to implement insurance, but need to understand it first.
			cout << "\nEnter a number selection:";
			cin >> choice;

			//Process choice selection
			//Checks to make sure choice is a valid int
 			if (StringToIntValidation(choice))
			{
				//if the choice was valid it becomes in int and put into choiceValid
				choiceValid = StringToIntValidation(choice);

				if (choiceValid == 1)
				{
					y++;
					HandleChoice(HIT);
				}

				if (choiceValid == 2)
				{
					HandleChoice(STAY);
					break;
				}
				//&& pDouble is there for input validation so the player can't select the option unless conditions are met previously
				if (choiceValid == 3 && pDouble == true)
				{
					y++;
					HandleChoice(DOUBLE);
					cout << "\nYou are doubling down! Your bet is being doubled!" << endl;
					player.ChangeWallet(-bet);
					waitTime(2);
					bet = bet * 2;
					cout << "\nNew Bet: " << bet;
					break;
				}
				//&& pSplit is there for input validation so the player can't select the option unless conditions are met previously
				if (choiceValid == 4 && pSplit == true)
				{
					y++;
					HandleChoice(SPLIT);
					cout << "\nYou're splitting!\n";
					player.ChangeWallet(-bet);
					splitBet = bet;
					pSplitTurn = true;

				}

			}
			
			//This is a hot mess, it needs to be fixed.
			while (pSplitTurn)
			{
				cout << "\n\nSplit Hand: ";
				player.printSplitHand();
				cout << "\nWhat would you like to do for the splitted hand? ";
				cout << "\n1> Hit \n";
				cout << "2> Stay \n";
				cin >> splitChoice;
				splitChoiceValid = StringToIntValidation(splitChoice);
				if (splitChoiceValid == 1)
				{
					player.splitDraw();
					cout << "\nSplit Hand: ";
					player.printSplitHand();
					cout << "\n\nYour Hand: ";
					player.printHand();
				}
				if (splitChoiceValid == 2)
				{
					cout << "\n\nSplit Hand: ";
					player.printSplitHand();
					cout << "\n\n";
					cout << "You are deciding to stay on your split hand!\n\n";
					waitTime(2);
					cout << "Your hand: ";
					player.printHand();
					cout << "\nYour hand value: " << player.GetHandTotal();
					pSplitTurn = false;
					pSplitOutcome = true;
					break;
				}
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
			waitTime(2);
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

		//This is to process outcomes if player decides to split, this also needs to be worked on
		if (pSplitOutcome && pOutcome)
		{
			while (pSplitOutcome)
			{
				//Function that takes the totals of the player and dealers hand and compares the
				cout << "\n\nProcessing your split hand outcome!\n";
				waitTime(2);
				processOutcome(player.GetSplitTotal(), dealer.GetHandTotal(), splitBet);
				waitTime(2);
				cout << "\n\nProcessing your hand outcome!\n";
				waitTime(2);
				processOutcome(player.GetHandTotal(), dealer.GetHandTotal(), bet);
				pSplitOutcome == false;
				pOutcome == false;
				playAgain == true;
				break;
			}
	
		}
		else
		{
			//Process outcome as normal if no split
			while (pOutcome)
			{
				//Function that takes the totals of the player and dealers hand and compares them
				cout << "\n\nProcessing your hand outcome!\n";
				waitTime(2);
				processOutcome(player.GetHandTotal(), dealer.GetHandTotal(), bet);
				pOutcome = false;
				playAgain = true;
				break;
			}
			
		}
		
		//End of round/ask for restart
		while (playAgain)
		{
			//Dont think this needs to be a hundreded characters but I thought it would help with some buffer overflow issues
			//I dont think someones gonna accidently type in 100 characters,
			char play[100];
			waitTime(2);
			cout << "\nPlay Again?" << endl;
			cout << "\nY/N: ";
 			cin >> play;
			cout << "\n";

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
			else if (play[0] == 'n')
			{
				running = false;
				break;
			}
			else
			{
				cout << "\nWrong input, enter 'y' for yes and 'n' for no.\n";
			}
	
		}
	}
	return  0;
}