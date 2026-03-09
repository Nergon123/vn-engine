#include <string>
#include <vector>
#include <functional>
#include <raylib.h>
int currentLine = 0;
std::string currentFile = "game.vn";
std::string currentLabel = "";




struct Command
{
    std::string command;
    std::function<void(std::vector<std::string>)> func;
};

void sayCommand(std::vector<std::string> args)
{
    // say [Character] "Dialogue";
    //flags in dialogue:
    // $[color = #RRGGBB] for changing text color $[/color]
    // $[speed = value] for changing text speed $[/speed]
    // $[wait = value] for adding a wait after the text is displayed $[/wait]
    // $[bold] $[/bold]
    // $[italic] $[/italic]
    // $[underline] $[/underline]
    // $var
    // $$ for literal $




}

void jumpCommand(std::vector<std::string> args)
{
    // jump [label];
}

void playAudioCommand(std::vector<std::string> args)
{
    // playAudio [id] [Audio] [flags];
    // flags: loop, music, sfx , volume=[0-100]
}

void modAudioCommand(std::vector<std::string> args)
{
    // modAudio [id] [flags];
    // flags: loop, music, sfx , volume=[0-100]
}

void stopAudioCommand(std::vector<std::string> args)
{
    // stopAudio [id];
}

void setBackgroundCommand(std::vector<std::string> args)
{
    // setBackground [Background];
}

void showCharacterCommand(std::vector<std::string> args)
{
    // showCharacter [Character] [Expression] [Location];
}

void hideCharacterCommand(std::vector<std::string> args)
{
    // hideCharacter [Character];
}

void setExpressionCommand(std::vector<std::string> args)
{
    // setExpression [Character] [Expression];
}
void waitCommand(std::vector<std::string> args)
{
    // wait [duration in ms];
}
void choiceCommand(std::vector<std::string> args)
{
    // choice [Option 1] [Label 1] [Option 2] [Label 2] ... [Option n] [Label n];
}
void labelCommand(std::vector<std::string> args)
{
    // label [id]{
}
void endLabelCommand(std::vector<std::string> args)
{
    // endLabel;
}
void returnCommand(std::vector<std::string> args)
{
    // return from label;
}
void setVariableCommand(std::vector<std::string> args)
{
    // setVariable [name] [value];
}

void ifCommand(std::vector<std::string> args)
{
    // if [Variable] [Operator] [Value] [Label if true];
}

void elseCommand(std::vector<std::string> args)
{
    // else [Label if false];
}

void elifCommand(std::vector<std::string> args)
{
    // elif [Variable] [Operator] [Value] [Label if true];
}

void endIfCommand(std::vector<std::string> args)
{
    // endIf;
}

void nextFileCommand(std::vector<std::string> args)
{
    // nextFile [fileName];
}

std::vector<Command> commands = {
    {"say", sayCommand},
    {"jump", jumpCommand},
    {"playAudio", playAudioCommand},
    {"modAudio", modAudioCommand},
    {"stopAudio", stopAudioCommand},
    {"setBackground", setBackgroundCommand},
    {"showCharacter", showCharacterCommand},
    {"hideCharacter", hideCharacterCommand},
    {"setExpression", setExpressionCommand},
    {"wait", waitCommand},
    {"choice", choiceCommand},
    {"label", labelCommand},
    {"endLabel", endLabelCommand},
    {"return", returnCommand},
    {"setVariable", setVariableCommand},
    {"if", ifCommand},
    {"else", elseCommand},
    {"elif", elifCommand},
    {"endIf", endIfCommand},
    {"nextFile", nextFileCommand},
};

void parseCommand(std::string input)
{
}