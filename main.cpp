#include <iostream>
using namespace std;

#include "linkedList.h"

class Character {
public:

    Character() {}
    Character(string name, int health, int magic) {
        this->name = name;
        this->health = health;
        this->magic = magic;
    }

    string name;
    int health;
    int magic;

    Character* before = NULL;
    Character* after = NULL;
};

string image(Character* character) {
    string border = "====================================\n";
    string name   = "Charater name:   \t" +           character->name    + "\n";
    string health = "Character health:\t" + to_string(character->health) + "\n";
    string magic  = "Character magic: \t" + to_string(character->magic)  + "\n";
    return border + name + health + magic + border;
}

int main() {

    LinkedList<Character> characters;

    characters.insert(new Character("Dragon", 250, 98), 0);
    characters.push_back(new Character("Slime", 45, 32));
    characters.push_back(new Character("Warlock", 132, 876));

    characters[0]->name = "Duckling";
    characters[2]->health = 2891177;
    
    for(int i = 0; i < characters.size(); i++) {
        cout << image(characters[i]) << endl;
    }

    cout << characters[0]->name << endl;
    
    
    return 0;
}
