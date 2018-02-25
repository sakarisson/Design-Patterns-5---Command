#include "GameInterface.h"
#include "MoveCommand.h"

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;

GameInterface::GameInterface() {
    _hanoiEngine = std::make_unique<HanoiEngine>();
    _commandManager = std::make_unique<CommandManager>();
    lastMenuResult = "";
}

GameInterface::~GameInterface() {

}

void GameInterface::run() {
    while (!_hanoiEngine->isDone()) {
        this->tick();
    }
}

void GameInterface::showGame() {
    _hanoiEngine->show();
}

void GameInterface::showMenu() {
    cout <<
        "1. Replay last game" << endl <<
        "2. Move" << endl <<
        "3. Undo" << endl <<
        "4. Redo" << endl <<
        "5. Reset" << endl;
    if (lastMenuResult != "") {
        cout <<
            "====================================" << endl <<
            lastMenuResult << endl <<
            "====================================" << endl;
    }
    cout <<
        "What would you like to do? ";
}

int GameInterface::getUserInput() {
    int input;
    std::cin >> input;
    return input;
}

void GameInterface::tick() {
    cout <<
        "Towers of Hanoi" << endl <<
        "============================================================" << endl;
    this->showGame();
    cout <<
        "============================================================" << endl;
    this->showMenu();
    int choice = this->getUserInput();
    switch (choice) {
    case 1:
        this->replay();
        break;
    case 2:
        this->move();
        break;
    case 3:
        this->undo();
        break;
    case 4:
        this->redo();
        break;
    case 5:
        this->reset();
        break;
    default:
        lastMenuResult = "Invalid choice";
        break;
    }
    getchar();
    system("cls");
}

void GameInterface::replay() {

}

void GameInterface::move() {
    int from, to;
    cout <<
        "From: ";
    std::cin >> from;
    cout <<
        "To: ";
    std::cin >> to;
    if (1 > from || 3 < from || 1 > to || 3 < to) {
        lastMenuResult = "Invalid tower. Please pick a number between 1 and 3";
        return;
    }
    // Implied else
    std::unique_ptr<MoveCommand> gameMove = std::make_unique<MoveCommand>(from - 1, to - 1, _hanoiEngine.get());
    _commandManager->storeAndExecute(std::move(gameMove));
    lastMenuResult = "Moved disc from tower " + std::to_string(from) + " to tower " + std::to_string(to);
}

void GameInterface::undo() {

}

void GameInterface::redo() {

}

void GameInterface::reset() {

}