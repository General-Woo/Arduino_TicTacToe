#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>   
#include <avr/pgmspace.h> 
#include <TouchScreen.h>
#include "graphic.h"

#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define TS_MINX 930
#define TS_MINY 160
#define TS_MAXX 140
#define TS_MAXY 900

#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int gameScreen = 1;
int moves = 1;

int winner = 0;  //0 = Remiza, 1 = Om, 2 = IA

boolean buttonEnabled = true;
boolean mode = true;

int board[]={0,0,0,0,0,0,0,0,0};// holds position data 0 is blank, 1 human, 2 is computer

void resetGame(){
  buttonEnabled = false;
  for(int i=0;i<9;i++)
  {
   board[i]=0;
  }
  moves = 1;
  winner = 0;
  gameScreen=2;
}

void drawStartScreen(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,319,240,WHITE);
  
  //Print "Tic Tac Toe" Text
  tft.setCursor(30,100);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Tic Tac Toe");
  
  tft.setCursor(80,30);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.print("Arduino");

  createStartButton();
  
}

void createStartButton()
{
    //Create Red Button
  tft.fillRect(60,180, 200, 40, RED);
  tft.drawRect(60,180,200,40,WHITE);
  tft.setCursor(80,188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Start Joc");
}

void initDisplay()
{
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
}

void drawGameScreen()
{
   tft.fillScreen(BLACK);
   tft.drawRect(0,0,319,240,WHITE);
   drawVerticalLine(125);
   drawVerticalLine(195);
   drawHorizontalLine(80);
   drawHorizontalLine(150);
}

void drawGameOverScreen()
{
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,318,241,WHITE);
  tft.setCursor(15,30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("JOC INCHEIAT");
  

  if(winner == 0){
    tft.setCursor(90,100);
    tft.setTextColor(MAGENTA);
    tft.setTextSize(4);
    tft.print("REMIZA");
    
  }
  if(winner == 1){
    tft.setCursor(90,80);
    tft.setTextColor(BLUE);
    tft.setTextSize(4);
    tft.print("OMUL A");
    tft.setCursor(90,130);
    tft.print("INVINS");
  }

  if(winner == 2){
    tft.setCursor(114,80);
    tft.setTextColor(GREEN);
    tft.setTextSize(4);
    tft.print("IA A");
    tft.setCursor(90,130);
    tft.print("INVINS");
  }

   createPlayAgainButton();

   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);

   
}

