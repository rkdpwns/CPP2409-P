#include "user.h"
#include <iostream>
using namespace std;

User::User() : hp(20), characterType("Unknown") {}

void User::Initialize(const string& type) {
    characterType = type;
    if (type == "Warrior") {
        hp = 30; // 전사는 체력이 높음
    } else if (type == "Mage") {
        hp = 20; // 마법사는 체력이 낮지만 강력한 공격력 가능
    }
    cout << type << "로 설정되었습니다. 초기 HP: " << hp << endl;
}

string User::GetCharacterType() const {
    return characterType;
}

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
int User::GetInventoryCount(const string& item) const {
    auto it = inventory.find(item);
    return (it != inventory.end()) ? it->second : 0;
}


//아이템 추가
void User::AddItem(const string& item) {
    inventory[item]++;
    cout << item << "을(를) 획득했습니다! 현재 수량: " << inventory[item] << endl;
}

//아이템 사용
void User::UseItem(const string& item) {
    if (inventory[item] > 0) { // 인벤토리에 아이템이 있는지 확인
        inventory[item]--; // 아이템 개수 감소
        cout << item << "을(를) 사용했습니다. 남은 수량: " << inventory[item] << endl;

        if (item == "포션") {
            IncreaseHP(3); // 포션 사용 시 체력 3 회복
            cout << "포션 사용으로 HP +3. 현재 HP: " << GetHP() << endl;
            // 아이템 사용은 단순 메시지로 처리. 실제 게임 로직에서 추가 구현 가능.
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
