#include "../../include/MultiplayerGame.h"

// Player类实现
Player::Player(char head, char body, string playerName) {
    headSymbol = head;
    bodySymbol = body;
    name = playerName;
    score = 0;
    highScore = 0;
    nTail = 0;
    dir = PLAYER_STOP;
    isAlive = true;
}

void Player::reset(int startX, int startY) {
    x = startX;
    y = startY;
    nTail = 0;
    score = 0;
    dir = PLAYER_STOP;
    isAlive = true;
}

// ScoreBoard类实现
ScoreBoard::ScoreBoard() {
    player1Score = 0;
    player2Score = 0;
    player1HighScore = 0;
    player2HighScore = 0;
}

void ScoreBoard::updateScore(int player, int score) {
    if (player == 1) {
        player1Score = score;
        if (score > player1HighScore) {
            player1HighScore = score;
        }
    } else if (player == 2) {
        player2Score = score;
        if (score > player2HighScore) {
            player2HighScore = score;
        }
    }
}

void ScoreBoard::updateHighScore(int player, int score) {
    if (player == 1 && score > player1HighScore) {
        player1HighScore = score;
    } else if (player == 2 && score > player2HighScore) {
        player2HighScore = score;
    }
}

void ScoreBoard::draw(int width, int height) {
    // 在右侧显示分数面板
    int panelX = width + 5;
    
    // 绘制面板边框
    COORD coord;
    coord.X = panelX;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    cout << "╔══════════════════╗" << endl;
    
    coord.Y = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║    分数面板      ║" << endl;
    
    coord.Y = 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y = 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ 玩家1 (绿色):    ║" << endl;
    
    coord.Y = 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║   分数: " << player1Score << "        ║" << endl;
    
    coord.Y = 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║   最高: " << player1HighScore << "        ║" << endl;
    
    coord.Y = 6;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y = 7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ 玩家2 (蓝色):    ║" << endl;
    
    coord.Y = 8;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║   分数: " << player2Score << "        ║" << endl;
    
    coord.Y = 9;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║   最高: " << player2HighScore << "        ║" << endl;
    
    coord.Y = 10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╚══════════════════╝" << endl;
}

void ScoreBoard::reset() {
    player1Score = 0;
    player2Score = 0;
}

// GameController类实现
GameController::GameController() {
    currentState = GAME_MENU;
    isRunning = false;
}

void GameController::startGame() {
    currentState = GAME_PLAYING;
    isRunning = true;
}

void GameController::pauseGame() {
    if (currentState == GAME_PLAYING) {
        currentState = GAME_PAUSED;
    }
}

void GameController::resumeGame() {
    if (currentState == GAME_PAUSED) {
        currentState = GAME_PLAYING;
    }
}

void GameController::restartGame() {
    currentState = GAME_PLAYING;
    isRunning = true;
}

void GameController::endGame() {
    currentState = GAME_OVER;
    isRunning = false;
}

GameState GameController::getState() const {
    return currentState;
}

bool GameController::getIsRunning() const {
    return isRunning;
}

void GameController::drawControls(int width) {
    int panelX = width + 5;
    COORD coord;
    coord.X = panelX;
    coord.Y = 12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    cout << "╔══════════════════╗" << endl;
    
    coord.Y = 13;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║    游戏控制      ║" << endl;
    
    coord.Y = 14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y = 15;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ P1: WASD 移动    ║" << endl;
    
    coord.Y = 16;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ P2: 方向键 移动  ║" << endl;
    
    coord.Y = 17;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y = 18;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ SPACE: 暂停/继续 ║" << endl;
    
    coord.Y = 19;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ R: 重新开始      ║" << endl;
    
    coord.Y = 20;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ ESC: 退出游戏    ║" << endl;
    
    coord.Y = 21;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╚══════════════════╝" << endl;
}

// CollisionDetector类实现
CollisionType CollisionDetector::checkWallCollision(int x, int y, int width, int height) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return COLLISION_WALL;
    }
    return COLLISION_NONE;
}

CollisionType CollisionDetector::checkSelfCollision(int x, int y, int tailX[], int tailY[], int nTail) {
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            return COLLISION_SELF;
        }
    }
    return COLLISION_NONE;
}

