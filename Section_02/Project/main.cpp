#include <iostream>
#include <string>
#include "FBullCowGame.h"

using namespace std;
using FText = std::string;
using int32 = int;

// Declaração de funções
void PrintIntro();
FText GetGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game
const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();


int32 main()
{	do{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());	
	return 0;
}

void PrintIntro()
{	// Constante para definir o tamanho das palavras
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	cout << endl;
}

void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guess
	while ( !BCGame.IsGameWon() )
	{
		for (int32 i = 0; i < MaxTries; i++)
		{
			FText guess = GetGuess();
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
			// Print32 number of bulls and cows
			cout << "Bulls = " << BullCowCount.Bulls;
			cout << ". Cows = " << BullCowCount.Cows << endl;
			cout << endl;
		}
	}
	// TODO Summarise game
}

FText GetGuess()
{
	FText guess = "";
	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		cout << "Try " << CurrentTry << ". Enter your guess: ";
		getline(cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				cout << "Error: The type of word is incorrect, type a valid word!\n";
				break;
			case EGuessStatus::Not_Ispgram:
				cout << "Error: Please enter a word without repeating letters!\n";
				break;
			case EGuessStatus::Not_Lowercase:
				cout << "Error: Please enter all lowercase letters!\n";
				break;
			default:
				break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);// Capturando a tentativa do jogador	

	return guess;
}

bool AskToPlayAgain()
{	cout << "Do you want to play again? (Y/N): ";
	FText Response = "";
	getline(cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
}