from gettext import install
import random
import time
import numpy as np

def attacked_queens_pairs(seqs):
    a = np.array([0] * 81)      
    a = a.reshape(9, 9)      
    n = 0  
    for i in range(1, 9):
        if seqs[i-1] != 0: 
            a[seqs[i - 1]][i] = 1  

    for i in range(1, 9):
        if seqs[i - 1] == 0:
            continue 
        for k in list(range(1, i)) + list(range(i + 1, 9)):  
            if a[seqs[i - 1]][k] == 1: 
                n += 1
        t1 = t2 = seqs[i - 1]
        for j in range(i - 1, 0, -1):  
            if t1 != 1:
                t1 -= 1
                if a[t1][j] == 1:
                    n += 1  

            if t2 != 8:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  

        t1 = t2 = seqs[i - 1]
        for j in range(i + 1, 9):  
            if t1 != 1:
                t1 -= 1
                if a[t1][j] == 1:
                    n += 1  

            if t2 != 8:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  
    return int(n/2)  

def display_board(seqs):
    board = np.array([0] * 81)  
    board = board.reshape(9, 9)  

    for i in range(1, 9):
        board[seqs[i - 1]][i] = 1  
    print('The corresponding chessboard is as follows:')
    for i in board[1:]:
        for j in i[1:]:
            print(j, ' ', end="")  
        print()  
    print('The number of queens to attack is' + str(attacked_queens_pairs(seqs)))

start = time.time()
frontier_priority_queue = [{'unplaced_queens':8, 'pairs':28, 'seqs':[0] * 8}] 
solution = []
flag = 0 

while frontier_priority_queue: 
    first = frontier_priority_queue.pop(0)  
    if first['pairs'] == 0 and first['unplaced_queens'] == 0: 
        solution = first['seqs']
        flag = 1  
        break
    nums = list(range(1, 9))  
    seqs = first['seqs']
    if seqs.count(0) == 0: 
        continue     
    for j in range(8):         
        pos = seqs.index(0)
        temp_seqs = list(seqs)
        temp = random.choice(nums)          
        temp_seqs[pos] = temp         
        nums.remove(temp)          
        frontier_priority_queue.append({'unplaced_queens':temp_seqs.count(0), 'pairs':attacked_queens_pairs(temp_seqs),'seqs':temp_seqs})
    frontier_priority_queue = sorted(frontier_priority_queue, key=lambda x:(x['pairs']+x['unplaced_queens']))

if solution:
    print('Solution sequence found:' + str(solution))
    display_board(solution)
else:
    print('Algorithm failed, no solution found')

end = time.time()
print('Time' + str('%.2f' % (end-start)) + 's')

solution