CollisionType CollisionDetector::checkPlayerCollision(int x, int y, int otherTailX[], int otherTailY[], int otherNTail) {
    for (int i = 0; i < otherNTail; i++) {
        if (otherTailX[i] == x && otherTailY[i] == y) {
            return COLLISION_OTHER_PLAYER;
        }
    }
    return COLLISION_NONE;
}

bool CollisionDetector::checkFruitCollision(int x, int y, int fruitX, int fruitY) {
    return (x == fruitX && y == fruitY);
}

// MultiplayerGame类实现
MultiplayerGame::MultiplayerGame() {
    player1 = new Player('O', 'o', "玩家1");
    player2 = new Player('X', 'x', "玩家2");
    controller = new GameController();
    scoreBoard = new ScoreBoard();
    gameOver = false;
    winner = "";
    srand(time(0));
}

MultiplayerGame::~MultiplayerGame() {
    delete player1;
    delete player2;
    delete controller;
    delete scoreBoard;
}

void MultiplayerGame::setup() {
    // 设置玩家初始位置
    player1->reset(WIDTH / 4, HEIGHT / 2);
    player2->reset(3 * WIDTH / 4, HEIGHT / 2);
    
    // 生成食物
    generateFruit();
    
    // 重置游戏状态
    gameOver = false;
    winner = "";
    scoreBoard->reset();
}

void MultiplayerGame::generateFruit() {
    bool validPosition = false;
    while (!validPosition) {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        
        // 确保食物不在蛇身上
        validPosition = true;
        
        // 检查玩家1的蛇身
        if (player1->x == fruitX && player1->y == fruitY) validPosition = false;
        for (int i = 0; i < player1->nTail && validPosition; i++) {
            if (player1->tailX[i] == fruitX && player1->tailY[i] == fruitY) {
                validPosition = false;
            }
        }
        
        // 检查玩家2的蛇身
        if (validPosition) {
            if (player2->x == fruitX && player2->y == fruitY) validPosition = false;
            for (int i = 0; i < player2->nTail && validPosition; i++) {
                if (player2->tailX[i] == fruitX && player2->tailY[i] == fruitY) {
                    validPosition = false;
                }
            }
        }
    }
}

void MultiplayerGame::drawGame() {
    system("cls");
    
    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    // 绘制游戏区域
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";
            
            // 绘制玩家1（绿色）
            if (player1->isAlive && i == player1->y && j == player1->x) {
                cout << "\033[32m" << player1->headSymbol << "\033[0m";
            }
            // 绘制玩家2（蓝色）
            else if (player2->isAlive && i == player2->y && j == player2->x) {
                cout << "\033[34m" << player2->headSymbol << "\033[0m";
            }
            // 绘制食物
            else if (i == fruitY && j == fruitX) {
                cout << "\033[31mF\033[0m";
            }
            else {
                bool printed = false;
                
                // 绘制玩家1的蛇身
                if (player1->isAlive) {
                    for (int k = 0; k < player1->nTail; k++) {
                        if (player1->tailX[k] == j && player1->tailY[k] == i) {
                            cout << "\033[32m" << player1->bodySymbol << "\033[0m";
                            printed = true;
                            break;
                        }
                    }
                }
                
                // 绘制玩家2的蛇身
                if (!printed && player2->isAlive) {
                    for (int k = 0; k < player2->nTail; k++) {
                        if (player2->tailX[k] == j && player2->tailY[k] == i) {
                            cout << "\033[34m" << player2->bodySymbol << "\033[0m";
                            printed = true;
                            break;
                        }
                    }
                }
                
                if (!printed)
                    cout << " ";
            }
            
            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }
    
    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    // 绘制分数面板和控制说明
    scoreBoard->draw(WIDTH, HEIGHT);
    controller->drawControls(WIDTH);
}

