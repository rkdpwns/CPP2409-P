#include "game_logic.h"
#include "save_load.h"
#include "enemy.h"
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
    static Enemy currentEnemy = CreateRandomEnemy(); // 전투 시작 시 랜덤 적 생성

    // 적과의 전투
    if (map[user_y][user_x] == 2) { // 적 칸
        cout << currentEnemy.GetName() << "과(와) 전투가 시작되었습니다!" << endl;
        cout << "적 정보 - HP: " << currentEnemy.GetHP() 
             << ", 공격력: " << currentEnemy.GetAttack() 
             << ", 방어력: " << currentEnemy.GetDefense() << endl;

        while (currentEnemy.IsAlive() && user.GetHP() > 0) {
            // 플레이어 행동 선택
            cout << "행동을 선택하세요 (attack, skill, run): ";
            string action;
            cin >> action;

            if (action == "attack") {
                // 기본 공격
                int playerAttack = 10; // 플레이어 기본 공격력
                currentEnemy.TakeDamage(playerAttack);
                cout << currentEnemy.GetName() << "에게 " << playerAttack << " 피해를 입혔습니다!" << endl;
                cout << currentEnemy.GetName() << "의 남은 HP: " << currentEnemy.GetHP() << endl;
            } else if (action == "skill") {
                // 스킬 사용
                if (user.GetCharacterType() == "warrior") {
                    cout << "전사의 스킬 '베기'를 사용했습니다!" << endl;
                    currentEnemy.TakeDamage(15); // 전사 스킬 데미지
                } else if (user.GetCharacterType() == "mage") {
                    cout << "마법사의 스킬 '라이트닝 볼트'를 사용했습니다!" << endl;
                    currentEnemy.TakeDamage(20); // 마법사 스킬 데미지
                }
                cout << currentEnemy.GetName() << "의 남은 HP: " << currentEnemy.GetHP() << endl;
            } else if (action == "run") {
                // 도망
                cout << "전투에서 도망쳤습니다!" << endl;
                return; // 전투 종료
            } else {
                cout << "알 수 없는 명령입니다. 다시 선택하세요." << endl;
                continue;
            }

            // 적의 공격
            if (currentEnemy.IsAlive()) {
                int enemyDamage = currentEnemy.GetAttack();
                user.DecreaseHP(enemyDamage);
                cout << currentEnemy.GetName() << "이(가) 공격합니다! 플레이어가 " << enemyDamage << " 피해를 입었습니다." << endl;
                cout << "현재 HP: " << user.GetHP() << endl;
            }
        }

        // 전투 종료
        if (!currentEnemy.IsAlive()) {
            cout << currentEnemy.GetName() << "을(를) 물리쳤습니다!" << endl;
            map[user_y][user_x] = 0; // 적 제거
        } else if (user.GetHP() <= 0) {
            cout << "플레이어가 사망했습니다. 게임 종료." << endl;
            exit(0); // 게임 종료
        }
    }

    // 아이템 발견
    if (map[user_y][user_x] == 1) { // 아이템 칸
        cout << "아이템을 발견했습니다!" << endl;
        user.AddItem("armor"); // 갑옷 아이템 추가
        map[user_y][user_x] = 0; // 맵에서 해당 칸을 빈칸으로 변경
    }

    // 포션 발견
    else if (map[user_y][user_x] == 3) { // 포션 칸
        cout << "포션을 발견했습니다!" << endl;
        user.AddItem("potion"); // 포션 아이템 추가
        map[user_y][user_x] = 0; // 맵에서 해당 칸을 빈칸으로 변경
    }
}



void processCommand(const string& command, int& user_x, int& user_y, vector<vector<int>>& map, User& user, bool& weapon, int& armor) {
    if (command == "inventory") {
        user.DisplayInventory(); // 인벤토리 출력

        cout << "아이템을 사용하시겠습니까? (yes/no): ";
        string choice;
        cin >> choice;

        if (choice == "yes") {
            cout << "사용할 아이템 이름을 입력하세요 (armor/potion): ";
            string item;
            cin >> item;

            if (item == "armor") {
                user.UseItem("armor"); // 갑옷 사용
            } else if (item == "potion") {
                user.UseItem("potion"); // 포션 사용
            } else {
                cout << "알 수 없는 아이템입니다!" << endl;
            }
        }
    } else if (command == "map") {
        displayMap(map, user_x, user_y);
    } else if (command == "save") {
        saveGame("user_id", map, user_x, user_y, user, weapon, armor);
        cout << "게임 상태가 저장되었습니다." << endl;
    } else {
        cout << "알 수 없는 명령입니다!" << endl;
    }
}
