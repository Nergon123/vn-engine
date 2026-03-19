#include "Scene.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <raylib.h>
#include <string>
#include <vector>
int         currentLine    = 0;
std::string currentLineStr = "";
std::string currentFile    = "game/game.vn";
std::string currentLabel   = "";
ulong       linePos        = 0;
std::string currentFileContent;
void        readFromFile(std::string fileName);
void        readNewFile(std::string fileName);
struct Command {
    std::string                                   command;
    std::function<void(std::vector<std::string>)> func;
};

void exceptionHandler(std::string error) { std::cerr << "Error: " << error << std::endl; }

void checkArgsCount(std::vector<std::string> args, int expected, std::string command) {
    if (args.size() != expected) {
        exceptionHandler("Command " + command + " expects " + std::to_string(expected) +
                         " arguments, but got " + std::to_string(args.size()));
    }
}

void sayCommand(std::vector<std::string> args) {
    checkArgsCount(args, 2, "say");
    // say [Character] "Dialogue";
    // flags in dialogue:
    // $[color = #RRGGBB] for changing text color $[/color]
    // $[speed = value] for changing text speed $[/speed]
    // $[wait = value] for adding a wait after the text is displayed $[/wait]
    // $[bold] $[/bold]
    // $[italic] $[/italic]
    // $[underline] $[/underline]
    // $var
    // $$ for literal $
    ChangeTextBox(args[1], args[0]);
}

void jumpCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "jump");

    // jump [label];
}

void playAudioCommand(std::vector<std::string> args) {
    if (args.size() < 2) { checkArgsCount(args, 2, "playAudio"); }
    // playAudio [id] [Audio] [flags];
    // flags: loop, music, sfx , volume=[0-100]
}

void modAudioCommand(std::vector<std::string> args) {
    if (args.size() < 2) { checkArgsCount(args, 2, "modAudio"); }
    // modAudio [id] [flags];
    // flags: loop, music, sfx , volume=[0-100]
}

void stopAudioCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "stopAudio");
    // stopAudio [id];
}

void setBackgroundCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "setBackground");
    // setBackground [Background];
}

void showCharacterCommand(std::vector<std::string> args) {
    checkArgsCount(args, 4, "showCharacter");
    // showCharacter [Character] [Clothes] [Expression] [Location];
}

void hideCharacterCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "hideCharacter");

    // hideCharacter [Character];
}

void setExpressionCommand(std::vector<std::string> args) {
    checkArgsCount(args, 2, "setExpression");
    // setExpression [Character] [Expression];
}
void waitCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "wait");
    // wait [duration in ms];
}
void choiceCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "choice");
    // choice [Option 1] [Label 1] [Option 2] [Label 2] ... [Option n] [Label n];
}
void labelCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "label");
    // label [id]{
}
void endLabelCommand(std::vector<std::string> args) {
    checkArgsCount(args, 0, "endLabel");
    // endLabel;
}
void returnCommand(std::vector<std::string> args) {
    checkArgsCount(args, 0, "return");
    // return from label;
}
void setVariableCommand(std::vector<std::string> args) {
    checkArgsCount(args, 2, "setVariable");
    // setVariable [name] [value];
}

void ifCommand(std::vector<std::string> args) {
    checkArgsCount(args, 4, "if");
    // if [Variable] [Operator] [Value] [Label if true];
}

void elseCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "else");
    // else [Label if false];
}

void elifCommand(std::vector<std::string> args) {
    checkArgsCount(args, 4, "elif");
    // elif [Variable] [Operator] [Value] [Label if true];
}

void endIfCommand(std::vector<std::string> args) {
    checkArgsCount(args, 0, "endIf");
    // endIf;
}

void nextFileCommand(std::vector<std::string> args) {
    checkArgsCount(args, 1, "nextFile");
    // nextFile [fileName];
    currentFileContent = "";
    linePos            = 0;
    readNewFile(args[0]);
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
std::ifstream file;
void          readNewFile(std::string fileName) {
    if (file.is_open()) { file.close(); }
    file.open(fileName);
    readFromFile(fileName);
}

void readFromFile(std::string fileName) {
    if (!file.is_open()) {
        exceptionHandler("Could not open file: " + fileName);
        return;
    }
    if (!getline(file, currentLineStr, ';')) {
        currentLineStr.clear();
        file.close(); // optional but clean
        exit(0);
        return;
    }
}

void unexpectedChar(char character, std::string expected) {
    if (expected.find(character) == std::string::npos) { return; }
    exceptionHandler("Unexpected character '" + std::string(1, character) + "' at position " +
                     std::to_string(linePos) + " in line: " + currentLineStr);
}

std::vector<std::string> parseNextCommand() {
    std::string command;
    if (!file.is_open()) { readNewFile(currentFile); }
    currentLineStr.replace (0, currentLineStr.find_first_not_of(" \t\n\r\f\v"), ""); // trim left
    printf("Parsing line %d: %s\n", currentLine, currentLineStr.c_str());
    std::vector<std::string> args;

    std::string currentArg;
    while (linePos < currentLineStr.size()) {
        char c = currentLineStr[linePos++];
        printf("%c\n", c);

        if (c == '\\') {
            if (linePos < currentLineStr.size()) { currentArg += currentLineStr[linePos++]; }
        }
        else if (c == ' ') {
            if (!currentArg.empty()) {
                args.push_back(currentArg);
                currentArg.clear();
            }
        }
        else if (c == '"') {
            while (linePos < currentLineStr.size() && currentLineStr[linePos] != '"') {
                if (currentLineStr[linePos] == '\\' && linePos + 1 < currentLineStr.size()) {
                    currentArg += currentLineStr[linePos + 1];
                    linePos += 2;
                }
                else { currentArg += currentLineStr[linePos++]; }
            }
            if (linePos < currentLineStr.size()) { linePos++; }
            else { exceptionHandler("Unclosed quote"); }
        }
        else if (c == '[') {
            while (linePos < currentLineStr.size() && currentLineStr[linePos] != ']') {
                if (currentLineStr[linePos] == '\\' && linePos + 1 < currentLineStr.size()) {
                    currentArg += currentLineStr[linePos + 1];
                    linePos += 2;
                }
                else { currentArg += currentLineStr[linePos++]; }
            }
            if (linePos < currentLineStr.size()) { linePos++; }
            else { exceptionHandler("Unclosed bracket"); }
        }
        else { currentArg += c; }
    }
    if (!currentArg.empty()) { args.push_back(currentArg); }
    currentLine++;
    linePos = 0;
    readFromFile(currentFile);
    return args;
}
void executeNextCommand() {
    std::vector<std::string> args = parseNextCommand();
    if (args.empty()) {
        readFromFile(currentFile);
        return;
    }
    std::string cmd = args[0];
    args.erase(args.begin());
    for (auto &command : commands) {
        if (command.command == cmd) {
            command.func(args);
            return;
        }
    }
    exceptionHandler("Unknown command: " + cmd);
}