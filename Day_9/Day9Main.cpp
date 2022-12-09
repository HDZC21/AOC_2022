#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

struct Coordinate_t
{
  int x = 0;
  int y = 0;

  Coordinate_t& operator+=(const Coordinate_t move)
  {
    x += move.x;
    y += move.y;
    return *this;
  };

  size_t operator()(const Coordinate_t coorToHash) const 
  {
    size_t hash = coorToHash.x * 10 + coorToHash.y;
    return hash;
  };
};

inline bool operator==(const Coordinate_t& lhs, const Coordinate_t& rhs)
{
  if ((lhs.x == rhs.x) && (lhs.y == rhs.y))
  {
    return true;
  }
  return false;
};

Coordinate_t CreateCoordinateFromInstruction(char direction);
Coordinate_t CalculateTailChange(Coordinate_t headCoor, Coordinate_t tailCoor);
bool MovementRequired(Coordinate_t headCoor, Coordinate_t tailCoor);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  Coordinate_t head;
  Coordinate_t tail;

  std::unordered_set<Coordinate_t, Coordinate_t> tailCoors;
  tailCoors.insert(tail);
  
  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      char direction = currentLine.at(0);
      int moves = std::stoi(currentLine.substr(2, 2));

      Coordinate_t move = CreateCoordinateFromInstruction(direction);

      for (int i = 0; i < moves; i++)
      {
        head += move;
        tail = CalculateTailChange(head, tail);
        tailCoors.insert(tail);
      }
    }
  }
  
  inputFile.close();

  int uniqueCoorsVisited = tailCoors.size();

  std::cout << "Unique Coordinates Visited by Tail = " << uniqueCoorsVisited << std::endl;
}

Coordinate_t CreateCoordinateFromInstruction(char direction)
{
  Coordinate_t returnCoor;
  switch (direction)
  {
  case 'U':
    returnCoor.y++;
    break;
  case 'D':
    returnCoor.y--;
    break;
  case 'L':
    returnCoor.x--;
    break;
  case 'R':
    returnCoor.x++;
    break;
  }

  return returnCoor;
}

Coordinate_t CalculateTailChange(Coordinate_t headCoor, Coordinate_t tailCoor)
{
  // Tail doesn't move
  if (!MovementRequired(headCoor, tailCoor))
  {
    return tailCoor;
  }
  
  // Movement required
  Coordinate_t newTailPos = tailCoor;

  // X movement
  if (headCoor.y == tailCoor.y)
  {
    newTailPos.x += (headCoor.x > tailCoor.x) ? 1 : -1;
    return newTailPos;
  }
  
  // Y movement
  if (headCoor.x == tailCoor.x)
  {
    newTailPos.y += (headCoor.y > tailCoor.y) ? 1 : -1;
    return newTailPos;
  }

  newTailPos.x += (headCoor.x > tailCoor.x) ? 1 : -1;
  newTailPos.y += (headCoor.y > tailCoor.y) ? 1 : -1;
  return newTailPos;
}

bool MovementRequired(Coordinate_t headCoor, Coordinate_t tailCoor)
{
  if ((abs(headCoor.x - tailCoor.x) > 1) || (abs(headCoor.y - tailCoor.y) > 1))
  {
    return true;
  }

  return false;
}