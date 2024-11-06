#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iostream>
#include "./headers/chordinate.h"

// using namespace std;

// todo: battle function given set parameters + battle subfunctions
// enum Command {}

// TO RUN:
// CTRL + `
// g++ chordinate.cpp main.cpp -o main -> this will output main.exe
// .\main -> this will run the produced main.exe

void handleInput(std::string prompt, std::string &input)
{
    std::cout << prompt;
    std::getline(std::cin, input);
}

std::string handleExpectedInput(std::string prompt, std::string &errorMessage, std::vector<std::string> &expectedInputs)
{
    bool invalidInput = true;
    std::string input = "";
    while (invalidInput)
    {
        handleInput(input, prompt);
        invalidInput = (std::find(expectedInputs.begin(), expectedInputs.end(), input) == expectedInputs.end()); // test that final element does not trigger failure
        if (invalidInput)
            std::cout << errorMessage << std::endl;
    }
    return input;
}

bool battleTest(std::vector<Hero> &heroParty, std::vector<BasicAction> &basicActions)
{
    std::cout << " * * * BATTLE START ! * * * " << std::endl;
    // std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); // https://cplusplus.com/forum/beginner/79497/

    // start the battle loop
    bool completed = false;
    // bool won = false;
    int turnCount = 0;

    // std::sort(heroParty.begin(), heroParty.end());
    do
    {
        turnCount++;

        // std::vector<std::string> turnInputs = {};
        std::vector<chordinate::Note> notes = {};
        for (chordinate::Hero &hero : heroParty)
        {
            // display info for all heroes:
            // std::cout << hero.displayInfo() << std::endl;
            // std::cout << " * " + hero.getName() + " assumed a battle stance!" << std::endl;

            std::string input = "";
            handleInput("\r\nWhat will " + hero.getName() + " do?\r\n> ", input);

            // expected inputs: ATTACK <target>, DEFEND <target>, SUPPORT <target>

            // turnInputs.push_back(hero.getName() + ":\t" + input + "\r\n");
            chordinate::Note note = chordinate::Note(hero, basicActions[0]);
            notes.push_back(note);
        }
        std::cout << std::endl;

        // std::sort(notes.begin(), notes.end(), chordinate::Note::speedSort);
        for (chordinate::Note note : notes)
        {
            std::cout << " * " + note.getConsoleDisplay() << std::endl;
            // debug: test modifying the hero values, make sure that the party vars are modified as well
            note.testHeroMod();
        }

        completed = (turnCount >= 2); // DEBUG TURN LIMITER
    } while (!completed);

    // won = completed;
    // std::string status = won ? "WON !" : "FAILED...";
    // std::cout << "\r\n * * * YOU " + status + " * * * \r\n" << std::endl;
    std::cout << "\r\n * * * BATTLE COMPLETE ! * * * \r\n"
              << std::endl;

    return completed;
}

int main()
{
    // // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ Extension!"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;

    // todo:
    // pick a battle scenario
    // run the battle or quit
    // std::cout << "Enter anything to start.\r\n> ";

    // std::string test;
    // std::cin >> test; // I suspect that crossing the lines between std::getline and std::cin causes issues

    chordinate::Hero
        flaire = chordinate::Hero(4, 5, 3, "FLAIRE", Voice::Soprano, 35, 8, 8, 20, 5),
        dew = chordinate::Hero(2, 5, 2, "DEW", Voice::Alto, 30, 8, 12, 15, 5),
        waft = chordinate::Hero(1, 5, 1, "WAFT", Voice::Tenor, 45, 10, 10, 10, 20),
        dust = chordinate::Hero(3, 5, 4, "DUST", Voice::Bass, 60, 15, 15, 5, 5);
    std::vector<chordinate::Hero> party = {flaire, dew, waft, dust};

    chordinate::BasicAction
        attack = chordinate::BasicAction("ATTACK", "attacks!", ActionType::A, ActionTargetType::SingleFoe),
        defend = chordinate::BasicAction("DEFEND", "assumes a defensive stance!", ActionType::D, ActionTargetType::SingleAllyOrSelf),
        support = chordinate::BasicAction("SUPPORT", "prepares to assist!", ActionType::S, ActionTargetType::SingleAlly);
    std::vector<chordinate::BasicAction> basicActions = {attack, defend, support};

    // todo: how to bind these together... a static Party object?

    // C++ Reference: object&
    for (chordinate::Hero &hero : party)
    {
        // display info for all heroes:
        std::cout << hero.displayInfo() << std::endl;
    }

    battleTest(party, basicActions);

    // std::cout << waft.displayInfo() << std::endl;
    // e.g. 'What will Waft do? 'input: >'1 > 1'

    // select battle (i.e., party of monsters to fight) -> first, just some dummies that don't fight back
    // begin the battle
    //  > go through each character and pick an action for the turn (options: attack, defend, support)
    //  > after each character's action is picked, run the turn
    //      > after each action plays during the turn, check victory conditions and end battle if one is met

    // bool run = true;
    // while (true) {
    //      run = false;
    // }

    // DOUBLE TESTING
    for (chordinate::Hero &hero : party)
    {
        // display info for all heroes:
        std::cout << hero.displayInfo() << std::endl;
    }

    std::cout << "Execution complete!" << std::endl;
    // std::cout << test << std::endl;
}