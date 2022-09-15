from json.encoder import INFINITY
from queue import Empty



def run_game(surface, menu, ttt):
    reset_game(surface, menu, ttt)
    while True:
        is_user = True
        if ttt.turn == computer:
            is_user = False
            ttt.play_computer()

        for event in pygame.event.get():
            if event.type == QUIT:
                terminate()
            elif event.type == MOUSEBUTTONUP:
                if is_user:
                    if not ttt.check_board(event.pos):
                        if menu.check_rect(event.pos):
                            reset_game(surface, menu, ttt)
            
        if ttt.check_gameover():
            return
        pygame.display.update()
        fps_clock.tick(fps)

def reset_game(surface, menu, ttt):
    surface.fill(white)
    menu.draw_menu()
    ttt.init_game()

def set_frist_player(self):
    self.turn = random.choice([computer, user])
    if self.turn == computer:
        x = random.choice([0,1,2])
        y = random.choice([0,1,2])
        self.draw_shape(x,y)

def set_coordds(self):
    for i in range(3):
        for j in range(3):
            coord = left + j * box_size, top +i * box_size
            self.coords.append(coord)

def get_coord(self, pos):
    for coord in self.coords:
        x,y = coord
        rect = pygame.Rect(x,y, box_size, box_size)
        if(rect.collidepoint(pos)):
            return coord
    return None

def get_board(self, coord):
    x, y = coord
    x = (x - left)
    y = (y - top)
    return x, y

def play_computer(self):
    self.ai.minimax(0, -INFINITY, INFINITY, computer)
    x,y = self.ai.get_best_coord()
    self.draw_shape(x,y)

def check_board(self,pos):
    coord = self.get_coord(pos)
    if not coord:
        return False
    x,y = self.get_board(coord)
    if self.board[y][x] != empty:
        return True
    else:
        return self.draw_shape(x,y)

def draw_shape(self, x, y):
    self.board[y][x] = self.turn

    if self.ai.is_win(self.turn, self.board):
        self.finish = True
        self.menu.show_msg(self.turn)
    x,y = self.get_pixel_coord(x,y)
    if self.turn == computer:
        self.draw_x(x,y)
        self.turn = User
    else:
        self.draw_o(x,y)
        self.turn = computer
    return True
def check_gameover(self):
    if self.ai.is_full(self.board):
        if not self.finish:
            self.menu.show_msg('tie')
        self.finish = Ture
    return self.finish
def is_finish(self):
    return(self.is_full(self.board)or
           self.is_win(computer, self.board)or
           self.is_win(user, self.board))
def get_coords(self):
    coords = []
    for y in range(3):
        if self.board[y][x] == empty:
            coords.append((x,y))
    return coords
def evaluate(self):
    if self.is_win(computer, self.board):
        return 1
    elif self.is_win(user, self.board):
        return -1
    else:
        return 0
def get_best_coord(self):
    score = -100
    best_coord = None
    for best in self.at_score:
        if best[0] > score:
            score = best[0]
            best_coord = best[1]
    self.at_score.clear()
    return best_coord
def fill_board(self, coord, player):
    x,y = coord
    self.board[y][x] = player
def minimax(self,depth, alpha, beta, player):
    if alpha >= beta:
        if player == computer:
            return INFINITY
        else:
            return -INFINITY
    if self.is_finish():
            return self.evaluate()
    coords = self.get_coords()
    max_score  = -INFINITY
    min_score = INFINITY
    for coord in coords:
        if player == computer:
            self.fill_board(coord,computer)
            score = self.minimax(depth +1, alpha, beta, user)
            max_score = max(score,max_score)
            alpha = max(max_score, alpha)

            if depth == 0:
                self.at_score.append((max_score,coord))
        else:
            self.fill_board(coord,user)
            score = self.minimax(depth+1, alpha, beta, computer)
            min_score = min(score, min_score)
            beta = min(min_score,beta)

        self.board[coord[1]][coord[0]] = Empty
        if score == INFINITY or score == -INFINITY:
            break
    if player == computer:
        return max_score
    else: 
        return min_score