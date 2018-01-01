#include "graph.h"
#include <libfdr/jrb.h>
#include <libfdr/jval.h>


typedef struct Board
{
	int **state; // this is 2 dimenstions array for storing a board;
	int xB;
	int yB;
	int collection; //open or close
}


Board newBoard()
{
	board.state = (int **)malloc(sizeof(int*) * 9);
	int i;
	for(i = 0; i < 9 ; i++)
	{
		board.state[i] = (int *)malloc(sizeof(int) * 9);
	}
	board.collection = 0;
}

Board copyBoard(Board board)
{
	int i;
	int j;
	Board newBoard = newBoard();
	newBoard.collection = board.collection;
	newBoard.xB	 = board.xB;
	newBoard.yB = board.yB;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j< 9; j++)
		{
			newBoard[i][j] = board[i][j];
		}
	}
	return newBoard;
}


void printBoard(Board board)
{
	int i;
	int j;
	for(i = 0; i< 9; i++)
	{
		for(j = 0; j< 9; j++)
		{
			printf("%d \t", board.state[i][j]);
		}
		printf("-");
	}
}

void printBoardPretty(Board board);
{
	int i;
	int j;
	for(i = 0; i < 9; i++){
		for(j = 0; j< 9; j++)
		{
			printf("%d \t", board.state[i][j]);
		}
		printf("\n");
	}
}


int getValue(Board board, int i, int j)
{
	return board.state[i][j];
}


int **getState(Board board)
{
	return board.state;
}


void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


Board nextStageRight(Board board)
{
	if(board.xB == 2)return NULL;
	Board newBoard = copyBoard(board);
	swap(&board[xB][yB], &board[xB + 1][yB]);

}
