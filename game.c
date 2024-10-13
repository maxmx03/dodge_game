
#include <raylib.h>
#include <stdbool.h>

#define AXE_COUNT 5

int main() {
  int width = 1230;
  int height = 500;
  int origin = 0;
  int speed = 10;
  int direction = 10;
  const char title[] = "Dodge Game";
  InitWindow(width, height, title);

  int circleX = 0;
  int circleY = height / 2;
  int circleR = 25;

  Rectangle flag = {width - (circleR * 2), (float)height / 2, 25, 25};
  Rectangle circle = {circleX, circleY, circleR * 2, circleR * 2};
  Rectangle axes[AXE_COUNT];
  int axeSpeeds[AXE_COUNT];

  for (int i = 0; i < AXE_COUNT; i++) {
    axes[i].x = GetRandomValue(100, width - 100);
    axes[i].y = GetRandomValue(0, height - 100);
    axes[i].width = 50;
    axes[i].height = 50;
    axeSpeeds[i] = GetRandomValue(5, 15);
  }

  bool collisionWithAxe = false;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawRectangleRec(flag, BLACK);

    if (collisionWithAxe) {
      DrawText("Game Over!", width / 2 - 50, height / 2, 20, RED);
    } else {
      for (int i = 0; i < AXE_COUNT; i++) {
        if (CheckCollisionRecs(circle, axes[i])) {
          collisionWithAxe = true;
        }
      }

      for (int i = 0; i < AXE_COUNT; i++) {
        DrawRectangleRec(axes[i], RED);
        axes[i].y += axeSpeeds[i];

        if (axes[i].y > height - axes[i].height || axes[i].y < origin) {
          axeSpeeds[i] *= -1;
        }
      }

      DrawRectangleRounded(circle, 100.0, 0, YELLOW);

      if (CheckCollisionRecs(circle, flag)) {
        DrawText("You Win!", width / 2 - 50, height / 2, 20, BLUE);
      } else {
        if (IsKeyDown(KEY_D) && circle.x + circle.width < width)
          circle.x += speed;
        if (IsKeyDown(KEY_A) && circle.x > origin)
          circle.x -= speed;
        if (IsKeyDown(KEY_W) && circle.y > origin)
          circle.y -= speed;
        if (IsKeyDown(KEY_S) && circle.y + circle.height < height)
          circle.y += speed;
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
