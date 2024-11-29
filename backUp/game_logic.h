#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <string>
#include "user.h"
using namespace std;

const int mapX = 5;
const int mapY = 5;

void displayMap(const vector<vector<int>>& map, int user_x, int user_y);
bool moveUser(int& user_x, int& user_y, const string& direction, int mapX, int mapY, User& user);
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y);
void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user, bool& weapon, int& armor);
bool CheckUser(const User& user);
void processCommand(const string& command, int& user_x, int& user_y, vector<vector<int>>& map, User& user, bool& weapon, int& armor);
void selectUserClass(User& user);
bool checkXY(int user_x, int user_y, int mapX, int mapY); // 추가

#endif
