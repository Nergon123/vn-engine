#include "Render.h"
Font font;
Button *button;

void setupRender()
{
    font = LoadFont("FreeSerif.ttf");
    button = new Button(new Label("Hello world", &font, 40, {0, 0}, WHITE), {100, 100}, {200, 50}, true, false, Texture2D(), Texture2D());
}
void renderLoop()
{
    button->render();
}