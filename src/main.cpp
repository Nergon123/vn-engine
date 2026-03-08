#include <raylib.h>
#include "Render.h"
int main()
{
    InitWindow(1280, 720, "Hello world");
    setupRender();
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    while (!WindowShouldClose())
    {
        BeginDrawing();
        renderLoop();
        EndDrawing();
        printf("fps:%d\n", GetFPS());
    }
}