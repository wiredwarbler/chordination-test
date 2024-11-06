// specification file
// where class/data declarations go
#ifndef chordinate
#define chordinate

#pragma once
#include <string>
#include <vector>

/* ******************************** BASIC/CORE DATA ******************************* */

/* ********* ENUMS ********* */
enum Voice
{
    Soprano = 1,
    Alto = 2,
    Tenor = 3,
    Bass = 4
};
enum StatType
{
    HitPoints = 1,
    Attack = 2,
    Defense = 3,
    Speed = 4,
    Luck = 5
};
enum ActionType
{
    NoAction = 0,
    A = 1,
    D = 2,
    S = 3
};
enum ActionTargetType
{
    MultiFoe = 1,
    MultiAlly = 2,
    SingleFoe = 3,
    SingleAlly = 4,
    SingleAllyOrSelf = 5,
    Self = 6
};
enum ActorState
{
    Normal = 1,
    Down = 2
};
enum ChordType
{
    I = 1,
    ii = 2,
    iii = 3,
    IV = 4,
    V = 5,
    vi = 6,
    vii = 7
};

// todo: enum string mappers

/* ******** CLASSES ******** */
class Stat
{
protected:
    StatType type;
    int max;
    int current;

public:
    Stat(StatType st, int m);
    // Getters
    int getMax();
    int getCurrent();
    std::string getDisplay();
    // Mutators
    void reset();
    void delta(int value);
};

/* ********************************** ACTOR DATA ********************************** */
class Actor
{
protected:
    int id;
    int level;
    std::string name;
    Stat hp;
    Stat attack;
    Stat defense;
    Stat speed;
    Stat luck;
    ActorState state;

public:
    Actor(int i, int lvl, std::string n, int h, int a, int d, int s, int l);
    // Getters
    int getCurrentHP();
    // Mutators
    void deltaHP(int n);
};

class Hero : Actor
{
protected:
    Voice voice;
    int partySequence;

public:
    Hero(int i, int lvl, int ps, std::string n, Voice v, int h, int a, int d, int s, int l);
    // Getters
    std::string displayInfo();
    std::string getName();
    int getSpeed();
    // Mutators / Setters
    void deltaHP(int n);

    // Helper Methods
    bool operator<(const Hero &other) const; // supposedly, you can just make other sort methods and do this: std::sort(heroParty.begin(), heroParty.end(), sortmethod);
};

// class Foe : Actor
// {
// // public:
// //     Foe();
// };

// class Party {
//     // todo: collection of Actors
//     // todo: cumulative, residual chord effects?
// };

/* ******* CHORDINATION ******* */
class BasicAction
{
protected:
    std::string name;
    std::string actorActionText;
    ActionType type;
    ActionTargetType allowedTargetType;
    // int power; // Percent, or Added Power?
    // int accuracy;
    // int critical;
public:
    BasicAction(std::string n, std::string aat, ActionType t, ActionTargetType att);
    std::string getActionText();
};

class Note
{
protected:
    // https://stackoverflow.com/questions/12387239/is-it-idiomatic-to-store-references-members-in-a-class-and-are-there-pitfalls
    Hero &hero; // MUST BE SURE THAT THESE REFERENCES WILL ALWAYS OUTLIVE THIS NOTE OBJ
    BasicAction &action;
    // std::vector<Actor&> targets;
    // std::string actionText;
    int sequence;
    bool attempted;
    bool success;

public:
    Note(Hero &h, BasicAction &a);
    void setAttempted(bool a);
    void setSuccess(bool s);
    int getHeroSpeed();
    std::string getConsoleDisplay();
    // bool speedSort(Note &other);
    void testHeroMod();
};

// class Skill : BasicAction // todo: Action taken versus Action Type, Available Actions
// {
// protected:

// };

// class ChordNote
// {
// protected:
//     Hero* hero;
//     std::vector<Actor*> targets;
// public:

// };

// class Chord
// {
// protected:
//     int id;
//     int circleSequence; // proper sequence of this chord, in the circle
//     int basePercentModifier; // how much this chord affects certain actions
//     ActionType type; // what this chord affects
//     std::string name;
//     std::vector<ChordNote> chordNotes;
// public:
//     Chord();
// };

// class Measure
// {
// protected:
//     Chord chord;
// };

// class Turn
// {
//     // todo: collection/vector of Actions
//     // todo: get produced/determined chord from Action ActionTypes
//     // https://cplusplus.com/reference/vector/vector/
// };

// class Progression {
//     // todo: collection/vector of Turns
//     // resolution -> grand effect/explosion
//     // failed movement -> reset Progression and
// };

#endif