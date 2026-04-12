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
    Texture2D setting = LoadTexture("Resources/setting.png");

    Font font = LoadFontEx("Resources/monogram.ttf", 64, 0, 0);

    Game game = Game();

    bool inMenu = true;

    while(WindowShouldClose() == false){
        UpdateMusicStream(game.music);

        Vector2 mousePoint = GetMousePosition();
        Rectangle settingBtn = {440, 560, 45, 45};

        if (IsKeyPressed(KEY_SPACE)) {
            if (!inMenu && !game.gameOver) {
                game.inSettings = !game.inSettings;

            if (game.inSettings) game.isPaused = true;
            else game.isPaused = false;
    }
}

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, settingBtn)){
            game.inSettings = !game.inSettings;

            if (game.inSettings && !inMenu && !game.gameOver){
                game.isPaused = true;
            }
        } else if (game.inSettings){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Rectangle MusicBtn = {125, 200, 250, 50};
                Rectangle sfxBtn = {125, 280, 250, 50};
                Rectangle continueBtn = {125, 360, 250, 50};
                Rectangle returnBtn = {125, 440, 250, 50};

                if (CheckCollisionPointRec(mousePoint, MusicBtn)){
                    game.musicEnabled = !game.musicEnabled;

                    if (game.musicEnabled) ResumeMusicStream(game.music);
                    else PauseMusicStream(game.music);
                }
                if (CheckCollisionPointRec(mousePoint, sfxBtn)){
                    game.sfxEnabled = !game.sfxEnabled;
                }
                if (CheckCollisionPointRec(mousePoint, continueBtn)){
                    game.inSettings = false;
                    game.isPaused = false;
                }
                if (!inMenu){
                    if (CheckCollisionPointRec(mousePoint, returnBtn)){
                        game.inSettings = false;
                        game.isPaused = false;
                        inMenu = true;
                        game.Reset();
                    }
                }
            }
        } else {

        if (inMenu){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
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

        if (game.gameOver){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Rectangle newGameBtn = {125, 380, 250, 50};

                if (CheckCollisionPointRec(mousePoint, newGameBtn)){
                    game.Reset();
                }
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

        if (game.gameOver){
            DrawRectangle(0, 0, 500, 620, Fade(BLACK, 0.8f));
            DrawTextEx(font, "GAME OVER", {120, 150}, 60, 2, RED);
            const char* finalScoreText = TextFormat("Final Score: %d", game.score);
            Vector2 textSize = MeasureTextEx(font, finalScoreText, 40, 2);
            DrawTextEx(font, finalScoreText, {(500 - textSize.x)/2, 250}, 40, 2, YELLOW);

            Rectangle newGameBtn = {125, 380, 250, 50};
            DrawRectangleRec(newGameBtn, LIGHTGRAY);
            DrawTextEx(font, "New Game", {170, 390}, 38, 2, BLACK);
        }
        }

        DrawTexture(setting, 440, 560, WHITE);

        if (game.inSettings){
            DrawRectangle(0, 0, 500, 620, Fade(BLACK, 0.9f));
            DrawTextEx(font, "Settings", {150, 100}, 50, 2, WHITE);

            Rectangle MusicBtn = {125, 200, 250, 50};
            DrawRectangleRounded(MusicBtn, 0.2, 5, game.musicEnabled ? GREEN : GRAY);
            DrawTextEx(font, game.musicEnabled ? "Music: ON" : "Music: OFF", {160, 210}, 38, 2, BLACK);

            Rectangle sfxBtn = {125, 280, 250, 50};
            DrawRectangleRounded(sfxBtn, 0.2, 5, game.sfxEnabled ? GREEN : GRAY);
            DrawTextEx(font, game.sfxEnabled ? "SFX: ON" : "SFX: OFF", {180, 290}, 38, 2, BLACK);

            Rectangle continueBtn = {125, 360, 250, 50};
            DrawRectangleRounded(continueBtn, 0.2, 5, LIGHTGRAY);
            DrawTextEx(font, "Continue", {175, 370}, 38, 2, BLACK);

            if (!inMenu){
                Rectangle returnBtn = {125, 440, 250, 50};
                DrawRectangleRounded(returnBtn, 0.2, 5, LIGHTGRAY);
                DrawTextEx(font, "Return Menu", {145, 450}, 38, 2, BLACK);
            }
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(menu);
    UnloadTexture(setting);

    CloseWindow();
    return 0;
}