void createPlayAgainButton(){
  tft.fillRect(60,180, 200, 40, RED);
  tft.drawRect(60,180,200,40,WHITE);
  tft.setCursor(72,188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Joaca iar!");
}


void drawHorizontalLine(int y){
  int i=0;
  for(i=0;i<7;i++)
  {
    tft.drawLine(60,y+i,270,y+i,WHITE);
  }
}

void drawVerticalLine(int x){
  int i=0;
  for(i=0;i<7;i++)
  {
    tft.drawLine(x+i,20,x+i,220,WHITE);
  }
}

void playerMove(){
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  TSPoint p;
  boolean validMove = false;
  Serial.print("\nMutarea jucatorului:");
  do{    
    p = ts.getPoint(); 
    if (p.z > ts.pressureThreshhold){
      p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
      p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
      Serial.println(p.x);
      Serial.println(p.y);
  
      if((p.x<125)&& (p.y<80)){
        if(board[0]==0){
          Serial.println("Mutarea jucatorului: 0");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[0]=1;
          drawPlayerMove(0);  
        }
      }else if((p.x>125 && p.x<=195)&& (p.y<80)){
        if(board[1]==0){
          Serial.println("Mutarea jucatorului: 1");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[1]=1;
          drawPlayerMove(1);  
        }
      }else if((p.x>195)&& (p.y<80)){
        if(board[2]==0){
          Serial.println("Mutarea jucatorului: 2");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[2]=1;
          drawPlayerMove(2);
        }  
      }else if((p.x>0 && p.x<115)&& (p.y<150 && p.y>80)){
        if(board[3]==0){
         Serial.println("Mutarea jucatorului: 3");
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[3]=1;
          drawPlayerMove(3);  
        }
      }else if((p.x>125 && p.x<=195)&& (p.y<150 && p.y>80)){
        if(board[4]==0){
          Serial.println("Mutarea jucatorului: 4");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[4]=1;
          drawPlayerMove(4);  
        }
      }else if((p.x>195)&& (p.y<150 && p.y>80)){
        if(board[5]==0){
          Serial.println("Mutarea jucatorului: 5");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[5]=1;
          drawPlayerMove(5);  
        }
      }else if((p.x<115)&& (p.y>=150)){
        if(board[6]==0){
          Serial.println("Mutarea jucatorului: 6");
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[6]=1;
          drawPlayerMove(6);  
          Serial.println("Drawing player move");
        }
      }else if((p.x>125 && p.x<=195)&& (p.y>150)){
        if(board[7]==0){
          Serial.println("Mutarea jucatorului: 7");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[7]=1;
          drawPlayerMove(7);  
        }
      }else if((p.x>195)&& (p.y>150)){
        if(board[8]==0){
          Serial.println("Mutarea jucatorului: 8");          
          pinMode(XM, OUTPUT);
          pinMode(YP, OUTPUT);
          board[8]=1;
          drawPlayerMove(8);  
        }
      }   
    }
  }while(p.z<ts.pressureThreshhold);
}

void printBoard(){
  int i=0;
  Serial.print("Platou: [");
  for(i=0;i<9;i++){
    Serial.print(board[i]);
    Serial.print(",");
  }
  Serial.print("]");
}

int checkWinPossibillity(){
       if (board[0]==2 && board[1]==2 && board[2]==0)
    return 2;
  else if (board[0]==2 && board[1]==0 && board[2]==2)
    return 1;
  else if (board[0]==0 && board[1]==2 && board[2]==2)
    return 0;

  else if (board[3]==2 && board[4]==2 && board[5]==0)
    return 5;
  else if (board[3]==2 && board[4]==0 && board[5]==2)
    return 4;
  else if (board[3]==0 && board[4]==2 && board[5]==2)
    return 3;

  else if (board[6]==2 && board[7]==2 && board[8]==0)
    return 8;
  else if (board[6]==2 && board[7]==0 && board[8]==2)
    return 7;
  else if (board[6]==0 && board[7]==2 && board[8]==2)
    return 6;

  else if (board[0]==0 && board[3]==2 && board[6]==2)
    return 0;
  else if (board[0]==2 && board[3]==0 && board[6]==2)
    return 3;
  else if (board[0]==2 && board[3]==2 && board[6]==0)
    return 6;

  else if (board[1]==0 && board[4]==2 && board[7]==2)
    return 1;
  else if (board[1]==2 && board[4]==0 && board[7]==2)
    return 4;
  else if (board[1]==2 && board[4]==2 && board[7]==0)
    return 7;

  else if (board[2]==0 && board[5]==2 && board[8]==2)
    return 2;
  else if (board[2]==2 && board[5]==0 && board[8]==2)
    return 5;
  else if (board[2]==2 && board[5]==2 && board[8]==0)
    return 8;

  else if (board[0]==0 && board[4]==2 && board[8]==2)
    return 0;
  else if (board[0]==2 && board[4]==0 && board[8]==2)
    return 4;
  else if (board[0]==2 && board[4]==2 && board[8]==0)
    return 8;

  else if (board[2]==0 && board[4]==2 && board[6]==2)
    return 2;
  else if (board[2]==2 && board[4]==0 && board[6]==2)
    return 4;
  else if (board[2]==2 && board[4]==2 && board[6]==0)
    return 6;

  else
    return 100;
}

int checkOpponentWin(){
  if (checkWinPossibillity() == 100){
         if (board[0]==1 && board[1]==1 && board[2]==0)
      return 2;
    else if (board[0]==1 && board[1]==0 && board[2]==1)
      return 1;
    else if (board[0]==0 && board[1]==1 && board[2]==1)
      return 0;

  else if (board[3]==1 && board[4]==1 && board[5]==0)
    return 5;
  else if (board[3]==1 && board[4]==0 && board[5]==1)
    return 4;
  else if (board[3]==0 && board[4]==1 && board[5]==1)
    return 3;

  else if (board[6]==1 && board[7]==1 && board[8]==0)
    return 8;
  else if (board[6]==1 && board[7]==0 && board[8]==1)
    return 7;
  else if (board[6]==0 && board[7]==1 && board[8]==1)
    return 6;

  else if (board[0]==0 && board[3]==1 && board[6]==1)
    return 0;
  else if (board[0]==1 && board[3]==0 && board[6]==1)
    return 3;
  else if (board[0]==1 && board[3]==1 && board[6]==0)
    return 6;

  else if (board[1]==0 && board[4]==1 && board[7]==1)
    return 1;
  else if (board[1]==1 && board[4]==0 && board[7]==1)
    return 4;
  else if (board[1]==1 && board[4]==1 && board[7]==0)
    return 7;

  else if (board[2]==0 && board[5]==1 && board[8]==1)
    return 2;
  else if (board[2]==1 && board[5]==0 && board[8]==1)
    return 5;
  else if (board[2]==1 && board[5]==1 && board[8]==0)
    return 8;

  else if (board[0]==0 && board[4]==1 && board[8]==1)
    return 0;
  else if (board[0]==1 && board[4]==0 && board[8]==1)
    return 4;
  else if (board[0]==1 && board[4]==1 && board[8]==0)
    return 8;

  else if (board[2]==0 && board[4]==1 && board[6]==1)
    return 2;
  else if (board[2]==1 && board[4]==0 && board[6]==1)
    return 4;
  else if (board[2]==1 && board[4]==1 && board[6]==0)
    return 6;

  else
    return 100;

  }else
  return checkWinPossibillity();

}

int checkOpponent3(){
  if (board[0]==1){
    int v1[]={1,3};
    int randMove =random(2); 
    int c=v1[randMove];
    return c;
  }else if (board[2]==1){
    int v1[]={1,5};
    int randMove =random(2); 
    int c=v1[randMove];
    return c;
  }else if (board[6]==1){
    int v1[]={3,7};
    int randMove =random(2); 
    int c=v1[randMove];
    return c;
  }else if (board[8]==1){
    int v1[]={5,7};
    int randMove =random(2); 
    int c=v1[randMove];
    return c;
  }else if (board[1]==1||board[3]==1||board[5]==1||board[7]==1){
    int v1[]={0,2,6,8};
    int randMove =random(4); 
    int c=v1[randMove];
    return c;
  }
}

int checkOpponent3v2(){
  if (board[0]==2 && board[8]==0){
    return 8;
  }else if (board[2]==2 && board[6]==0){
    return 6;
  }else if (board[6]==2 && board[2]==0){
    return 2;
  }else if (board[8]==2 && board[0]==0){
    return 0;
  }else if (board[0]==2 && board[8]==1){
    int v2[]={2,6};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }else if (board[2]==2 && board[6]==1){
    int v2[]={0,8};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }else if (board[6]==2 && board[2]==1){
    int v2[]={0,8};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }else if (board[8]==2 && board[0]==1){
    int v2[]={2,6};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }
}

int checkOpponent5(){
  if (board[1]==1&&board[0]==2)
    return 6;
  else if (board[1]==1&&board[2]==2)
    return 8;
  else if (board[1]==1&&board[6]==2)
    return 0;
  else if (board[1]==1&&board[8]==2)
    return 2;

  else if (board[3]==1&&board[0]==2)
    return 2;
  else if (board[3]==1&&board[2]==2)
    return 0;
  else if (board[3]==1&&board[6]==2)
    return 8;
  else if (board[3]==1&&board[8]==2)
    return 6;

  else if (board[5]==1&&board[0]==2)
    return 2;
  else if (board[5]==1&&board[2]==2)
    return 0;
  else if (board[5]==1&&board[6]==2)
    return 8;
  else if (board[5]==1&&board[8]==2)
    return 6;

  else if (board[7]==1&&board[0]==2)
    return 6;
  else if (board[7]==1&&board[2]==2)
    return 8;
  else if (board[7]==1&&board[6]==2)
    return 0;
  else if (board[7]==1&&board[8]==2)
    return 2;

  else if (board[0]==1&&board[1]==2)
    return 3;
  else if (board[0]==1&&board[3]==2)
    return 1;

  else if (board[2]==1&&board[1]==2)
    return 5;
  else if (board[2]==1&&board[5]==2)
    return 1;

  else if (board[6]==1&&board[7]==2)
    return 3;
  else if (board[6]==1&&board[3]==2)
    return 7;

  else if (board[8]==1&&board[5]==2)
    return 7;
  else if (board[8]==1&&board[7]==2)
    return 5;

  else
    return 100;
}

int checkOpponent5v2(){
  if (board[0]==2 && board[8]==2){
    int v2[]={2,6};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }else if (board[6]==2 && board[2]==2){
    int v2[]={0,8};
    int randMove =random(2); 
    int c=v2[randMove];
    return c;
  }else if (board[0]==2 && board[2]==2 && board[6] == 1){
    return 8;
  }else if (board[0]==2 && board[2]==2 && board[8] == 1){
    return 6;
  }else if (board[2]==2 && board[8]==2 && board[0] == 1){
    return 6;
  }else if (board[2]==2 && board[8]==2 && board[6] == 1){
    return 0;
  }else if (board[6]==2 && board[8]==2 && board[0] == 1){
    return 2;
  }else if (board[6]==2 && board[8]==2 && board[2] == 1){
    return 0;
  }else if (board[0]==2 && board[6]==2 && board[2] == 1){
    return 8;
  }else if (board[0]==2 && board[6]==2 && board[8] == 1){
    return 2;
  }else{
    return 100;
  }
}

void arduinoMove(){
  int b = 0;
  Serial.print("\nMutarea Arduino:");

  do{

    if(mode==false){  

      if(moves==1){
              
        if (board[4]==0){  
          delay(1000);
          board[4]=2;
          Serial.print(4);
          Serial.println();
          drawCpuMove(4);
          b=1;
        }   
          
      }else if (moves==3){
        int nextMove = checkOpponent3(); 
        int c=nextMove;

        if (board[c]==0){  
          delay(1000);
          board[c]=2;
          Serial.print(c);
          Serial.println();
          drawCpuMove(c);
          b=1;
        } 

      }else if (moves==5){
        int nextMove = checkOpponentWin();
        if(nextMove == 100){  
            nextMove = checkOpponent5();
            if(nextMove == 100){    
            int randomMove =random(9); 
            if (board[randomMove]==0){  
                delay(1000);
                board[randomMove]=2;
                Serial.print(randomMove);
                Serial.println();
                drawCpuMove(randomMove);
                b=1;
              }
            }else if (board[nextMove]==0){  
              delay(1000);
              board[nextMove]=2;
              Serial.print(nextMove);
              Serial.println();
              drawCpuMove(nextMove);
              b=1;
            }  
        }else{
          delay(1000);
          board[nextMove]=2;
          drawCpuMove(nextMove);
          b=1;
        }
      }else{
        int nextMove = checkOpponentWin();
        if(nextMove == 100){  
            int randomMove =random(9); 
            if (board[randomMove]==0){  
              delay(1000);
              board[randomMove]=2;
              Serial.print(randomMove);
              Serial.println();
              drawCpuMove(randomMove);
              b=1;
            }  
        }else{
          delay(1000);
          board[nextMove]=2;
          drawCpuMove(nextMove);
          b=1;
        }
      }

    }else{

      /** 
       */

      if(moves==1){
        
        int firstMoves[] = {0, 2, 6, 8};
        int randomMove = random(4); 
        int c = firstMoves[randomMove];

        if (board[c]==0){  
          delay(1000);
          board[c]=2;
          Serial.print(c);
          Serial.println();
          drawCpuMove(c);
          b=1;
        }   
          
      }else if (moves==3){
        int nextMove = checkOpponent3v2(); 
        int c=nextMove;

        if (board[c]==0){  
          delay(1000);
          board[c]=2;
          Serial.print(c);
          Serial.println();
          drawCpuMove(c);
          b=1;
        } 

      }else if (moves==5){
        int nextMove = checkOpponentWin();
        if(nextMove == 100){  
            nextMove = checkOpponent5v2();
            if(nextMove == 100){    
            int randomMove =random(9); 
            if (board[randomMove]==0){  
                delay(1000);
                board[randomMove]=2;
                Serial.print(randomMove);
                Serial.println();
                drawCpuMove(randomMove);
                b=1;
              }
            }else if (board[nextMove]==0){  
              delay(1000);
              board[nextMove]=2;
              Serial.print(nextMove);
              Serial.println();
              drawCpuMove(nextMove);
              b=1;
            }  
        }else{
          delay(1000);
          board[nextMove]=2;
          drawCpuMove(nextMove);
          b=1;
        }
      }else{
        int nextMove = checkOpponentWin();
        if(nextMove == 100){  
            int randomMove =random(9); 
            if (board[randomMove]==0){  
              delay(1000);
              board[randomMove]=2;
              Serial.print(randomMove);
              Serial.println();
              drawCpuMove(randomMove);
              b=1;
            }  
        }else{
          delay(1000);
          board[nextMove]=2;
          drawCpuMove(nextMove);
          b=1;
        }
      }
      

      /** 
       */

    }

  }while (b<1);
}

void drawCircle(int x, int y){
  drawBitmap(x,y,circle,65,65,RED);
}

void drawX(int x, int y){
  drawBitmap(x,y,x_bitmap,65,65,GREEN);
}

void drawPlayerMove(int move){
  switch(move){
    case 0: drawCircle(55,15);  break;
    case 1: drawCircle(130,15); break;
    case 2: drawCircle(205,15); break;
    case 3: drawCircle(55,85);  break;
    case 4: drawCircle(130,85); break;
    case 5: drawCircle(205,85); break;
    case 6: drawCircle(55,155); break;
    case 7: drawCircle(130,155);break;
    case 8: drawCircle(205,155);break;
  }
}

void drawCpuMove(int move){
  switch(move){
    case 0: drawX(55,15);  break;
    case 1: drawX(130,15); break;
    case 2: drawX(205,15); break;
    case 3: drawX(55,85);  break;
    case 4: drawX(130,85); break;
    case 5: drawX(205,85); break;
    case 6: drawX(55,155); break;
    case 7: drawX(130,155);break;
    case 8: drawX(205,155);break;
  }
}

void checkWinner(){
  int qq=0;
  if (board[0]==1 && board[1]==1 && board[2]==1) { 
    winner=1; 
  }
  if (board[3]==1 && board[4]==1 && board[5]==1) { 
    winner=1; 
  }
  if (board[6]==1 && board[7]==1 && board[8]==1) { 
    winner=1; 
  }  
  if (board[0]==1 && board[3]==1 && board[6]==1) { 
    winner=1;
  }
  if (board[1]==1 && board[4]==1 && board[7]==1) { 
    winner=1;
  }
  if (board[2]==1 && board[5]==1 && board[8]==1) { 
    winner=1;
  }  
  if (board[0]==1 && board[4]==1 && board[8]==1) { 
    winner=1; 
  }
  if (board[2]==1 && board[4]==1 && board[6]==1) { 
    winner=1; 
  }

  if (board[0]==2 && board[1]==2 && board[2]==2) { 
    winner=2; 
  }
  if (board[3]==2 && board[4]==2 && board[5]==2) { 
    winner=2; 
  }
  if (board[6]==2 && board[7]==2 && board[8]==2) { 
    winner=2; 
  }  
  if (board[0]==2 && board[3]==2 && board[6]==2) { 
    winner=2; 
  }
  if (board[1]==2 && board[4]==2 && board[7]==2) { 
    winner=2; 
  }
  if (board[2]==2 && board[5]==2 && board[8]==2) { 
    winner=2; 
  }  
  if (board[0]==2 && board[4]==2 && board[8]==2) { 
    winner=2; 
  }
  if (board[2]==2 && board[4]==2 && board[6]==2) { 
    winner=2; 
  }
 
}

void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}

