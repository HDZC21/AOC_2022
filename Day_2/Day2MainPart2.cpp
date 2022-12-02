#include <iostream>
#include <fstream>
#include <string>

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

const int LOSE = 0;
const int DRAW = 3;
const int WIN = 6;

int chooseHandForResult(char desiredResult, int opponentPlay);
int convertChoiceToInt(char playedHand);
int scoreRound(int userPlay, int opponentPlay);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;
  int totalScore = 0;

  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      int opponentPlay = convertChoiceToInt(currentLine[0]);
      int userPlay = chooseHandForResult(currentLine[2], opponentPlay);

      totalScore += scoreRound(userPlay, opponentPlay);
    }
  }
  inputFile.close();

  std::cout << "Player Score = " << totalScore << std::endl;
}

int chooseHandForResult(char desiredResult, int opponentPlay)
{
  if (desiredResult == 'Y')
  {
    return opponentPlay;
  }
  
  if (opponentPlay == ROCK)
  {
    if (desiredResult == 'X')
    {
      return SCISSORS;
    }
    else
    {
      return PAPER;
    }
  }
  else if (opponentPlay == PAPER)
  {
    if (desiredResult == 'X')
    {
      return ROCK;
    }
    else
    {
      return SCISSORS;
    }
  }
  else
  {
    if (desiredResult == 'X')
    {
      return PAPER;
    }
    else
    {
      return ROCK;
    }
  }
}

int convertChoiceToInt(char playedHand)
{
  if ((playedHand == 'A') || (playedHand == 'X'))
  {
    return ROCK;
  }
  else if ((playedHand == 'B') || (playedHand == 'Y'))
  {
    return PAPER;
  }
  else
  {
    return SCISSORS;
  }
}

int scoreRound(int userPlay, int opponentPlay)
{
  if (userPlay == opponentPlay)
  {
    return userPlay + DRAW;
  }
  else if (((userPlay == ROCK) && (opponentPlay == SCISSORS)) ||
      ((userPlay == PAPER) && (opponentPlay == ROCK)) || 
      ((userPlay == SCISSORS) && (opponentPlay == PAPER)))
  {
    return userPlay + WIN;
  }
  else
  {
    return userPlay + LOSE;
  }
}