void MultiplayerGame::handleInput() {
    if (_kbhit()) {
        char key = _getch();
        
        // 处理特殊键（方向键）
        if (key == -32 || key == 0) {
            key = _getch();
            // 玩家2使用方向键
            if (player2->isAlive) {
                switch (key) {
                    case 75: // 左箭头
                        if (player2->dir != PLAYER_RIGHT)
                            player2->dir = PLAYER_LEFT;
                        break;
                    case 77: // 右箭头
                        if (player2->dir != PLAYER_LEFT)
                            player2->dir = PLAYER_RIGHT;
                        break;
                    case 72: // 上箭头
                        if (player2->dir != PLAYER_DOWN)
                            player2->dir = PLAYER_UP;
                        break;
                    case 80: // 下箭头
                        if (player2->dir != PLAYER_UP)
                            player2->dir = PLAYER_DOWN;
                        break;
                }
            }
        } else {
            // 处理普通按键
            switch (key) {
                // 玩家1使用WASD
                case 'w':
                case 'W':
                    if (player1->isAlive && player1->dir != PLAYER_DOWN)
                        player1->dir = PLAYER_UP;
                    break;
                case 's':
                case 'S':
                    if (player1->isAlive && player1->dir != PLAYER_UP)
                        player1->dir = PLAYER_DOWN;
                    break;
                case 'a':
                case 'A':
                    if (player1->isAlive && player1->dir != PLAYER_RIGHT)
                        player1->dir = PLAYER_LEFT;
                    break;
                case 'd':
                case 'D':
                    if (player1->isAlive && player1->dir != PLAYER_LEFT)
                        player1->dir = PLAYER_RIGHT;
                    break;
                    
                // 游戏控制
                case ' ':
                    if (controller->getState() == GAME_PLAYING) {
                        controller->pauseGame();
                    } else if (controller->getState() == GAME_PAUSED) {
                        controller->resumeGame();
                    }
                    break;
                case 'r':
                case 'R':
                    controller->restartGame();
                    reset();
                    break;
                case 27: // ESC
                    gameOver = true;
                    break;
            }
        }
    }
}

