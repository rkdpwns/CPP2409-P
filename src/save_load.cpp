#include "save_load.h"
#include "user.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, const User& user, bool weapon, int armor) {
    ofstream save_file(user_id + "_game_save.txt");

    if (save_file.is_open()) {
        // 맵 저장
        for (const auto& row : map) {
            for (int cell : row) save_file << cell << " ";
            save_file << endl;
        }

        // 플레이어 상태 저장
        save_file << user_x << " " << user_y << endl;
        save_file << user.GetHP() << endl;
        save_file << weapon << " " << armor << endl;
        save_file << user.GetCharacterType() << endl;

        // 인벤토리 저장
        const unordered_map<string, int>& inventory = user.GetInventory();
        save_file << inventory.size() << endl; // 인벤토리 항목 수
        for (const auto& item : inventory) {
            save_file << item.first << " " << item.second << endl; // 아이템 이름과 수량
        }

        save_file.close();
        cout << "게임이 성공적으로 저장되었습니다." << endl;
    } else {
        cout << "파일 저장에 실패했습니다!" << endl;
    }
}



bool loadGame(const string& user_id, vector<vector<int>>& map, int& user_x, int& user_y, User& user, bool& weapon, int& armor) {
    ifstream load_file(user_id + "_game_save.txt");

    if (!load_file.is_open()) {
        cout << "세이브 파일을 찾을 수 없습니다!" << endl;
        return false;
    }

    // 맵 로드
    for (auto& row : map)
        for (int& cell : row) load_file >> cell;

    // 플레이어 상태 로드
    load_file >> user_x >> user_y;
    int hp;
    load_file >> hp;
    user.IncreaseHP(hp - user.GetHP());
    load_file >> weapon >> armor;

    string characterType;
    load_file >> characterType;
    user.Initialize(characterType);

    // 인벤토리 로드
    int inventory_size;
    load_file >> inventory_size;
    for (int i = 0; i < inventory_size; ++i) {
        string item_name;
        int item_count;
        load_file >> item_name >> item_count;
        user.SetInventoryItem(item_name, item_count); // 아이템 설정
    }

    load_file.close();
    cout << "게임이 성공적으로 불러와졌습니다." << endl;
    return true;
}
