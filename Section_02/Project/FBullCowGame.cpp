#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{	constexpr int32 MAX_TRIES = 4;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{	
	if (FBullCowGame::GetHiddenWordLength() != guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!FBullCowGame::IsIsogram(guess))
	{
		return EGuessStatus::Not_Ispgram;
	}
	else if (!FBullCowGame::IsLowerCase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
		

	
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (int32 GChar = 0; GChar < WordLength; GChar++)
	{
		for (int32 MHChar = 0; MHChar < WordLength; MHChar++)
		{
			if (MyHiddenWord[GChar] == guess[MHChar])
			{
				if (GChar == MHChar)
				{
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	if (guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
	for (auto Letter : guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
