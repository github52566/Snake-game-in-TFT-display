#include <EEPROM.h>

// UTFT_Demo_320x240 // 
#include <UTFT.h>
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
UTFT myGLCD(ILI9325D_16,38,39,40,41);

struct item{
  int x;
  int y;
  };

item snake[100];
item food;
int snake_position = 1;//if 0 means that going left,1 means that going right,2 means that going down,3 means that going up
int snakesize = 5;
int point = 0;
int highscore[5];
int timer = 50;
int foodtype = 0; // if 1 then bonus otherwise normal
int bonusfoodstate = 1;
int currentsnakestate;
int test_speed = 10;
int state = 2; //0 means game running,1 means gameover,2 means menu,3 means highscore,4 means pause menu
int menuupblock = 1;
int menudownblock = 0;
int menuposition = 0;//if 0 means that Newgame,1 means that Highscore
int pausemenuposition = 0; //if 0 means that Continuegame,1 means that NewGame,2 means that HighScore
int highscoremenuposition = 0;
int gameovermenuposition = 0;
int gamepauseposition = 0;
int comefrompausemenu = 0;
int ypos1 = 30;
int ypos2 = 50;
int normal_food = 0;
int bonus_food = 0;
void setup() 
{  
  Serial.begin(9600);
  pinMode(8,INPUT);//left
  pinMode(9,INPUT);//up
  pinMode(10,INPUT);//right
  pinMode(11,INPUT);//down
  pinMode(12,INPUT);//ok
  randomSeed(analogRead(0));  // Setup the LCD  
  myGLCD.InitLCD();  
  myGLCD.setFont(SmallFont); 
  
 //myGLCD.fillScr(0,106,78);
  //backgound_with_board();
  background();
  draw_snake();
  generate_food();
   for(int i = 0;i<5;i++)
   {
    highscore[i] =  EEPROM.read(i);
   }
 }
  
void loop() {
  //backgound_with_board();
  
     if(state == 0)
     {
       game_running();
     }
     else if(state == 1)
        {
       gameover_to_menu();
        gameover();
        delay(100);
        }
      else if(state == 2)
        {
        
       selection_menu();
       checkmenuposition();
       control_menu();
       delay(100);
        }
       else if(state == 3)
        {
       highscore_to_menu();
       Highscore();
       delay(100);
        } 
       else if(state == 4)
        {
       check_from_pause_to_selection_menu();
       check_from_pause_menuposition();
       pause_control_menu();
//       pause_menu(30,50);
       delay(100);
       }   
       
  }

     void Highscore()
   {
     background();

     myGLCD.setFont(BigFont);
     myGLCD.setBackColor(0,106,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("HighScore",CENTER,5);

     
     myGLCD.setBackColor(0,106,78);   
     myGLCD.setColor(255, 255, 255);
     myGLCD.printNumI(EEPROM.read(0),CENTER,32);
     
     myGLCD.setBackColor(0,106,78);   
     myGLCD.setColor(255, 255, 255);
     myGLCD.printNumI(EEPROM.read(1),CENTER,62);
     
     myGLCD.setBackColor(0,106,78);   
     myGLCD.setColor(255, 255, 255);
     myGLCD.printNumI(EEPROM.read(2),CENTER,92);
     
     myGLCD.setBackColor(0,106,78);   
     myGLCD.setColor(255, 255, 255);
     myGLCD.printNumI(EEPROM.read(3),CENTER,122);

     myGLCD.setBackColor(0,106,78);   
     myGLCD.setColor(255, 255, 255);
     myGLCD.printNumI(EEPROM.read(4),CENTER,152);

     myGLCD.setColor(45,45,78); 
     myGLCD.fillRect(80 ,180 ,239,210);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(255, 255, 255);
     myGLCD.print("Main Menu",CENTER,182);

      myGLCD.setBackColor(45,45,78);
      myGLCD.setColor(255, 255, 255);  
      myGLCD.drawRect(80, 180, 239, 210);
     
   }
  void highscore_to_menu()
    {
     if(digitalRead(12) == 1 && highscoremenuposition == 1)
     {
      if(comefrompausemenu == 1)
      {
        state = 4;
        comefrompausemenu = 0;
      }
      else
      state = 2;  
     }
    }


    
void checkmenuposition()
{
    if(digitalRead(11) == 1 && menuposition == 0)
        menuposition++ ;
    if(digitalRead(9) == 1 && menuposition == 1)
        menuposition --;  
}

void selection_menu()
{
   if(digitalRead(12) == 1 && menuposition == 0)
   {
        state = 0;
   }
   if(digitalRead(12) == 1 && menuposition == 1)
   {
        state = 3;
        highscoremenuposition = 1;
   }
   
}
void menu(int y1,int y2)
 {
     background();
     myGLCD.setFont(BigFont);
     myGLCD.setBackColor(0,106,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Menu",CENTER,5);
     //1
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 , 30 , 239 ,50);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("NewGame",CENTER,32);
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 ,70 ,239,90);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("HighScore",CENTER,72);
     /*
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 ,110 ,239,130);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Control",CENTER,112);
     */
     
      myGLCD.setBackColor(45,45,78);
      myGLCD.setColor(255, 255, 255);  
      myGLCD.drawRect(80, y1, 239, y2);//y1 = 30,y2 =50
 }

