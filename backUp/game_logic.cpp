#include "game_logic.h"
#include "save_load.h"
#include <iostream>
using namespace std;

void displayMap(const vector<vector<int>>& map, int user_x, int user_y) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (i == user_y && j == user_x) cout << " USER |";
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
        cout << "---------------------------------" << endl;
    }
}
bool checkXY(int user_x, int user_y, int mapX, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}


bool moveUser(int& user_x, int& user_y, const string& direction, int mapX, int mapY, User& user) {
    int prev_x = user_x;
    int prev_y = user_y;

    if (direction == "up") user_y -= 1;
    else if (direction == "down") user_y += 1;
    else if (direction == "left") user_x -= 1;
    else if (direction == "right") user_x += 1;
    else return false; // 잘못된 방향 입력 처리

    if (!checkXY(user_x, user_y, mapX, mapY)) {
        cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
        user_x = prev_x;
        user_y = prev_y;
        return false;
    }

    user.DecreaseHP(1);
    cout << direction << " 방향으로 이동했습니다. 남은 HP: " << user.GetHP() << endl;
    return true; // 이동 성공
}


void selectUserClass(User& user) {
    while (true) {
        string choice;
        cout << "직업을 선택하세요 (Warrior/Mage): ";
        cin >> choice;
        if (choice == "Warrior" || choice == "Mage") {
            user.Initialize(choice);
            break;
        }
        cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
    }
}

bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return map[user_y][user_x] == 4; // 목표 위치
}

bool CheckUser(const User& user) {
    return user.GetHP() > 0;
}

void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user, bool& weapon, int& armor) {
    if (map[user_y][user_x] == 1) { // 아이템 칸
        cout << "아이템을 발견했습니다!" << endl;
        user.AddItem("아이템");
        map[user_y][user_x] = 0; // 아이템을 빈칸으로 변경
    } else if (map[user_y][user_x] == 2) { // 적 칸
        cout << "적과 전투 중입니다!" << endl;

        if (armor > 0) { // 갑옷이 있으면 갑옷으로 방어
            armor--;
            cout << "갑옷으로 방어했습니다. 남은 갑옷: " << armor << endl;
        } else if (user.GetInventoryCount("아이템") > 0) { // 무기가 있으면 방어
            user.UseItem("아이템");
            cout << "아이템으로 적의 공격을 방어했습니다!" << endl;
        } else { // 갑옷과 무기가 없으면 체력 감소
            user.DecreaseHP(5);
            cout << "체력 감소! 남은 HP: " << user.GetHP() << endl;
        }
    } else if (map[user_y][user_x] == 3) { // 포션 칸
        cout << "포션을 발견했습니다!" << endl;
        user.AddItem("포션");
        map[user_y][user_x] = 0; // 포션 칸을 빈칸으로 변경
    }
}

void processCommand(const string& command, int& user_x, int& user_y, vector<vector<int>>& map, User& user, bool& weapon, int& armor) {
    if (command == "map") {
        displayMap(map, user_x, user_y);
    } else if (command == "inventory") {
        user.DisplayInventory();
    } else if (command.rfind("use ", 0) == 0) { // "use"로 시작하는 명령어 처리
        string item = command.substr(4); // "use " 이후의 문자열을 아이템 이름으로 사용
        user.UseItem(item);
    } else if (command == "save") {
        saveGame("user_id", map, user_x, user_y, user, weapon, armor);
        cout << "게임 상태가 저장되었습니다." << endl;
    } else {
        cout << "알 수 없는 명령입니다!" << endl;
    }
}
