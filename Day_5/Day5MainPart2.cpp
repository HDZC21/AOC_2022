#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

struct Instruction_t
{
  int numToMove;
  int from;
  int to;
};

void GenerateVectorMap(std::vector<std::string> &rawMap, std::vector<std::vector<char>> &vectorMap);
void ExecuteInstruction(std::vector<std::vector<char>> &vectorMap, Instruction_t &instruction);
std::string GenerateOutput(std::vector<std::vector<char>> &vectorMap);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  std::vector<std::string> rawMap;
  std::vector<std::vector<char>> vectorMap (9);
  Instruction_t currentInstruction;
  std::string finalOutput;

  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      if (currentLine.find('1') == std::string::npos)
      {
        rawMap.push_back(currentLine);
      }
      else
      {
        // Skip a line
        getline(inputFile, currentLine);
        break;
      }
    }

    GenerateVectorMap(rawMap, vectorMap);

    // Start reading moves
    while(getline(inputFile, currentLine))
    {
      // How many crates to move
      std::string tempLine = currentLine.substr(5, 2);
      if (tempLine.at(1) == ' ')
      {
        tempLine = tempLine.at(0);
      }

      currentInstruction.numToMove = std::stoi(tempLine);

      // Where to move crate from (subtract 1 for index)
      tempLine = currentLine.substr(currentLine.size() - 6, 1);
      currentInstruction.from = (std::stoi(tempLine) - 1);

      // Where to move crate to (subtract 1 for index)
      tempLine = currentLine.substr(currentLine.size() - 1, 1);
      currentInstruction.to = (std::stoi(tempLine) - 1);

      ExecuteInstruction(vectorMap, currentInstruction);
    }

    finalOutput = GenerateOutput(vectorMap);
  }

  inputFile.close();

  std::cout << "Final Stack State = " << finalOutput << std::endl;
}

void GenerateVectorMap(std::vector<std::string> &rawMap, std::vector<std::vector<char>> &vectorMap)
{
  int mapIdx = 1;
  int idxOffset = 4;

  // Read the map bottom-up so stack push works correctly
  for (int i = rawMap.size() - 1; i >= 0; i--)
  {
    // Nine total crate stacks
    for (int j = 0; j < 9; j++)
    {
      if (rawMap.at(i).at(mapIdx) != ' ')
      {
        vectorMap.at(j).push_back(rawMap.at(i).at(mapIdx));
      }

      mapIdx += idxOffset;
    }

    mapIdx = 1;
  }
}

void ExecuteInstruction(std::vector<std::vector<char>> &vectorMap, Instruction_t &instruction)
{
  char workingVal;
  int startingIdx = (vectorMap.at(instruction.from).size()) - instruction.numToMove;
  std::cout << "StartingIdx: " << startingIdx << std::endl;

  for (int i = startingIdx; i < vectorMap.at(instruction.from).size(); i++)
  {
    vectorMap.at(instruction.to).push_back(vectorMap.at(instruction.from).at(i));
  }

  vectorMap.at(instruction.from).erase(vectorMap.at(instruction.from).begin() + startingIdx, vectorMap.at(instruction.from).end());
}

std::string GenerateOutput(std::vector<std::vector<char>> &vectorMap)
{
  std::string outputBuild = "";
  for (int i = 0; i < vectorMap.size(); i++)
  {
    outputBuild += vectorMap.at(i).back();
  }

  return outputBuild;
}