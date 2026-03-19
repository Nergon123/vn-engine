#include "UI.h"
#include <raylib.h>

#include "Scene.h"
// Visual novel main scene

std::string currentText        = "hello world";
std::string currentSpeaker     = "";
int         textIndex          = 0;
float       textSpeed          = 50; // characters per second
float       textTimer          = 0;
bool        isMessageBoxActive = 1;

std::string DebugInfo   = "";
bool        isDebugMode = 1;

std::vector<DisplayableImage> currentImages;

DisplayableImage textBoxImage;
Vector2          textBoxPosition    = {0, 400};
Vector2          textBoxSize        = {800, 200};
int              textBoxFrameOffset = 10;

void ChangeTextBox(std::string newText,std::string speaker) {
    currentText        = newText;
    currentSpeaker     = speaker;
    textIndex          = 0;
    textTimer          = 0;
    isMessageBoxActive = true;
}

void SceneSetup() {
    DisplayableImage bg;
    bg.texture  = LoadTexture("images/bg.png");
    bg.position = {0, 0};
    bg.rotation = {0, 0, 0};
    bg.size     = {(float)GetRenderWidth(), (float)GetRenderHeight()};
    bg.tint     = WHITE;
    currentImages.push_back(bg);
    textBoxImage.texture  = LoadTexture("assets/textbox.png");
    textBoxImage.position = textBoxPosition;
    textBoxImage.rotation = {0, 0, 0};
    textBoxImage.scale    = {textBoxSize.x / textBoxImage.texture.width,
                             textBoxSize.y / textBoxImage.texture.height};
    textBoxImage.tint     = WHITE;
    textBoxPosition       = {textBoxImage.position.x + textBoxFrameOffset,
                             textBoxImage.position.y + textBoxFrameOffset};
    if (textBoxImage.texture.id != 0) {
        textBoxSize = {textBoxImage.texture.width * textBoxImage.scale.x - textBoxFrameOffset * 2,
                       textBoxImage.texture.height * textBoxImage.scale.y -
                           textBoxFrameOffset * 2};
    }
    else {
        textBoxSize     = {(float)GetRenderWidth() / 1.5f, (float)GetRenderHeight() / 5};
        textBoxPosition = {(GetRenderWidth() - textBoxSize.x) / 2,
                           (GetRenderHeight() - textBoxSize.y) / 1.05f};
    }
}

void DrawDisplayableImage(DisplayableImage image) {
    if (image.texture.id == 0) {
        if (image.size.x == 0 || image.size.y == 0) { return; }
        DrawRectangleV(image.position, image.size, image.tint);
        return;
    }
    if (image.size.x != 0 && image.size.y != 0) {
        image.scale = {image.size.x / image.texture.width, image.size.y / image.texture.height};
    }
    DrawTextureEx(image.texture, image.position, image.rotation.y, image.scale.x, image.tint);
}

void BeginFrame() {
    if (isDebugMode) { DebugInfo = ""; }
    DebugPrint("DEBUG:");
    DebugPrint("FPS: " + std::to_string(GetFPS()));
}
void DrawDebugInfo() {
    if (isDebugMode) {

        Vector2 size = MeasureTextEx(GetFontDefault(), DebugInfo.c_str(), 20, 1);
        DrawRectangle(0, 0, size.x + 50, size.y, (Color){0, 0, 0, 128});
        DrawText(DebugInfo.c_str(), 10, 10, 20, WHITE);
    }
}
void DebugPrint(std::string info) {
    if (isDebugMode) { DebugInfo += info + "\n"; }
}
struct Character {
    std::string      name;
    u_int32_t        color;
    DisplayableImage image;
};

void MessageBox() {
    if (isMessageBoxActive) {
        if (textBoxImage.texture.id == 0) {
            DrawRectangleV(textBoxPosition, textBoxSize, (Color){0, 0, 0, 128});
        }
        else { DrawDisplayableImage(textBoxImage); }
        DrawText(currentSpeaker.c_str(), textBoxPosition.x + textBoxFrameOffset,
                 textBoxPosition.y + textBoxFrameOffset - 25, 20, WHITE);
        if (textIndex < currentText.size()) {
            textTimer += GetFrameTime();
            if (textTimer >= 1.0f / textSpeed) {
                textIndex++;
                textTimer = 0;
            }

            DrawText(currentText.substr(0, textIndex).c_str(),
                     textBoxPosition.x + textBoxFrameOffset,
                     textBoxPosition.y + textBoxFrameOffset, 20, WHITE);
        }
        else {
            DrawText(currentText.c_str(), textBoxPosition.x + textBoxFrameOffset,
                     textBoxPosition.y + textBoxFrameOffset, 20, WHITE);
        }
    }
}

void Scene() {
    if (currentImages.empty()) { return; }
    DebugInfo += "Images:\n";
    // render images in order of currentImages vector
    for (auto &image : currentImages) {
        Texture2D tex = image.texture;
        DebugPrint("X: " + std::to_string((int)image.position.x) +
                   " Y: " + std::to_string((int)image.position.y) +
                   " ID: " + std::to_string(image.texture.id) + "\n");

        DrawDisplayableImage(image);
    }
}

void RenderScene() {
    BeginFrame();
    Scene();
    MessageBox();
    DrawDebugInfo();
}