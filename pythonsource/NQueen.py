global N
N = 4
import random
n = int(input())
POPULATION_SIZE = n			# 개체 집단의 크기
MUTATION_RATE = 0.1			# 돌연 변이 확률
SIZE = n				# 하나의 염색체에서 유전자 개수		
 
def printSolution(board):
    for i in range(N):
        for j in range(N):
            print (board[i][j],end=' ')
        print()
 
def isSafe(board, row, col):
 
    # Check this row on left side
    for i in range(col):
        if board[row][i] == 1:
            return False
 
    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
 
    # Check lower diagonal on left side
    for i, j in zip(range(row, N, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
 
    return True
 
def solveNQUtil(board, col):
    if col >= N:
        return True
    for i in range(N):
 
        if isSafe(board, i, col):
            board[i][col] = 1
 
            if solveNQUtil(board, col + 1) == True:
                return True
 
            board[i][col] = 0
 
    return False
 
def solveNQ():
    board = [ [0, 0, 0, 0],
              [0, 0, 0, 0],
              [0, 0, 0, 0],
              [0, 0, 0, 0]
             ]
 
    if solveNQUtil(board, 0) == False:
        print ("Solution does not exist")
        return False
 
    printSolution(board)
    return True

solveNQ()