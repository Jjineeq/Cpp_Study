import numpy as np
import queue

global N
N=3

def attacked_queens_pairs(seqs): 
    a = np.array([0] * N**2)  
    a = a.reshape(N, N)  
    n = 0  

    for i in range(1, N):
        if seqs[i-1] != 0:
            a[seqs[i - 1]][i] = 1  

    for i in range(1, N):
        if seqs[i - 1] == 0:
            continue
        for k in list(range(1, i)) + list(range(i + 1, N)): 
            if a[seqs[i - 1]][k] == 1:  
                n += 1
        t1 = t2 = seqs[i - 1]
        for j in range(i - 1, 0, -1):  
            if t1 != 1:
                t1 -= 1
                if a[t1][j] == 1:
                    n += 1 

            if t2 != N-1:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  

        t1 = t2 = seqs[i - 1]
        for j in range(i + 1, N):  
            if t1 != 1:
                 t1 -= 1
                 if a[t1][j] == 1:
                     n += 1 

            if t2 != n-1:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  
    return int(n/2)  

def display_board(seqs):
    board = np.array([0] * N**2) 
    board = board.reshape(N, N) 
    for i in range(1,N):
        board[seqs[i - 1]][i] = 1  
    print('The corresponding chessboard is as follows:')
    for i in board[1:]:
        for j in i[1:]:
            print(j, ' ', end="") 
        print()  
    print('The number of queens to attack is' + str(attacked_queens_pairs(seqs)))

open_queue = queue.PriorityQueue()
open_queue.put(attacked_queens_pairs, display_board)

closed_queue = []
