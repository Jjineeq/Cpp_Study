from gettext import install
import random
import time
import numpy as np

def attacked_queens_pairs(seqs):
    """
    Calculate the queen logarithm of the attack on the chessboard corresponding to the sequence n]
    We only need to check whether there are other queens on the eight queens of the current chessboard in their respective rows and two diagonals, without judging whether there are other queens in the same column
    """
    a = np.array([0] * 81)  # Create a one-dimensional array with 81 zeros
    a = a.reshape(9, 9)  # Change to 9 * 9 two-dimensional array. For the convenience of later use, only the 8 * 8 parts of the last eight rows and columns are used as a blank chessboard
    n = 0  # The number of queens attacking each other is initialized to 0

    for i in range(1, 9):
        if seqs[i-1] != 0: # An element of seqs is 0, which means that no queen should be placed in the corresponding chessboard column
            a[seqs[i - 1]][i] = 1  # Generate the corresponding chessboard sequence, and place it in the order of the first chessboard column

    for i in range(1, 9):
        if seqs[i - 1] == 0:
            continue # If an element of seqs is 0, it represents the corresponding chessboard. If no queen is placed in this column, the next column will be judged directly
        for k in list(range(1, i)) + list(range(i + 1, 9)):  # Check whether there are other queens on each queen's line
            if a[seqs[i - 1]][k] == 1:  # There are other queens
                n += 1
        t1 = t2 = seqs[i - 1]
        for j in range(i - 1, 0, -1):  # Look at the two diagonals in the left half
            if t1 != 1:
                t1 -= 1
                if a[t1][j] == 1:
                    n += 1  # There are other queens on the left half of the diagonal

            if t2 != 8:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  # There are other queens on the left half of the sub diagonal

        t1 = t2 = seqs[i - 1]
        for j in range(i + 1, 9):  # Look at the two diagonals in the right half
            if t1 != 1:
                t1 -= 1
                if a[t1][j] == 1:
                    n += 1  # There are other queens on the right half of the diagonal

            if t2 != 8:
                t2 += 1
                if a[t2][j] == 1:
                    n += 1  # There are other queens on the right half of the sub diagonal
    return int(n/2)  # Returns n/2, because A attacking B also means B attacking A, so returns half of n

def display_board(seqs):
    """
     Displays the chessboard corresponding to the sequence
    """
    board = np.array([0] * 81)  # Create a one-dimensional array with 81 zeros
    board = board.reshape(9, 9)  # Change to a 9 * 9 two-dimensional array. For the convenience of later use, only the 8 * 8 parts of the last eight rows and columns are used as a blank chessboard

    for i in range(1, 9):
        board[seqs[i - 1]][i] = 1  # According to the sequence, from the first column to the last column, put a queen in the corresponding position to generate the chessboard corresponding to the current sequence
    print('The corresponding chessboard is as follows:')
    for i in board[1:]:
        for j in i[1:]:
            print(j, ' ', end="")  # With end, print doesn't wrap
        print()  # After outputting one line, wrap it. This cannot be print('\n'), otherwise it will be replaced by two lines
    print('The number of queens to attack is' + str(attacked_queens_pairs(seqs)))

start = time.time()
frontier_priority_queue = [{'unplaced_queens':8, 'pairs':28, 'seqs':[0] * 8}] # The initial state is 8 zeros, which means that there are no queens on the chessboard; g(n) = the number of queens that have not been placed well, h(n) = the logarithm of queens attacking each other, and h(n)=28, g(n)=8
solution = []
flag = 0 # The representative has not found a solution

while frontier_priority_queue: # If the frontier is not empty, the loop will continue. If the solution is found successfully, the loop will output the solution. If the frontier is empty, the loop will fail
    first = frontier_priority_queue.pop(0)  # Since frontier s are sorted every time, the first sequence is extended
    if first['pairs'] == 0 and first['unplaced_queens'] == 0: # Do the goal test before extending the node: if the sequence h(n)=g(n)=0, then the sequence is the solution sequence
        solution = first['seqs']
        flag = 1  # success
        break
    nums = list(range(1, 9))  # List with elements 1-8
    seqs = first['seqs']
    if seqs.count(0) == 0: # Due to the sorting mechanism in the following code, the node that [8 queens have been placed, i.e. g(n)=0, but the number of queens attacking each other is close to 0, but not 0, i.e. h(n)!=0] may be placed in the first place; and this kind of node certainly does not meet the requirements, but such a node cannot be expanded, because the 8 queens have been placed
        continue # You can only skip this kind of node
    for j in range(8): # In the first position of 0 in the sequence, that is, the leftmost column without queen, select a row to place queen
        pos = seqs.index(0)
        temp_seqs = list(seqs)
        temp = random.choice(nums)  # Select a random row in the column to place the queen
        temp_seqs[pos] = temp # Place the queen on line temp of the column
        nums.remove(temp)  # Remove generated values from nums
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