void MultiplayerGame::updateGame() {
    if (controller->getState() != GAME_PLAYING) return;
    
    // 更新玩家1
    if (player1->isAlive && player1->dir != PLAYER_STOP) {
        // 保存蛇尾位置
        int prevX = player1->tailX[0];
        int prevY = player1->tailY[0];
        int prev2X, prev2Y;
        player1->tailX[0] = player1->x;
        player1->tailY[0] = player1->y;
        
        for (int i = 1; i < player1->nTail; i++) {
            prev2X = player1->tailX[i];
            prev2Y = player1->tailY[i];
            player1->tailX[i] = prevX;
            player1->tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        
        // 移动头部
        switch (player1->dir) {
            case PLAYER_LEFT: player1->x--; break;
            case PLAYER_RIGHT: player1->x++; break;
            case PLAYER_UP: player1->y--; break;
            case PLAYER_DOWN: player1->y++; break;
            default: break;
        }
        
        // 碰撞检测
        CollisionType collision = CollisionDetector::checkWallCollision(
            player1->x, player1->y, WIDTH, HEIGHT);
        
        if (collision == COLLISION_NONE) {
            collision = CollisionDetector::checkSelfCollision(
                player1->x, player1->y, player1->tailX, player1->tailY, player1->nTail);
        }
        
        if (collision == COLLISION_NONE && player2->isAlive) {
            collision = CollisionDetector::checkPlayerCollision(
                player1->x, player1->y, player2->tailX, player2->tailY, player2->nTail);
            if (collision == COLLISION_NONE && player2->x == player1->x && player2->y == player1->y) {
                collision = COLLISION_OTHER_PLAYER;
            }
        }
        
        if (collision != COLLISION_NONE) {
            player1->isAlive = false;
        }
        
        // 检查是否吃到食物
        if (CollisionDetector::checkFruitCollision(player1->x, player1->y, fruitX, fruitY)) {
            player1->score += 10;
            player1->nTail++;
            scoreBoard->updateScore(1, player1->score);
            generateFruit();
        }
    }
    
    // 更新玩家2
    if (player2->isAlive && player2->dir != PLAYER_STOP) {
        // 保存蛇尾位置
        int prevX = player2->tailX[0];
        int prevY = player2->tailY[0];
        int prev2X, prev2Y;
        player2->tailX[0] = player2->x;
        player2->tailY[0] = player2->y;
        
        for (int i = 1; i < player2->nTail; i++) {
            prev2X = player2->tailX[i];
            prev2Y = player2->tailY[i];
            player2->tailX[i] = prevX;
            player2->tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        
        // 移动头部
        switch (player2->dir) {
            case PLAYER_LEFT: player2->x--; break;
            case PLAYER_RIGHT: player2->x++; break;
            case PLAYER_UP: player2->y--; break;
            case PLAYER_DOWN: player2->y++; break;
            default: break;
        }
        
        // 碰撞检测
        CollisionType collision = CollisionDetector::checkWallCollision(
            player2->x, player2->y, WIDTH, HEIGHT);
        
        if (collision == COLLISION_NONE) {
            collision = CollisionDetector::checkSelfCollision(
                player2->x, player2->y, player2->tailX, player2->tailY, player2->nTail);
        }
        
        if (collision == COLLISION_NONE && player1->isAlive) {
            collision = CollisionDetector::checkPlayerCollision(
                player2->x, player2->y, player1->tailX, player1->tailY, player1->nTail);
            if (collision == COLLISION_NONE && player1->x == player2->x && player1->y == player2->y) {
                collision = COLLISION_OTHER_PLAYER;
            }
        }
        
        if (collision != COLLISION_NONE) {
            player2->isAlive = false;
        }
        
        // 检查是否吃到食物
        if (CollisionDetector::checkFruitCollision(player2->x, player2->y, fruitX, fruitY)) {
            player2->score += 10;
            player2->nTail++;
            scoreBoard->updateScore(2, player2->score);
            generateFruit();
        }
    }
    
    // 检查游戏是否结束
    if (!player1->isAlive && !player2->isAlive) {
        gameOver = true;
        controller->endGame();
        
        // 确定获胜者
        if (player1->score > player2->score) {
            winner = player1->name;
        } else if (player2->score > player1->score) {
            winner = player2->name;
        } else {
            winner = "平局";
        }
    }
}

void MultiplayerGame::drawMenu() {
    system("cls");
    cout << endl;
    cout << "  ╔══════════════════════════════════════╗" << endl;
    cout << "  ║                                      ║" << endl;
    cout << "  ║      贪吃蛇双人对战游戏              ║" << endl;
    cout << "  ║                                      ║" << endl;
    cout << "  ╠══════════════════════════════════════╣" << endl;
    cout << "  ║                                      ║" << endl;
    cout << "  ║  玩家1 (绿色): WASD 控制             ║" << endl;
    cout << "  ║  玩家2 (蓝色): 方向键 控制           ║" << endl;
    cout << "  ║                                      ║" << endl;
    cout << "  ║  按 ENTER 开始游戏                   ║" << endl;
    cout << "  ║  按 ESC 退出                         ║" << endl;
    cout << "  ║                                      ║" << endl;
    cout << "  ╚══════════════════════════════════════╝" << endl;
}

void MultiplayerGame::drawGameOver() {
    COORD coord;
    coord.X = WIDTH / 2 - 10;
    coord.Y = HEIGHT / 2 - 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    cout << "╔══════════════════╗" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║    游戏结束      ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    if (winner == "平局") {
        cout << "║    平局!         ║" << endl;
    } else {
        cout << "║  " << winner << " 获胜!" << endl;
    }
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ P1分数: " << player1->score << "        ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ P2分数: " << player2->score << "        ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╠══════════════════╣" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ R: 重新开始      ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ ESC: 退出        ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╚══════════════════╝" << endl;
}

void MultiplayerGame::drawPause() {
    COORD coord;
    coord.X = WIDTH / 2 - 8;
    coord.Y = HEIGHT / 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    cout << "╔══════════════╗" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║   游戏暂停   ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "║ SPACE: 继续  ║" << endl;
    
    coord.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "╚══════════════╝" << endl;
}

void MultiplayerGame::run() {
    while (true) {
        if (controller->getState() == GAME_MENU) {
            drawMenu();
            
            bool waiting = true;
            while (waiting) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 13) { // ENTER
                        controller->startGame();
                        setup();
                        waiting = false;
                    } else if (key == 27) { // ESC
                        return;
                    }
                }
                Sleep(100);
            }
        }
        
        if (controller->getState() == GAME_PLAYING || controller->getState() == GAME_PAUSED) {
            drawGame();
            
            if (controller->getState() == GAME_PAUSED) {
                drawPause();
            }
            
            handleInput();
            updateGame();
            
            if (gameOver) {
                controller->endGame();
            }
            
            Sleep(100);
        }
        
        if (controller->getState() == GAME_OVER) {
            drawGame();
            drawGameOver();
            
            bool waiting = true;
            while (waiting) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 'r' || key == 'R') {
                        controller->restartGame();
                        reset();
                        waiting = false;
                    } else if (key == 27) { // ESC
                        return;
                    }
                }
                Sleep(100);
            }
        }
    }
}

void MultiplayerGame::reset() {
    setup();
}
