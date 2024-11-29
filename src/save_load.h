#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>
#include <string>
#include "user.h"
using namespace std;

void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, const User& user, bool weapon, int armor);
bool loadGame(const string& user_id, vector<vector<int>>& map, int& user_x, int& user_y, User& user, bool& weapon, int& armor);

#endif
