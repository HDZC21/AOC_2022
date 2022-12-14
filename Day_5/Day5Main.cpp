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

void GenerateStacks(std::vector<std::string> &rawMap, std::vector<std::stack<char>> &stacks);
void ExecuteInstruction(std::vector<std::stack<char>> &stacks, Instruction_t &instruction);
std::string GenerateOutput(std::vector<std::stack<char>> &stacks);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  std::vector<std::string> rawMap;
  std::vector<std::stack<char>> stackMap (9);
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

    GenerateStacks(rawMap, stackMap);

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

      ExecuteInstruction(stackMap, currentInstruction);
    }

    finalOutput = GenerateOutput(stackMap);
  }

  inputFile.close();

  std::cout << "Final Stack State = " << finalOutput << std::endl;
}

void GenerateStacks(std::vector<std::string> &rawMap, std::vector<std::stack<char>> &stacks)
{
  int mapIdx = 1;
  int idxOffset = 4;

  // Read the map bottom-up so stack push works correctly
  for (int i = rawMap.size() - 1; i >= 0; i--)
  {
    // Nine total stacks
    for (int j = 0; j < 9; j++)
    {
      if (rawMap.at(i).at(mapIdx) != ' ')
      {
        stacks.at(j).push(rawMap.at(i).at(mapIdx));
      }

      mapIdx += idxOffset;
    }

    mapIdx = 1;
  }
}

void ExecuteInstruction(std::vector<std::stack<char>> &stacks, Instruction_t &instruction)
{
  char workingVal;

  for (int i = 0; i < instruction.numToMove; i++)
  {
    workingVal = stacks.at(instruction.from).top();
    stacks.at(instruction.from).pop();
    stacks.at(instruction.to).push(workingVal);
  }
}

std::string GenerateOutput(std::vector<std::stack<char>> &stacks)
{
  std::string outputBuild = "";
  for (int i = 0; i < stacks.size(); i++)
  {
    outputBuild += stacks.at(i).top();
  }

  return outputBuild;
}