void control_menu()
{ 
  if(menuposition == 0)
    {
      Serial.println("0 menu");
       ypos1 = 30;
       ypos2 = 50;
       menu(ypos1,ypos2);
     //  menuupblock = 0;
    }
   if(menuposition == 1)
    {
      Serial.println("1 menu");
       ypos1 = 70;
       ypos2 = 90;
       menu(ypos1,ypos2);
      // menuupblock = 0;
    } 
} 



void check_from_pause_menuposition()
{
    if(digitalRead(11) == 1 && pausemenuposition != 2)
        pausemenuposition++ ;
    if(digitalRead(9) == 1 && pausemenuposition != 0)
        pausemenuposition --;  
}

void check_from_pause_to_selection_menu()
{
   if(digitalRead(12) == 1 && pausemenuposition == 0)
   {
        state = 0;
   }
   if(digitalRead(12) == 1 && pausemenuposition == 1)
   {
        snakesize = 5;
        snake_position = 1;
        snakesize = 5;
        point = 0;
        timer = 50;
        foodtype = 0;
        bonusfoodstate = 1;
        normal_food = 0;
        bonus_food = 0;
        draw_snake();
        state = 0;
   }
   if(digitalRead(12) == 1 && pausemenuposition == 2)
   {
        state = 3;
        highscoremenuposition = 1;
        comefrompausemenu = 1;
   }
   
}
void pause_menu(int y1,int y2)
 {
     background();
     myGLCD.setFont(BigFont);
     myGLCD.setBackColor(0,106,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Menu",CENTER,5);
     //1
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 , 30 , 239 ,50);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Continue",CENTER,32);
     
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 ,70 ,239,90);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("NewGame",CENTER,72);
     
     myGLCD.setColor(45,45,78);  
     myGLCD.fillRect(80 ,110 ,239,130);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("HighScore",CENTER,112);
       
      myGLCD.setBackColor(45,45,78);
      myGLCD.setColor(255, 255, 255);  
      myGLCD.drawRect(80, y1, 239, y2);//y1 = 30,y2 =50 starting block
 }

void pause_control_menu()
{ 
  if(pausemenuposition == 0)
    {
      Serial.println("0 menu");
       ypos1 = 30;
       ypos2 = 50;
       pause_menu(ypos1,ypos2);
     //  menuupblock = 0;
    }
   if(pausemenuposition == 1)
    {
      Serial.println("1 menu");
       ypos1 = 70;
       ypos2 = 90;
       pause_menu(ypos1,ypos2);
      // menuupblock = 0;
    } 
    if(pausemenuposition == 2)
    {
      Serial.println("1 menu");
       ypos1 = 110;
       ypos2 = 130;
       pause_menu(ypos1,ypos2);
      // menuupblock = 0;
    } 
} 








 // deactivate_and_wait();
