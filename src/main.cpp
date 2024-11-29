#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "save_load.h"
#include "game_logic.h"

using namespace std;

int main() {
    string user_id;
    cout << "사용자 ID를 입력하세요: ";
    cin >> user_id;

    User user;
    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    int user_x = 0, user_y = 0;
    bool weapon = false;
    int armor = 0;

    // 게임 로드
    if (loadGame(user_id, map, user_x, user_y, user, weapon, armor)) {
        cout << "저장된 게임을 불러옵니다." << endl;
    } else {
        cout << "새로운 게임을 시작합니다." << endl;
        selectUserClass(user);  // 직업 선택
    }

    displayMap(map, user_x, user_y);

    while (true) {
        string command;
        cout << "명령어를 입력하세요 (up, down, left, right, map, inventory, save, exit): ";
        cin >> command;

        if (command == "exit") {
            cout << "게임을 종료합니다." << endl;
            saveGame(user_id, map, user_x, user_y, user, weapon, armor);
            break;
        }

        if (command == "up" || command == "down" || command == "left" || command == "right") {
            if (moveUser(user_x, user_y, command, mapX, mapY, user)) {
                checkState(map, user_x, user_y, user, weapon, armor);
                if (!CheckUser(user)) {
                    cout << "체력이 0입니다. 게임 종료." << endl;
                    break;
                }
                if (checkGoal(map, user_x, user_y)) {
                    cout << "목적지에 도착했습니다! 축하합니다!" << endl;
                    break;
                }
            }
        } else {
            processCommand(command, user_x, user_y, map, user, weapon, armor);
        }
        displayMap(map, user_x, user_y);
    }

    return 0;
}
