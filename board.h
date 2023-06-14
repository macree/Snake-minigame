class Board
{
  public:
  uint16_t boardTable[100][100]={0};
  uint16_t length{};
  uint16_t width{};

  Board(uint16_t l, uint16_t w):length(l), width(w)
  {
    generateBait();
  }
  ~Board(){}

  bool checkIsOutside(uint16_t x, uint16_t y)
  { 
    if(x<0||x>=length||y>=width||y<0)
      return true;
    return false;
  }

  bool checkIsBait(uint16_t x, uint16_t y)
  {
    if(boardTable[x][y]==2)
    {
      generateBait();
      return true;
    }
    return false;
  }

  void generateBait()//generare random a momelii
  {
    retryBait:
    retryX:
    
    srand((uint16_t) time(NULL)); //returns the current time of the system as the number of seconds that have elapsed since January 1, 1970, at 00:00:00
    uint16_t randomX = rand() % length; // de la 0 pana la 99
    if(randomX<0||randomX>=length)
      goto retryX;

    retryY:
    
    uint16_t randomY = rand() % width;
    if(randomY<0||randomY>=width)
      goto retryY;

    if(isCellEmpty(randomX, randomY)&&(!checkIsBait(randomX, randomY)))
      boardTable[randomX][randomY]=2; //2 este baitul, 0 este celula goala, 1 este corpul snake-ului
    else goto retryBait;
  }

  bool isCellEmpty(uint16_t x, uint16_t y)
  {
    if(boardTable[x][y]==0)
      return true;
    return false;
  }

  bool isBodyPart(uint16_t x, uint16_t y)
  {
    if(boardTable[x][y]==1)
      return true;
    return false;
  }

  bool isBait(uint16_t x, uint16_t y)
  {
    if(boardTable[x][y]==2)
      return true;
    return false;
  }

  void setValue(uint16_t x, uint16_t y, uint8_t value)
  {
      this->boardTable[x][y]=value;
  }

  void displayBoard()
  {
    for(int i=0;i<length;++i)
      {
      for(int j=0;j<width;++j)
        std::cout<<boardTable[i][j]<<" ";
      std::cout<<"\n";
      }
    std::cout<<"\n";
  }

  void quitGame()
  {
    std::cout<<"You have quitted the game!";
  }
  
  uint16_t getTableLength()
  {
    return length;
  }
  uint16_t getTableWidth()
  {
    return width;
  }

  //friend void displaySnakeOnTable(Board, Snake);
};