void game_running()
{
 myGLCD.setFont(SmallFont); 
  int radius = 5;
    //Serial.println(snake_position);
  /*
  Serial.println(snake[0].x);
  Serial.print(",");
  Serial.println(snake[0].y);
    */
    if(digitalRead(12) == 1 && gamepauseposition == 0)
     {
        state = 4;
     }
    score_board();
    collition(); // must be after every position change means that every running the snake
    taking_input();
    running_the_snake();
 // 

//value = digitalRead(8);

if(snake_position == 0)
  snake[0].x = snake[0].x - test_speed; 
  
else if(snake_position == 1)
  snake[0].x = snake[0].x + test_speed;
  
else if(snake_position == 2)
  snake[0].y = snake[0].y + test_speed; 
   
else if(snake_position == 3)
  snake[0].y = snake[0].y - test_speed;  

  //delay(10);
  for(int i = 0;i<snakesize;i++)
  {
    
  myGLCD.setColor(244, 42, 65);  
  myGLCD.fillCircle(snake[i].x,snake[i].y,radius);
  }
  backgound_with_board();
  drawfood();
   delay(100);  
}
void draw_snake()
{
  // snakesize =5;
  int radius = 5;
  int snakeheadx = random(10,220);
  int snakeheady = random(40,210);
  snake[0].x = snakeheadx;
  snake[0].y = snakeheady;
  for(int i = 1;i<snakesize;i++)
  {
      snake[i].x = snake[i-1].x+radius + radius;
      snake[i].y = snake[i-1].y;  
  }
  
  for(int i = 0;i<snakesize;i++)
  {
  myGLCD.setColor(244, 42, 65);  
  myGLCD.fillCircle(snake[i].x,snake[i].y,radius);
  }
  
}
       
 void running_the_snake()
 {
   for(int i = snakesize-1;i>0;i--)
    snake[i] = snake[i-1];
    /*
   if(snake[0].x>=320)
     snake[0].x = 0;
   if(snake[0].x<0)
     snake[0].x = 319;  
   if(snake[0].y>=240)
     snake[0].y = 0; 
   if(snake[0].y<0)
     snake[0].y = 239;  */
 }   

    
 void taking_input()
 {
    if(digitalRead(8) == 1 && snake_position != 1)
        snake_position = 0;
    if(digitalRead(10) == 1 && snake_position != 0)
        snake_position = 1;
    if(digitalRead(11) == 1 && snake_position != 3)
        snake_position = 2;
    if(digitalRead(9) == 1 && snake_position != 2)
        snake_position = 3;
 }
 void collition()
 {
     if(snake[0].x>= food.x-10 && snake[0].x<= food.x+10 && snake[0].y>= food.y-10 && snake[0].y<= food.y+10)
     {
       generate_food();
       if(foodtype == 1)
       {
        if(timer>=40)
           point += 50;
        else if(timer>=30)
           point += 40;
        else if(timer>=20)
           point += 30;  
        else if(timer>=10)
           point += 20;    
        else if(timer>=0)
           point += 10;      
           
       timer = 50;
       bonus_food++;
       }
       else
       {
       point++;
       normal_food++;
       }
       snakesize++;
       score_board();
    }
   else
    {
      for(int i=3;i<snakesize;i++)
      {
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y && snakesize>5)
        {
             Serial.print("Game over");
             state = 1;
             for(int i = 4;i>0;i--)
             {
                int r = EEPROM.read(i-1);
                 EEPROM.write(i,r);
             }
             EEPROM.write(0,point);


             for(int i = 0;i<5;i++)
                {
                  Serial.println(EEPROM.read(i));
                }
                Serial.println();
        }
      }
    }

    if ((snake[0].x < 8) || (snake[0].y < 38) || (snake[0].x > 309) || (snake[0].y > 229)) 
    {
                     Serial.print("Game over");
             state = 1;
             for(int i = 4;i>0;i--)
             {
                int r = EEPROM.read(i-1);
                 EEPROM.write(i,r);
             }
             EEPROM.write(0,point);


             for(int i = 0;i<5;i++)
                {
                  Serial.println(EEPROM.read(i));
                }
                Serial.println();
     }
    /*
    if(foodtype == 1)
       {
          if(snake[0].x>= food.x-16 && snake[0].x<= food.x+16 && snake[0].y>= food.y-16 && snake[0].y<= food.y+16 ){
               generate_food();
               point += 5;
               snakesize++;
              
              // score_board();
               }
       }
       else if(foodtype == 0)
       {
          if(snake[0].x>= food.x-10 && snake[0].x<= food.x+10 && snake[0].y>= food.y-10 && snake[0].y<= food.y+10 ){
               generate_food();
               point ++;
              // timer = 50;
               snakesize++;
              // score_board();
               }
       }
      
       score_board();
       */
 }

 void drawfood()
 {
  if(snakesize == currentsnakestate + 1)
     bonusfoodstate = 1;
   if(snakesize%5==0 && snakesize>5 && bonusfoodstate == 1 )
    {
      myGLCD.setColor(244, 42, 65);  
      myGLCD.fillCircle(food.x,food.y,8);
      foodtype = 1;
      
     }
   else
    {
      myGLCD.setColor(244, 42, 65);  
      myGLCD.fillCircle(food.x,food.y,5);
      foodtype = 0;
     }  
  }


 void generate_food()
 {
     food.x = random(90,305);
     food.y = random(40,225);
     drawfood();
 }
 void background()
 {
     myGLCD.setColor(0,106,78);  
     myGLCD.fillRect(0 , 0 , 319 , 239);
 }
 void  backgound_with_board()
 {
     myGLCD.setColor(0,0,0);  
     myGLCD.fillRect(0 , 0 , 319 , 30);
     myGLCD.setColor(0,106,78);  
     myGLCD.fillRect(0 , 30 , 319 , 239);
     
     myGLCD.setBackColor(0,106,78);
     myGLCD.setColor(255, 255, 255);  

     int m=1,n=31,o=318,p=238;
     
     for(int i = 0;i<5;i++)
     {
        myGLCD.drawRect(m, n, o, p);
        if(i<3)
        {
        m++;
        n++;
        }
        o--;
        p--;
     }
     
 }
 void score_board()
 {
    // myGLCD.setColor(0, 0, 0);  
    // myGLCD.fillRect(0 , 0 , 319 , 30);
     myGLCD.setBackColor(0,0,0);
     
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Score:",2,10);
     myGLCD.printNumI(point , 50 , 10);
     
     myGLCD.setBackColor(0,0,0);
     myGLCD.print("Normal food:", 179, 2);
     myGLCD.printNumI(normal_food,279, 2);

     myGLCD.setBackColor(0,0,0);
     myGLCD.print("Bonus  food:", 179, 15);
     myGLCD.printNumI(bonus_food,279, 15);
     
     if(foodtype == 1)
     {
         myGLCD.setBackColor(0,0,0);
         myGLCD.print("Timer:", 70, 10);
         myGLCD.printNumI(timer,120, 10);
         timer --;        
         if(timer == 0)
         {
            foodtype = 0;
            bonusfoodstate = 0;
            currentsnakestate = snakesize;
            generate_food();
            timer = 50;    
         }
     }
         
 }

