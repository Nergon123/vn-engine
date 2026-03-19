#include <raylib.h>
#include <string>
#include <vector>
struct DisplayableImage {
    Texture2D texture;
    Vector2   position;
    Vector3   rotation;
    Vector2   size;
    Vector2   scale;
    Color     tint;
};
void ChangeTextBox(std::string newText,std::string speaker);
void DrawDisplayableImage(DisplayableImage image);
void BeginFrame();
void DrawDebugInfo();
void SceneSetup();
void Scene();
void MessageBox();
void DebugPrint(std::string info);
void RenderScene();