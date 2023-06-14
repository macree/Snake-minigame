#include <iostream>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <forward_list>
#include <chrono>
#include <thread>
//#include <Windows.h>
#include <unistd.h>//pentru sleep

#include "board.h"
#include "snake.h"

int main() {
  Board table(5,5);
  Snake snake(3,3);
  
  snake.placeSnake(table, snake);

  table.displayBoard();

  char direction{};
  
  while(true)
  { 
    snake.move(table);
    snake.displayBodyParts();
    table.displayBoard();
  }
  
  return 0;
}