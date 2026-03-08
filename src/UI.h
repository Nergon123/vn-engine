#pragma once
#include <raylib.h>
#include <string>
#include <functional>
class UIElement
{
public:
    virtual void render() = 0;
    Vector2 size = {-1, -1};
    Vector2 location = {-1, -1};
    UIElement *previousElement;
    UIElement *nextElement;
};

class Label : UIElement
{
public:
    std::string text;
    Font *font;
    int spacing = 1;
    float fontSize;
    Vector2 size = {-1, -1};
    Vector2 location = {-1, -1};
    Color color = WHITE;
    void render() override
    {
        DrawTextEx(*font, text.c_str(), location, fontSize, spacing, color);
    };
    Label(std::string text, Font *font, float fontSize, Vector2 location, Color color)
        : text(text), font(font), fontSize(fontSize), location(location), color(color)
    {
        size = MeasureTextEx(*font, text.c_str(), fontSize, spacing);
    };
};

class Button : UIElement
{
public:
    Vector2 size = {-1, -1};
    Vector2 location = {-1, -1};
    Label *label;
    Texture2D unselected;
    Texture2D selected;
    bool isGraphical;
    bool interactive;
    bool isSelected;
    bool isSelectedTextureValid;
    bool isUnselectedTextureValid;
    bool isLabel;
    void (*function)();
    Color tint;
    Color selectedTint;
    void render() override
    {
        Vector2 mousepos = GetMousePosition();
        if (mousepos.x > location.x && mousepos.y > location.y && mousepos.x < location.x + size.x && mousepos.y < location.y + size.y)
        {
            isSelected = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && function)
            {
                function();
            }
        }
        else
        {
            isSelected = false;
        }
        if (isSelectedTextureValid && isUnselectedTextureValid)
        {
            DrawTexture(isSelected ? selected : unselected, location.x, location.y, interactive ? (isSelected ? selectedTint : tint) : DARKGRAY);
        }
        else if (isUnselectedTextureValid)
        {
            DrawTexture(isSelected ? selected : unselected, location.x, location.y, interactive ? (isSelected ? selectedTint : tint) : DARKGRAY);
        }
        else
        {
            DrawRectangleRec(Rectangle{location.x, location.y, size.x, size.y}, interactive ? (isSelected ? selectedTint : tint) : DARKGRAY);
        }

        if (label)
        {
            label->render();
        }
    }
    Button(Label *label, Vector2 location, Vector2 size = {-1, -1}, bool interactive = false, bool isGraphical = false, Texture2D unselected = Texture2D(), Texture2D selected = Texture2D(), float padding = 5, Color tint = GRAY, Color selectedTint = LIGHTGRAY, Color labelTint = WHITE)
        : label(label), location(location), size(size), interactive(interactive), isGraphical(isGraphical), unselected(unselected), selected(selected), tint(tint), selectedTint(selectedTint)
    {
        if (size.x < 0 || size.y < 0)
        {
            if (isGraphical)
            {
                if (isUnselectedTextureValid)
                    size = {(float)unselected.width, (float)unselected.height};
                else if (isSelectedTextureValid)
                    size = {(float)selected.width, (float)selected.height};
            }
        }
        if (label)
        {
            // Center the label within the button
            Vector2 labelLocation = label->location;
            label->location = {location.x + (size.x - label->size.x) / 2, location.y + (size.y - label->size.y) / 2};
            label->location = {labelLocation.x + label->location.x, labelLocation.y + label->location.y};
            label->color = interactive ? labelTint : GRAY;
        }
    }
};