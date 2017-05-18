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
void PrintGameSummary();

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
	cout << "\nBem vindo ao divertido game, Bulls & Cows!\n";
	cout << "Voce eh capaz de adivinhar isograma de " << WORD_LENGTH << " letras que estou pensando?\n";
	cout << endl;
}

void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guess
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText guess = GetGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		// Print32 number of bulls and cows
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << ". Cows = " << BullCowCount.Cows << endl;
		cout << endl;			
	}
	
		
	// TODO Summarise game
	PrintGameSummary();
	return;
}

FText GetGuess()
{
	FText guess = "";
	int32 CurrentTry = BCGame.GetCurrentTry();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		cout << "Tentativa " << CurrentTry << ". Digite seu palpite: ";
		getline(cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				cout << "Erro: A palavra digitada não é valida, tente novamente!\n";
				break;
			case EGuessStatus::Not_Ispgram:
				cout << "Erro: Por favor digite uma palavra sem letras repetidas!\n";
				break;
			case EGuessStatus::Not_Lowercase:
				cout << "Error: Por favor digite todas as letras em minúsculo!\n";
				break;
			default:
				break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);// Capturando a tentativa do jogador	

	return guess;
}

bool AskToPlayAgain()
{	cout << "Voce deseja jogar novamente com a mesma palavra? (S/N): ";
	FText Response = "";
	getline(cin, Response);
	return (Response[0] == 'S' || Response[0] == 's');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{	
		cout << "Muito bem - voce venceu!\n";
	}
	else {
		cout << "Lhe desejo mais sorte da proxima vez!\n";
	}
}