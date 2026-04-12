#pragma once
#include "grid.h"
#include "blocks.cpp"
using namespace std;

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void Reset();
    bool gameOver;
    bool isPaused;
    int score;
    Music music;
    bool inSettings;
    bool musicEnabled;
    bool sfxEnabled;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};
