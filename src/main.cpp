#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include <fstream>
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int user_y, int mapX, int mapY);
void displayMap(const vector<vector<int>>& map, int user_x, int user_y);
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y);
void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user, bool& weapon, int& armor, int prev_x, int prev_y);
bool CheckUser(User user);
void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, const User& user, bool weapon, int armor);
bool loadGame(const string& user_id, vector<vector<int>>& map, int& user_x, int& user_y, User& user, bool& weapon, int& armor);

int main() {
    string user_id;
    cout << "사용자 ID를 입력하세요: ";
    cin >> user_id;

    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    int user_x = 0;
    int user_y = 0;
    bool weapon = false;
    int armor = 0;

    User user;  // User 객체 생성

    // 게임 로드
    if (loadGame(user_id, map, user_x, user_y, user, weapon, armor)) {
        cout << "저장된 게임을 불러옵니다." << endl;
    }
    else {
        cout << "새로운 게임을 시작합니다." << endl;
    }

    while (true) {
        string user_input;
        cout << "명령어를 입력하세요 (up,down,left,right,map,inventory,save,exit): ";
        cin >> user_input;

        int prev_x = user_x;
        int prev_y = user_y;

        if (user_input == "up") {
            user_y -= 1;
            if (!checkXY(user_x, user_y, mapX, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y = prev_y;
            }
            else {
                user.DecreaseHP(1);  // 체력 감소
                cout << "위로 한 칸 올라갑니다. 남은 HP: " << user.GetHP() << endl;
                displayMap(map, user_x, user_y);
            }
        }
        else if (user_input == "down") {
            user_y += 1;
            if (!checkXY(user_x, user_y, mapX, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y = prev_y;
            }
            else {
                user.DecreaseHP(1);  // 체력 감소
                cout << "아래로 한 칸 내려갑니다. 남은 HP: " << user.GetHP() << endl;
                displayMap(map, user_x, user_y);
            }
        }
        else if (user_input == "left") {
            user_x -= 1;
            if (!checkXY(user_x, user_y, mapX, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x = prev_x;
            }
            else {
                user.DecreaseHP(1);  // 체력 감소
                cout << "왼쪽으로 이동합니다. 남은 HP: " << user.GetHP() << endl;
                displayMap(map, user_x, user_y);
            }
        }
        else if (user_input == "right") {
            user_x += 1;
            if (!checkXY(user_x, user_y, mapX, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x = prev_x;
            }
            else {
                user.DecreaseHP(1);  // 체력 감소
                cout << "오른쪽으로 이동합니다. 남은 HP: " << user.GetHP() << endl;
                displayMap(map, user_x, user_y);
            }
        }
        else if (user_input == "map") {
            displayMap(map, user_x, user_y);
        }
        else if (user_input == "inventory") {
            user.DisplayInventory(); // 인벤토리 출력
        } else if (user_input.rfind("use", 0) == 0) { // "use 포션"과 같은 명령
            if (user_input.length() > 4) {
                string item = user_input.substr(4); // 명령어 뒤의 아이템 이름 추출
                user.UseItem(item);
            } else {
                cout << "사용할 아이템의 이름을 입력해주세요! (예: use 포션)" << endl;
            }
        }

        else if (user_input == "exit") {
            cout << "게임을 종료합니다." << endl;
            break;
        }
        else if (user_input == "save") {
            saveGame(user_id, map, user_x, user_y, user, weapon, armor);
            cout << "게임 상태가 저장되었습니다." << endl;
        }
        
        else {
            cout << "잘못된 입력입니다." << endl;
        }

        if (user_x != prev_x || user_y != prev_y) {
            checkState(map, user_x, user_y, user, weapon, armor, prev_x, prev_y);
        }

        if (!CheckUser(user)) {
            cout << "체력이 0 이하입니다. 게임이 종료됩니다." << endl;
            break;
        }

        if (checkGoal(map, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            break;
        }
        else if (user_input == "exit") {
            saveGame(user_id, map, user_x, user_y, user, weapon, armor);
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    return 0;
}

void displayMap(const vector<vector<int>>& map, int user_x, int user_y) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (i == user_y && j == user_x) {
                cout << " USER |";
            }
            else {
                switch (map[i][j]) {
                case 0: cout << "      |"; break;
                case 1: cout << "아이템|"; break;
                case 2: cout << "  적  |"; break;
                case 3: cout << " 포션 |"; break;
                case 4: cout << "목적지|"; break;
                }
            }
        }
        cout << endl;
        cout << " -------------------------------- " << endl;
    }
}

void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, const User& user, bool weapon, int armor) {
    ofstream save_file(user_id + "_game_save.txt");

    if (save_file.is_open()) {
        // 맵 저장
        for (const auto& row : map) {
            for (int cell : row) {
                save_file << cell << " ";
            }
            save_file << endl;
        }
        // 플레이어 상태 저장
        save_file << user_x << " " << user_y << endl;
        save_file << user.GetHP() << endl;
        save_file << weapon << " " << armor << endl;

        save_file.close();
    }
}

bool loadGame(const string& user_id, vector<vector<int>>& map, int& user_x, int& user_y, User& user, bool& weapon, int& armor) {
    ifstream load_file(user_id + "_game_save.txt");

    if (!load_file.is_open()) return false;

    // 맵 로드
    for (auto& row : map) {
        for (int& cell : row) {
            load_file >> cell;
        }
    }
    // 플레이어 상태 로드
    load_file >> user_x >> user_y;
    int hp;
    load_file >> hp;
    user.IncreaseHP(hp - user.GetHP());  // HP 초기화
    load_file >> weapon >> armor;

    load_file.close();
    return true;
}

bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return map[user_y][user_x] == 4;
}

void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user, bool& weapon, int& armor, int prev_x, int prev_y) {
    if (user_x == prev_x && user_y == prev_y) return;

    switch (map[user_y][user_x]) {
        case 1:
            if (rand() % 2 == 0) {
                user.AddItem("무기");
            } else {
                user.AddItem("갑옷");
            }
            break;
        case 2:
            cout << "적을 만났습니다! ";
            if (armor > 0) {
                armor--;
                cout << "갑옷으로 적의 공격을 막았습니다. 남은 갑옷: " << armor << endl;
            } else if (weapon) {
                user.DecreaseHP(1);
                cout << "무기로 적을 베었습니다. HP -1. 현재 HP: " << user.GetHP() << endl;
            } else {
                user.DecreaseHP(2);
                cout << "적에게 공격당했습니다. HP -2. 현재 HP: " << user.GetHP() << endl;
            }
            break;
        case 3:
            user.AddItem("포션");
            break;
    }
}


bool CheckUser(User user) {
    return user.GetHP() > 0;
}

bool checkXY(int user_x, int user_y, int mapX, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}
