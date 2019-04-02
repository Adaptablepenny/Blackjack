#include <iostream>
#include <string>
#include <vector>
#include "Deck.h"
#include "player.h"
#include "dealer.h"
#include "Game.h"

using namespace std;

//Deck deck;
//int startWallet = 1000;
//char choice;
Game game;





int main()
{
	game.GameLoop();
}


	/*
	//spacing for readability:
	cout << "\n\n\n";
	Player player(&deck);
	Dealer dealer(&deck);
	Game game;

	/*cout << "\nWould you like to play?(y/n) ";
	cin >> startGame;
	if (startGame == 'y')
	{
		player.Wallet = 100;
		deck.generateDeck();
	}

	game.initGame();

	while (game.startGame == true)
	{
		if (player.Wallet > 0)
		{
			//Drawing two cards for player here.
			if (player.hand.size() == 0)
			{
				player.Draw();
				player.Draw();
			}

			cout << "\n\n";

			//Drawing two cards for dealer here.
			if (dealer.dHand.size() == 0)
			{
				dealer.Draw();
				dealer.Draw();
			}

			//Lines for readability and showing the first card of the dealer.
			cout << "\n\n\n";
			cout << "\nDealer shows a: " << dealer.ShowFirstCard() << endl;

			//Lines for readability and showing the players hand and starting the bet.
			cout << "The Players hand contains:\n";
			player.printHand();
			cout << "Here is your wallet: " << player.Wallet << endl;
	
				player.Betting();
			}
		else
		{
			cout << "\nGame Over!";
			cout << "Play Again?(y/n) ";
			//cin >> game.startGame;
		}
		

		/*This will be the game loop, always checking to see if the player has money or if
		they dont want to play after a round. something like that... 
		//This whole play function will be a function as soon as I figure out input validation for betting and checking hand value.
		while (player.betCash > 0)
		{
			if (player.Wallet >= 0)
			{

				cout << "(H)it, (S)tay, (F)old: ";
				cin >> choice;
				if (choice == 'h')
				{
					player.Draw();
					dealer.Draw();
				}

				if (choice == 's')
				{
					//stay
					//dealer draw
				}

				if (choice == 'f')
				{
					player.betCash = 0;
					player.Clear();
					dealer.Clear();
					break;
				}

			}//end if statement
			
		};//playing game loop
		
		

	};//stargame loop

}*/

