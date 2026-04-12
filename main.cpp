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

    Font font = LoadFontEx("Resources/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose() == false){
        UpdateMusicStream(game.music);
        game.HandleInput();

        if (EventTriggered(0.4) && game.gameOver == false && game.isPaused == false){
            game.MoveBlockDown();
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
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        if(game.isPaused){
            DrawRectangle(0, 0, 500, 620, Fade(BLACK, 0.6f));
            Rectangle continueBtn = {125, 250, 250, 50};
            DrawRectangleRec(continueBtn, LIGHTGRAY);
            DrawTextEx(font, "Continue", {165, 255}, 38, 2, BLACK);

            Rectangle newGameBtn = {125, 350, 250, 50};
            DrawRectangleRec(newGameBtn, LIGHTGRAY);
            DrawTextEx(font, "New Game", {165, 355}, 38, 2, BLACK);
        } else {
        game.Draw();
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
        EndDrawing();
    }
    CloseWindow();
}