void playGame(){
  do{
    if(moves%2==1){
      arduinoMove();
      printBoard();
      checkWinner();
    }else{
      playerMove(); 
      printBoard();
      checkWinner();  
    }
    moves++;
  }
  while (winner==0 && moves<10); 
  if(winner == 1){
    Serial.println("Omul a castigat");
    delay(3000);
    gameScreen=3;
    drawGameOverScreen();
    mode = !mode;
  }else if(winner ==2){
     Serial.println("Calculatorul a castigat");
     delay(3000);
     gameScreen=3;
     drawGameOverScreen();
     mode = !mode;
  }else{
    Serial.println("Remiza");
    delay(3000);
    gameScreen=3;
    drawGameOverScreen();
    mode = !mode;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.print("Incepere...");
  randomSeed(analogRead(0));
 
  initDisplay();
  drawStartScreen();
}

void loop(){
  TSPoint p = ts.getPoint();  

  if(gameScreen==3)
   {
    buttonEnabled =true;
   }
  
  if (p.z > ts.pressureThreshhold) {

   p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
   p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);

   Serial.print("X = "); Serial.print(p.x);
   Serial.print("\tY = "); Serial.print(p.y);
   Serial.print("\n");
       
   if(p.x>60 && p.x<260 && p.y>180 && p.y<220 && buttonEnabled)
   {
    buttonEnabled = false;
    Serial.println("Button Pressed");
    resetGame();  
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
    
   drawGameScreen();
   playGame();
   
   } 
   delay(10);  
  }
}
