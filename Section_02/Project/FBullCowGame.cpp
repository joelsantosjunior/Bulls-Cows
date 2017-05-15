#include "FBullCowGame.h"
#include <iostream>

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{	constexpr int32 MAX_TRIES = 4;
	const FString HIDDEN_WORD = "nop";

	MyMaxTries = MAX_TRIES;	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{	
	if (FBullCowGame::GetHiddenWordLength() != guess.length())
		return EGuessStatus::Wrong_Length;

	
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

bool FBullCowGame::IsIsogram(FString guess)
{	
	bool IsIsogramN = true;
	FString Copy = guess;
	for (int32 GChar = 0; GChar < GetHiddenWordLength(); GChar++)
	{	for (int32 CChar = 0; CChar < GetHiddenWordLength(); CChar++)
		{	if(guess[GChar] == Copy[CChar] && (GChar != CChar))
			IsIsogramN = false;
		}
	}
	return IsIsogramN;
}

