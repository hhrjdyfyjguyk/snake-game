#ifndef MULTIPLAYER_GAME_H
#define MULTIPLAYER_GAME_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// 游戏状态枚举
enum GameState {
    GAME_MENU,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_OVER
};

// 玩家方向枚举
enum PlayerDirection {
    PLAYER_STOP = 0,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_UP,
    PLAYER_DOWN
};

// 碰撞类型枚举
enum CollisionType {
    COLLISION_NONE,
    COLLISION_WALL,
    COLLISION_SELF,
    COLLISION_OTHER_PLAYER
};

// 玩家结构体
struct Player {
    int x, y;                           // 头部位置
    int tailX[100], tailY[100];         // 蛇身位置
    int nTail;                          // 蛇身长度
    int score;                          // 当前分数
    int highScore;                      // 最高分
    PlayerDirection dir;                // 当前方向
    char headSymbol;                    // 头部符号
    char bodySymbol;                    // 身体符号
    string name;                        // 玩家名称
    bool isAlive;                       // 是否存活
    
    Player(char head, char body, string playerName);
    void reset(int startX, int startY);
};

// 分数面板类
class ScoreBoard {
private:
    int player1Score;
    int player2Score;
    int player1HighScore;
    int player2HighScore;
    
public:
    ScoreBoard();
    void updateScore(int player, int score);
    void updateHighScore(int player, int score);
    void draw(int width, int height);
    void reset();
};

// 游戏控制类
class GameController {
private:
    GameState currentState;
    bool isRunning;
    
public:
    GameController();
    void startGame();
    void pauseGame();
    void resumeGame();
    void restartGame();
    void endGame();
    GameState getState() const;
    bool getIsRunning() const;
    void drawControls(int width);
};

// 碰撞检测类
class CollisionDetector {
public:
    static CollisionType checkWallCollision(int x, int y, int width, int height);
    static CollisionType checkSelfCollision(int x, int y, int tailX[], int tailY[], int nTail);
    static CollisionType checkPlayerCollision(int x, int y, int otherTailX[], int otherTailY[], int otherNTail);
    static bool checkFruitCollision(int x, int y, int fruitX, int fruitY);
};

// 双人对战游戏类
class MultiplayerGame {
private:
    static const int WIDTH = 30;
    static const int HEIGHT = 20;
    
    Player* player1;                    // 玩家1（绿色，WASD控制）
    Player* player2;                    // 玩家2（蓝色，方向键控制）
    int fruitX, fruitY;                 // 食物位置
    GameController* controller;         // 游戏控制器
    ScoreBoard* scoreBoard;             // 分数面板
    bool gameOver;                      // 游戏结束标志
    string winner;                      // 获胜者
    
    void generateFruit();
    void drawGame();
    void handleInput();
    void updateGame();
    void drawMenu();
    void drawGameOver();
    void drawPause();
    
public:
    MultiplayerGame();
    ~MultiplayerGame();
    void setup();
    void run();
    void reset();
};

#endif // MULTIPLAYER_GAME_H
