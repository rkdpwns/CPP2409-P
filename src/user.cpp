#include "user.h"
#include <iostream>
using namespace std;

User::User() : hp(20) {}

void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
    if (hp < 0) hp = 0;
}

void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int User::GetHP() const {
    return hp;
}

//아이템 추가
void User::AddItem(const string& item) {
    inventory[item]++;
    cout << item << "을(를) 획득했습니다! 현재 수량: " << inventory[item] << endl;
}

//아이템 사용
void User::UseItem(const string& item) {
    if (inventory[item] > 0) {
        inventory[item]--;
        cout << item << "을(를) 사용했습니다. 남은 수량: " << inventory[item] << endl;

        if (item == "포션") {
            IncreaseHP(5);
            cout << "포션 사용으로 HP +5. 현재 HP: " << GetHP() << endl;
        }
    } else {
        cout << item << "이(가) 인벤토리에 없습니다!" << endl;
    }
}

// 인벤토리 표시
void User::DisplayInventory() const {
    cout << "=== 인벤토리 ===" << endl;
    for (const auto& pair : inventory) {
        cout << pair.first << ": " << pair.second << endl;
    }
    cout << "================" << endl;
}
