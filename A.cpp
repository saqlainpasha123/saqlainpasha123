#include <iostream>  //to be able to take input and output 
#include <cstdlib>   //includes library
#include <ctime>     //includes time 
#include <conio.h>   //includes _kbhit() and _getch()

using namespace std;  //namespace

const int rows = 21;   //rows in the game board
const int columns = 19; //columns in the game board

int pacManX, pacManY;  //position of Pac-Man
int ghostsX[3], ghostsY[3]; //positions of three ghosts
int fruitX, fruitY;  //position of the fruit
int score;  //player's score
int level = 1; //game level

enum Direction { UP, DOWN, LEFT, RIGHT };  //gives directions

char board[rows][columns];  //an array to represent the game board

// function to initiate the game
void initializeGame() {
pacManX = rows / 2;  // initiate  Pac-Man's X-coordinate
pacManY = columns / 2;  // Initiate Pac-Man's Y-coordinate

// initiate positions of three ghosts
for (int i = 0; i < 3; ++i) {
ghostsX[i] = rand() % rows;  // randomize ghost X-coordinate
ghostsY[i] = rand() % columns;  // randomize ghost Y-coordinate
}

// Initiate position of the fruit
fruitX = rand() % (rows - 2) + 1;  // randomize fruit X-coordinate
fruitY = rand() % (columns - 2) + 1;  // randomize fruit Y-coordinate
score = 0;  // starts score

// starts the game board
for (int i = 0; i < rows; ++i) {
for (int j = 0; j < columns; ++j) {
// border of the game board
if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
board[i][j] = '#';  // wall
} else {
 board[i][j] = ' ';  // makes empty space inside the border
}
}
}

board[pacManX][pacManY] = 'P';  // places pac-Man on the board
// places ghosts on the board
for (int i = 0; i < 3; ++i) {
board[ghostsX[i]][ghostsY[i]] = 'G';
}
board[fruitX][fruitY] = 'F';  // places fruit on the board

// creates horizontal barriers on the board
for (int i = 0; i < rows; i += 2) {
for (int j = 1; j < columns - 1; ++j) {
board[i][j] = '_';
}
}
}

//function to draw the game board
void drawBoard() {
system("cls");  // clear the console screen

// loops through each cell of the board
for (int i = 0; i < rows; ++i) {
for (int j = 0; j < columns; ++j) {
// Highlights Pac-Man with red color
if (i == pacManX && j == pacManY) {
cout << "\033[1;31m" << board[i][j] << "\033[0m ";
} else {
cout << board[i][j] << ' ';  // prints the content of the cell
}
}
cout << endl;  // moves to the next line for the new row
}

// display the score and level
cout << "Score: " << score << " | Level: " << level << endl;
}

// function to update the game state based on the player input
void updateGame(Direction direction) {
board[pacManX][pacManY] = ' ';  // clear pac-man current position

// update pac-man position based on the chosen direction
switch (direction) {
case UP:
pacManX--;
break;
case DOWN:
pacManX++;
break;
case LEFT:
pacManY--;
break;
case RIGHT:
pacManY++;
break;
}

// makes sure that pac-man stays within the boundaries of the board
pacManX = (pacManX + rows) % rows;
pacManY = (pacManY + columns) % columns;

// if pac-man reaches the position of the fruit, increase the score and respawn the fruit
if (pacManX == fruitX && pacManY == fruitY) {
score += 10;
fruitX = rand() % (rows - 2) + 1;
fruitY = rand() % (columns - 2) + 1;
}

// check if pac-man collides with any of the ghosts, ending the game
for (int i = 0; i < 3; ++i) {
if (pacManX == ghostsX[i] && pacManY == ghostsY[i]) {
cout << "Game Over! Your final score is: " << score << endl;
exit(0);
}
}

// pac-man goes around the board if it reaches the left or right edge
if (pacManY == 0) {
pacManY = columns - 2;
} else if (pacManY == columns - 1) {
pacManY = 1;
}

board[pacManX][pacManY] = 'P';  // update pac-man new position on the board
}

// this Function makes ghost move  randomly on the board
void moveGhosts() {
for (int i = 0; i < 3; ++i) {
// choose a random direction for each ghost
int ghostDirection = rand() % 4;
switch (ghostDirection) {
case UP:
ghostsX[i]--;
break;
case DOWN:
ghostsX[i]++;
break;
case LEFT:
ghostsY[i]--;
break;
case RIGHT:
ghostsY[i]++;
break;
}

// make sure ghosts stays within the boundaries of the board
ghostsX[i] = (ghostsX[i] + rows) % rows;
ghostsY[i] = (ghostsY[i] + columns) % columns;

board[ghostsX[i]][ghostsY[i]] = 'G';  // updates the ghosts  position on the board
}
}

// function to proceed to the next level
void nextLevel() {
level++;  // increase the game level
initializeGame();  //intiates the game for the new level
}
// starting function where the game loop runs
int main() {
srand(static_cast<unsigned>(time(0)));  // random number generation
initializeGame();  // initializes the game state

// Game loop
while (true) {
drawBoard();  // draws the current state of the game board

// checks for player input
if (_kbhit()) {
char key = _getch();  // gets  the pressed key
Direction direction;

// Determines  the direction based on the pressed key
switch (key) {
case 'w':
direction = UP;
break;
case 's':
direction = DOWN;
break;
case 'a':
direction = LEFT;
break;
case 'd':
direction = RIGHT;
break;
default:
;  // Skip to the next level if an invalid key is pressed
}

updateGame(direction);  // updates the game state based on player input
 }

 moveGhosts();  // move the ghosts randomly on the board

// check if the player has reached the score required for the next level
if (score >= level * 50) {
nextLevel();  // proceeds to the next level
}
}

return 0;  // thank you for reading this code 
}
