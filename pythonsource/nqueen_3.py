import queue



class NQueens:

    def __init__(self, size):
        self.size = size

    def solve_astar(self): # f(n)
        global queue # 전역변수를 지역변수로
        if self.size < 1:
            return []
        solutions = []
        queue = queue.PriorityQueue()
        queue.put([])
        while not queue.empty(): # expand
            solution = queue.get()
            if self.conflict(solution):
                continue
            row = len(solution)
            if row == self.size:
                solutions.append(solution)
                continue
            for col in range(self.size):
                queen = (row, col)
                queens = solution.copy()
                queens.append(queen)
                queue.put(queens)
        return solutions

    def conflict(self, queens): #h(n), 서로 공격 가능한 퀸의 개수
        count = 0
        for i in range(1, len(queens)):
            for j in range(0, i):
                a, b = queens[i]
                c, d = queens[j]
                if a == c or b == d or abs(a - c) == abs(b - d):
                    count = count + 1
                    return True
        return False

    def print(self, queens):
        for i in range(self.size):
            print(' ---' * self.size)
            for j in range(self.size):
                p = 'Q' if (i, j) in queens else ' '
                print('| %s ' % p, end='')
            print('|')
        print(' ---' * self.size)


    def f(self):
        return self.h() + self.g()

    def h(self):
        return self.count

    def g(self):
        return self.solutions

    def __it__(self,other):
        return self.f() < other.g()

    def __gt__(self, other):
        return self.f() < other.f()

    def __eq__(self, other):
        return self.queen == other.queen

def main():
    print('.: 2018312031_Seongho_Jang N-Queens Problem :.')
    size = int(input('Please enter the size of board: '))
    print_solutions = input('Do you want the solutions to be printed (Y/N): ').lower() == 'y'
    n_queens = NQueens(size)
    astar_solutions = n_queens.solve_astar()
    if print_solutions:
        for i, solution in enumerate(astar_solutions):
            print('A* Solution %d:' % (i + 1))
            n_queens.print(solution)
    print('Total A* solutions: %d' % len(astar_solutions))



if __name__ == '__main__':
    main()