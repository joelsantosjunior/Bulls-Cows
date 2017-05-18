#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All velues are initialized with 0
struct FBullCowCount
{	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus { Invalid_Status, OK, Not_Ispgram, Wrong_Length, Not_Lowercase };

class FBullCowGame {
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString guess);

	

	void Reset(); // TODO make a more rich return value	

// ^^ Please try and ignore this and focus on the int32erface above ^^
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString guess) const;
	bool IsLowerCase(FString guess) const;
};
