// TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);

// Generates move for computerWon
// params: 1.Board as an array 2.reference to the row - int
// 3.reference to column - int
void generateComputerMove(string b[][SIZE], int &row, int &col);

int main() {
  // construct board
  string board[SIZE][SIZE];
  int position_id = 1;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      board[i][j] = to_string(position_id);
      /*  stringstream ss;
        ss << position_id;
        board[i][j] = ss.str();
        */ position_id++;
    }
  }

  // Initial game output
  cout << "Welcome to Tic-Tac-Toe" << endl;

  bool userTurn = userFirst();
  if (userTurn == true) {
    cout << "Player goes first!" << endl;
  } else {
    cout << "Computer goes first!" << endl;
  }

  // Loop for turn taking in game
  int positionsRemaining = SIZE * SIZE;
  bool userWon = false;
  bool computerWon = false;

  while ((positionsRemaining > 0) && (!userWon) && (!computerWon)) {
    displayBoard(board);

    // User's turn
    if (userTurn) {
      bool validMove = false;
      while (!validMove) {
        int position_id;
        cout << "Enter a position: ";
        cin >> position_id;
        if ((position_id <= (SIZE * SIZE)) && (position_id > 0)) {
          int row = (position_id - 1) / SIZE;
          int col = (position_id - 1) % SIZE;
          // cout << "row = " << row << " col = " << col << endl;
          if ((board[row][col] != "X") && (board[row][col] != "O")) {
            board[row][col] = "X";
            validMove = true;
          } else {
            cout << "Position already used. Try again." << endl;
          }

        } else {
          cout << "Position invalid. Try again." << endl;
        }
      }
      positionsRemaining--;
      userWon = currentPlayerWon(board, "X");
      userTurn = false;
    }

    // Computer's turn
    else {
      int row, col;
      generateComputerMove(board, row, col);
      board[row][col] = "O";
      positionsRemaining--;
      computerWon = currentPlayerWon(board, "O");
      userTurn = true;
    }
  }

  // Display game result
  displayBoard(board);
  if (userWon) {
    cout << "Congratulations! You have won!" << endl;
  } else if (computerWon) {
    cout << "The computer has won. Try again." << endl;
  } else {
    cout << "Out of moves. Try again." << endl;
  }
  return 0;
}

void displayBoard(string b[][SIZE]) {
  cout << "Tic-tac-toe board:" << endl << endl;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      cout << b[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
}

bool userFirst() {
  // set seed for random number generation
  srand(time(NULL));

  // generate a random number
  // 0 for computer
  // 1 for user
  int num = rand() % 2;
  if (num == 0) {
    return false;
  }
  return true;
}

// Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol) {
  // Horizontal case
  // Loop through each row
  for (int i = 0; i < SIZE; i++) {
    bool rowWinDetected = true;
    // Check all positions in row and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] != symbol) {
        rowWinDetected = false;
      }
    }
    if (rowWinDetected) {
      return true;
    }
  }

  // Vertical case
  // Loop through each column
  for (int i = 0; i < SIZE; i++) {
    bool colWinDetected = true;
    // Check all positions in column and see if they are the same symbol
    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] != symbol) {
        colWinDetected = false;
      }
    }
    if (colWinDetected) {
      return true;
    }
  }

  // Diagonal case #1
  bool diagonal1WinDetected = true;
  for (int i = 0; i < SIZE; i++) {
    if (b[i][i] != symbol) {
      diagonal1WinDetected = false;
    }
  }
  if (diagonal1WinDetected) {
    return true;
  }

  // Diagonal case #2
  bool diagonal2WinDetected = true;
  for (int i = 0; i < SIZE; i++) {
    if (b[(SIZE - 1) - i][i] != symbol) {
      diagonal2WinDetected = false;
    }
  }
  if (diagonal2WinDetected) {
    return true;
  }

  // otherwise win not diagonal2WinDetected
  return false;
}

