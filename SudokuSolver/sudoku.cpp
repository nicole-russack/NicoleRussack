#include "sudoku.h"
#include <iostream>

using namespace std;

Sudoku::Sudoku(int puzzle[9][9]) {
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      board[i][j] = puzzle[i][j];
    }
  }
}

Sudoku::~Sudoku() {
}

void Sudoku::verify() {
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      if(!isValid(i, j)) {
        cout << "INVALID PUZZLE" << endl;
        return;
      }
    }
  }
  cout << "VALID PUZZLE" << endl;
}

void Sudoku::print() {
  for (int row=0; row<9; row++) {
      if (row % 3== 0) {
      std::cout << "-------------------------------" << std::endl;
    }
    
    for (int col=0; col<9; col++) {
      if (col % 3 == 0) {
        std::cout << "|";
      }
    
        if (board[row][col] != 0) {
        std::cout << " " << board[row][col] << " ";
      } else {
        std::cout << " . ";
      }
      
    }
    
    std::cout << "|" << std::endl;
  }
  std::cout << "-------------------------------" << std::endl;
}

bool Sudoku::isValid(int row, int col) {


  int value = board[row][col];

  for (int i=0; i<9; i++) {
    if (i == row) {
    continue;
    }
    
    int temp = board[i][col];
    if (temp == value) {
      return false;
    }
  }
  
  for (int i=0; i<9; i++) {
      if (i == col) {
      continue;
    }
    
    int temp = board[row][i];
    if (temp == value) {
      return false;
    }
  }
  
  int box_row = row / 3; 
  int box_col = col / 3; 
  
  for (int i=box_row * 3; i < box_row * 3 + 3; i++) {
    for (int j=box_col * 3; j < box_col * 3 + 3; j++) {
      if (i == row && j == col) {
        continue;
      }
      
      int temp = board[i][j];
      if (temp == value) {
        return false;
      }
    }
  }
  
  return true;
}

void Sudoku::solve(){
  solveHelper(0, 0, false);
  return;
}


bool Sudoku::solveHelper(int row, int col, bool inProgress) {
  // if the number is alreay placed, do not need to solve


  //code for end base case 
  if(row == 8 && col == 8){
    //used all and does not work return false
    if(board[row][col] == 10){
        board[row][col] = 0;
        return false;
    }
    //end case, board is done
    else if(row == 8 && col == 8 && isValid(row, col) && board[row][col] != 0){
      //print();
      return true;
    }
    //this value was set and we are not alowed to change it 
    else if(board[row][col] != 0 && !inProgress){
      return false;
    }

    //increase it and see if it works 
    else{
      board[row][col] += 1;
      return solveHelper(row, col, true);
    }
  }


  //not last row
  //solveHelper() will ive if next argument is valid or not `

  //if does not work for any value return false
  else{
  if(board[row][col] == 10){
        board[row][col] = 0;
        return false;
  }
  //if the number is valid + works for rest will return true  
  if(isValid(row, col)){
    if(col == 8){
    if(solveHelper(row + 1, 0, false)){
      return true;
    }
    }
    else{
    if(solveHelper(row, col + 1, false)){
      return true;
    }
    }
  }

  //something is wrong with the number 
  //can we change it
  //if we cannot change it return false

if(board[row][col] != 0 && !inProgress){
      return false;
}

//if we can change it use the next number and try again in that location
else{
      board[row][col] += 1;
      return solveHelper(row, col, true);
}
  }
}


