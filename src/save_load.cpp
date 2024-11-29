#include "save_load.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, const User& user, bool weapon, int armor) {
    ofstream save_file(user_id + "_game_save.txt");

    if (save_file.is_open()) {
        for (const auto& row : map) {
            for (int cell : row) save_file << cell << " ";
            save_file << endl;
        }
        save_file << user_x << " " << user_y << endl;
        save_file << user.GetHP() << endl;
        save_file << weapon << " " << armor << endl;
        save_file << user.GetCharacterType() << endl;

        save_file.close();
    }
}

bool loadGame(const string& user_id, vector<vector<int>>& map, int& user_x, int& user_y, User& user, bool& weapon, int& armor) {
    ifstream load_file(user_id + "_game_save.txt");

    if (!load_file.is_open()) return false;

    for (auto& row : map)
        for (int& cell : row) load_file >> cell;

    load_file >> user_x >> user_y;
    int hp;
    load_file >> hp;
    user.IncreaseHP(hp - user.GetHP());
    load_file >> weapon >> armor;

    string characterType;
    load_file >> characterType;
    user.Initialize(characterType);

    load_file.close();
    return true;
}
