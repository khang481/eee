#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(530, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    bool isPaused = false;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);

        if (IsKeyPressed(KEY_SPACE)) {
            isPaused = !isPaused;
        }

        if (!isPaused && !game.gameOver)
        {
            game.HandleInput();
            if (EventTriggered(0.2))
            {
                game.MoveBlockDown();
            }
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.Draw();

        if (game.gameOver)
        {
            DrawRectangle(0, 0, 530, 620, Fade(BLACK, 0.3f));
            DrawTextEx(font, "GAME OVER", {90, 280}, 60, 2, YELLOW);
        }
        else if (isPaused)
        {
            DrawRectangle(0, 0, 530, 620, Fade(BLACK, 0.3f));
            DrawTextEx(font, "PAUSED", {150, 280}, 60, 2, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
}