void gameover()
 {
     myGLCD.setColor(0,106,78);  
     myGLCD.fillRect(0 , 0 , 319 , 239);
     myGLCD.setFont(BigFont);
     myGLCD.setBackColor(0,106,78);  
     myGLCD.setColor(244, 244, 244);
     myGLCD.print("Game OVER",CENTER,95);
     myGLCD.print("Score:",95,120);
     myGLCD.printNumI(point,195,120);
     //delay(10000);

     myGLCD.setColor(45,45,78); 
     myGLCD.fillRect(80 ,180 ,239,210);
     myGLCD.setBackColor(45,45,78);  
     myGLCD.setColor(255, 255, 255);
     myGLCD.print("Main Menu",CENTER,182);

     myGLCD.setBackColor(45,45,78);
     myGLCD.setColor(255, 255, 255);  
     myGLCD.drawRect(80, 180, 239, 210);
 }

    void gameover_to_menu()
    {
     if(digitalRead(12) == 1 && gameovermenuposition == 0)
     {
        state = 2;
        snakesize = 5;
        draw_snake();
        snake_position = 1;
        snakesize = 5;
        point = 0;
        timer = 50;
        foodtype = 0;
        bonusfoodstate = 1;
        normal_food = 0;
        bonus_food = 0;
     }
    }

/*
void deactivate_and_wait(){
  // set Databus inactive to prevent latchup 
  //22 to 37  
  for (int i = 22; i<=37; i++)
       pinMode(i,INPUT_PULLUP);   
       delay(100000);
    for (int i = 22; i<=37; i++)
       pinMode(i,OUTPUT); 
       }
       */
