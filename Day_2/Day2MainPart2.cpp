#include <iostream>
#include <fstream>
#include <string>

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

const int LOSE = 0;
const int DRAW = 3;
const int WIN = 6;

int ChooseHandForResult(char desiredResult, int opponentPlay);
int ConvertChoiceToInt(char playedHand);
int ScoreRound(int userPlay, int opponentPlay);

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
      int opponentPlay = ConvertChoiceToInt(currentLine[0]);
      int userPlay = ChooseHandForResult(currentLine[2], opponentPlay);

      totalScore += ScoreRound(userPlay, opponentPlay);
    }
  }
  inputFile.close();

  std::cout << "Player Score = " << totalScore << std::endl;
}

int ChooseHandForResult(char desiredResult, int opponentPlay)
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

int ConvertChoiceToInt(char playedHand)
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

int ScoreRound(int userPlay, int opponentPlay)
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