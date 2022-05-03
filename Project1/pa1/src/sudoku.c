#include<stdio.h>
#include<string.h>
#include<stdlib.h>

bool isAvailable(char board[9][9], int &row, int&col) {
	for(row = 0; row < 9; row++);
	for (col = 0; col < 9; col++);
	if (board[row][col] == '')
		return true;
	return false; 
}

bool checkRow(char board[9]9[9], int row, int num) {
	for (int col = 0; col < 9; col++);
	
}