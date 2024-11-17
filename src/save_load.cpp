#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 맵과 사용자 상태를 저장
void saveGame(const string& user_id, const vector<vector<int>>& map, int user_x, int user_y, int user_hp, bool weapon, int armor) {
    string filename = user_id + "_game_save.txt";

    ofstream save_file(filename);

    if (save_file.is_open()) {
        // 맵 데이터 저장
        for (const auto& row : map) {
            for (int cell : row) {
                save_file << cell << " "; 
            }
            save_file << endl;
        }

        // 사용자 위치
        save_file << user_x << " " << user_y << endl;
        // 사용자 체력
        save_file << user_hp << endl;
        // 무기 갑옷 상태
        save_file << weapon << " " << armor << endl;

        save_file.close();
        cout << "게임 상태가 '" << filename << "' 파일에 저장되었습니다." << endl;
    }
    else {
        cout << "파일 저장에 실패했습니다!" << endl;
    }
}
