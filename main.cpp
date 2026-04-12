#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main(){
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("Resources/background.jpg");
    Texture2D menu = LoadTexture("Resources/menu.png");

    Font font = LoadFontEx("Resources/monogram.ttf", 64, 0, 0);

    Game game = Game();

    bool inMenu = true;

    while(WindowShouldClose() == false){
        UpdateMusicStream(game.music);

        if (inMenu){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mousePoint = GetMousePosition();
                Rectangle startBtn = {125, 450, 250, 60};

                if (CheckCollisionPointRec(mousePoint, startBtn)){
                    inMenu = false;
                }
            }
        } else {
                game.HandleInput();
                if (EventTriggered(0.35) && game.gameOver == false && game.isPaused == false){
                    game.MoveBlockDown();
        }
        }

        if (game.isPaused){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mousePoint = GetMousePosition();

                Rectangle continueBtn = {125, 250, 250, 50};
                Rectangle newGameBtn = {125, 350, 250, 50};

                if (CheckCollisionPointRec(mousePoint, continueBtn)){
                    game.isPaused = false;
                }
                if (CheckCollisionPointRec(mousePoint, newGameBtn)){
                    game.Reset();
                    game.isPaused = false;
                }
            }
        }

        if (game.gameOver){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 mousePoint = GetMousePosition();

                Rectangle newGameBtn = {125, 380, 250, 50};

                if (CheckCollisionPointRec(mousePoint, newGameBtn)){
                    game.Reset();
                }
            }
        }

        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);

        if (inMenu){
            DrawTexture(menu, 0, 0, WHITE);

            const char* creatorText = "with HuBo & Xahoy";
            Vector2 textSize = MeasureTextEx(font, creatorText, 30, 2);
            DrawTextEx(font, creatorText, {(500 - textSize.x)/2, 380}, 30, 2, WHITE);

            Rectangle startBtn = {125, 450, 250, 60};
            DrawRectangleRounded(startBtn, 0.2, 5, DARKBLUE);
            DrawTextEx(font, "START GAME", {150, 460}, 40, 2, WHITE);
        } else {
            DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
            DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, darkBlue);

            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

            DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, darkBlue);
            game.Draw();

        if (game.isPaused){
            DrawRectangle(0, 0, 500, 620, Fade(BLACK, 0.6f));
            Rectangle continueBtn = {125, 250, 250, 50};
            DrawRectangleRec(continueBtn, LIGHTGRAY);
            DrawTextEx(font, "Continue", {165, 255}, 38, 2, BLACK);

            Rectangle newGameBtn = {125, 350, 250, 50};
            DrawRectangleRec(newGameBtn, LIGHTGRAY);
            DrawTextEx(font, "New Game", {165, 355}, 38, 2, BLACK);
        }

        if (game.gameOver){
            DrawRectangle(0, 0, 500, 620, Fade(BLACK, 0.8f));
            DrawTextEx(font, "GAME OVER", {120, 150}, 60, 2, RED);
            const char* finalScoreText = TextFormat("Final Score: %d", game.score);
            Vector2 textSize = MeasureTextEx(font, finalScoreText, 40, 2);
            DrawTextEx(font, finalScoreText, {(500 - textSize.x)/2, 250}, 40, 2, YELLOW);

            Rectangle newGameBtn = {125, 380, 250, 50};
            DrawRectangleRec(newGameBtn, LIGHTGRAY);
            DrawTextEx(font, "New Game", {165, 390}, 38, 2, BLACK);
        }
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(menu);

    CloseWindow();
    return 0;
}