// Generates move for computerWon
// params: 1.Board as an array 2.reference to the row - int
// 3.reference to column - int
void generateComputerMove(string b[][SIZE], int &row, int &col) {
  int emptyLocation = 0;
  int numOfXs = 0;
  int numOfOs = 0;
  int numOfSpaces = 0;

  // First Checks for a place it could win

  // Horizontal case
  for (int i = 0; i < SIZE; i++) {
    numOfXs = 0;
    numOfOs = 0;
    numOfSpaces = 0;
    // Check all positions in row and count X's, O's and spaces
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] == "X") {
        numOfXs++;
      } else if (b[i][j] == "O") {
        numOfOs++;
      } else {
        // empty spot
        numOfSpaces++;
        emptyLocation = j;
      }
    }
    // if you have the chance to win then place in correct empty Spot
    if (numOfOs == 2 && numOfSpaces == 1) {
      row = i;
      col = emptyLocation;
      return;
    }
  }

  // Verical case
  for (int i = 0; i < SIZE; i++) {
    numOfXs = 0;
    numOfOs = 0;
    numOfSpaces = 0;
    // Check all positions in row and count X's, O's and spaces
    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] == "X") {
        numOfXs++;
      } else if (b[j][i] == "O") {
        numOfOs++;
      } else {
        numOfSpaces++;
        emptyLocation = j;
      }
    }
    // if you have the chance to win then place in correct empty Spot
    if (numOfOs == 2 && numOfSpaces == 1) {
      row = emptyLocation;
      col = i;
      return;
    }
  }

  // Diagonal case #1
  numOfXs = 0;
  numOfOs = 0;
  numOfSpaces = 0;

  for (int i = 0; i < SIZE; i++) {
    if (b[i][i] == "X") {
      numOfXs++;
    } else if (b[i][i] == "O") {
      numOfOs++;
    } else {
      numOfSpaces++;
      emptyLocation = i;
    }
  }
  // if you have the chance to win then place in correct empty Spot
  if (numOfOs == 2 && numOfSpaces == 1) {
    row = emptyLocation;
    col = emptyLocation;
    return;
  }

  // Diagonal case #2
  numOfXs = 0;
  numOfOs = 0;
  numOfSpaces = 0;

  for (int i = 0; i < SIZE; i++) {
    if (b[(SIZE - 1) - i][i] == "X") {
      numOfXs++;
    } else if (b[(SIZE - 1) - i][i] == "O") {
      numOfOs++;
    } else {
      numOfSpaces++;
      emptyLocation = i;
    }
  }
  // if you have the chance to win then place in correct empty Spot
  if (numOfOs == 2 && numOfSpaces == 1) {
    row = (SIZE - 1) - emptyLocation;
    col = emptyLocation;
    return;
  }

  // Blocks User if they are about to win

  numOfXs = 0;
  numOfOs = 0;
  numOfSpaces = 0;

  // Horizontal case
  for (int i = 0; i < SIZE; i++) {
    numOfXs = 0;
    numOfOs = 0;
    numOfSpaces = 0;
    for (int j = 0; j < SIZE; j++) {
      if (b[i][j] == "X") {
        numOfXs++;
      } else if (b[i][j] == "O") {
        numOfOs++;
      } else {
        numOfSpaces++;
        emptyLocation = j;
      }
    }
    // if user has the chance to win then block it --X
    if (numOfXs == 2 && numOfSpaces == 1) {
      row = i;
      col = emptyLocation;
      return;
    }
  }

  // Verical case
  for (int i = 0; i < SIZE; i++) {
    numOfXs = 0;
    numOfOs = 0;
    numOfSpaces = 0;

    for (int j = 0; j < SIZE; j++) {
      if (b[j][i] == "X") {
        numOfXs++;
      } else if (b[j][i] == "O") {
        numOfOs++;
      } else {
        numOfSpaces++;
        emptyLocation = j;
      }
    }
    if (numOfXs == 2 && numOfSpaces == 1) {
      row = emptyLocation;
      col = i;
      return;
    }
  }

  // Diagonal case #1
  numOfXs = 0;
  numOfOs = 0;
  numOfSpaces = 0;

  for (int i = 0; i < SIZE; i++) {
    if (b[i][i] == "X") {
      numOfXs++;
    } else if (b[i][i] == "O") {
      numOfOs++;
    } else {
      numOfSpaces++;
      emptyLocation = i;
    }
  }
  if (numOfXs == 2 && numOfSpaces == 1) {
    row = emptyLocation;
    col = emptyLocation;
    return;
  }

  // Diagonal case #2
  numOfXs = 0;
  numOfOs = 0;
  numOfSpaces = 0;

  for (int i = 0; i < SIZE; i++) {
    if (b[(SIZE - 1) - i][i] == "X") {
      numOfXs++;
    } else if (b[(SIZE - 1) - i][i] == "O") {
      numOfOs++;
    } else {
      numOfSpaces++;
      emptyLocation = i;
    }
  }
  if (numOfXs == 2 && numOfSpaces == 1) {
    row = (SIZE - 1) - emptyLocation;
    col = emptyLocation;
    return;
  }

  // random move if conditions above aren't met
  bool validMove = false;
  while (!validMove) {
    row = rand() % SIZE;
    col = rand() % SIZE;
    if ((b[row][col] != "X") && (b[row][col] != "O")) {
      // b[row][col] = "O";
      validMove = true;
    }
  }
}
