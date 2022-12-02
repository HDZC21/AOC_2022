#include <iostream>
#include <fstream>
#include <string>

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

const int LOSE = 0;
const int DRAW = 3;
const int WIN = 6;

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
      char opponentPlay = currentLine[0];
      char userPlay = currentLine[2];

      totalScore += scoreRound(convertChoiceToInt(userPlay), convertChoiceToInt(opponentPlay));
    }
  }
  inputFile.close();

  std::cout << "Player Score = " << totalScore << std::endl;
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