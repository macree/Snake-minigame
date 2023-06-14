struct Cell
{
  uint16_t posX{};
  uint16_t posY{};
  uint16_t lastPosX{};
  uint16_t lastPosY{};
};

class Snake
{
  uint16_t posX{};
  uint16_t posY{};
  uint16_t lastPosX{};
  uint16_t lastPosY{};
  uint16_t length{1};

//std::map<int, std::pair<uint16_t, uint16_t>> body; // int este cheia, iar pairul sunt coordonatele x si y a fiecarui punct din corpul snake ului
  
  public:
  std::vector<Cell> body;
  Snake(uint16_t x, uint16_t y):posX(x),posY(y)
  {
    body.push_back({posX, posY, posX, posY}); // nu conteaza primele valaori de inceput cand incepe jocul
    displayBodyParts();
  }
  ~Snake(){}

  void displayBodyParts()
  {
    for(auto i=body.begin();i!=body.end();++i)
      {
      std::cout<<length<<". CurrentX: "<<i->posX<<" CurrentY: "<<i->posY<<" / LastX: "<<i->lastPosX<<" LastY: "<<i->lastPosY<<"\n";
      }
  }

  void setBodyPartsTable(Board& board)
  {
    int i=0;
    for(;i<body.size();++i)
      {
        board.boardTable[body[i].posX][body[i].posY]=1;
      }
    board.setValue(body[i-1].lastPosX, body[i-1].lastPosY, 0);
  }
    
  void placeSnake(Board& board, Snake& snake)
  {
    board.boardTable[snake.posX][snake.posY]=1;
  }

  void addBodySnake(const uint16_t& x, const uint16_t& y, const uint16_t& lx, const uint16_t& ly)//lx=lastx ly=lasty
  {
    body.push_back({x,y,lx,ly});
    ++length;
  }

  void updateCurrentPosHead(const uint16_t& x, const uint16_t& y, const uint16_t& lx, const uint16_t& ly)
  {
    body[0].posX=x;
    body[0].posY=y;
    body[0].lastPosX=lx;
    body[0].lastPosY=ly;
  }
  void updateBodyPartsPositions(Board& board)//functia asta este pentru a face ca corpul sarpelui sa urmeze acelasi drum ca si headul.
  {
    uint16_t auxX{};
    uint16_t auxY{};
    int i=1;
    for(;i<body.size();++i)
      {
        auxX=body[i].posX;
        auxY=body[i].posY;

        body[i].posX=body[i-1].lastPosX;
        body[i].posY=body[i-1].lastPosY;

        body[i].lastPosX=auxX;
        body[i].lastPosY=auxY;     
      }
  }

  void move(Board& board)
  {
    char direction{};
    
    retry:
    std::cout<<"Where you want to move u/d/l/r?\n";
    std::cin>>direction;
    switch(direction)
      {
        case 'u'://up
        {
            if(board.checkIsOutside(posX-1, posY))
            {
              std::cout<<"You cannot go that way, it is out of the border!\n";
              goto retry;
            }
            if(board.checkIsBait(posX-1,posY))
            {
              addBodySnake(posX,posY, lastPosX, lastPosY);
              lastPosX=posX;
              lastPosY=posY;
              
              posX-=1;
              
              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
              
              break;
            }
            if(board.isCellEmpty(posX-1, posY))
            {
              lastPosX=posX;
              lastPosY=posY;
              posX-=1;
      
              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
              break;
            }
            if(board.isBodyPart(posX-1, posY))
            {
              std::cout<<"You have hit your own body! You have lost!";
              exit(0);
            }
        }
        case 'd'://down
        {
            if(board.checkIsOutside(posX+1, posY))
            {
              std::cout<<"You cannot go that way, it is out of the border!\n";
              goto retry;
            }
            if(board.checkIsBait(posX+1,posY))
            {
              addBodySnake(posX,posY, lastPosX, lastPosY);
              lastPosX=posX;
              lastPosY=posY;
          
              posX+=1;

              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);

              break;
            }
            if(board.isCellEmpty(posX+1, posY))
            {
              lastPosX=posX;
              lastPosY=posY;
              posX+=1;
              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
              break;
            }
            if(board.isBodyPart(posX+1, posY))
            {
              std::cout<<"You have hit your own body! You have lost!";
              exit(0);
            }
        }
        case 'l'://left
        {
            if(board.checkIsOutside(posX, posY-1))
            {
              std::cout<<"You cannot go that way, it is out of the border!\n";
              goto retry;
            }
            if(board.checkIsBait(posX,posY-1))
            {
              addBodySnake(posX,posY, lastPosX, lastPosY);
              lastPosX=posX;
              lastPosY=posY;

              posY-=1;

              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);

              break;
            }
            if(board.isCellEmpty(posX, posY-1))
            {
              lastPosX=posX;
              lastPosY=posY;
              posY-=1;
              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
              
              break;
            }
            if(board.isBodyPart(posX, posY-1))
            {
              std::cout<<"You have hit your own body! You have lost!";
              exit(0);
            }
        }
        case 'r'://right
        {
            if(board.checkIsOutside(posX, posY+1))
            {
              std::cout<<"You cannot go that way, it is out of the border!\n";
              goto retry;
            }
            if(board.checkIsBait(posX,posY+1))
            {
              addBodySnake(posX,posY, lastPosX, lastPosY);
              lastPosX=posX;
              lastPosY=posY;
              
              posY+=1;

              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
 
              break;
            }
            if(board.isCellEmpty(posX, posY+1))
            {
              lastPosX=posX;
              lastPosY=posY;
              posY+=1;
              updateCurrentPosHead(posX,posY,lastPosX, lastPosY);
              updateBodyPartsPositions(board);
        
              break;
            }
            if(board.isBodyPart(posX+1, posY))
            {
              std::cout<<"You have hit your own body! You have lost!";
              exit(0);
            }
        }
        case 'q':
        {
          board.quitGame();
          exit(0);
        }
        default:
          std::cout<<"Invalid direction! Please choose u/d/l/r.\n";
          goto retry;
          break;
      }
    setBodyPartsTable(board);
  }

  friend class Board;
  //friend void displayBoard();
};