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
    if (inventory[item] > 0) {
        inventory[item]--;
        if (item == "armor") {
            ActivateArmor(); // 갑옷 활성화
        } else if (item == "potion") {
            IncreaseHP(20); // 포션 사용 시 체력 회복
            cout << "포션 사용으로 HP +20. 현재 HP: " << GetHP() << endl;
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

void User::ActivateArmor() {
    armor_active = true; // 갑옷 활성화
    cout << "갑옷을 착용했습니다! 적의 공격을 방어할 수 있습니다." << endl;
}

void User::DeactivateArmor() {
    armor_active = false; // 갑옷 비활성화
    cout << "갑옷이 파괴되었습니다." << endl;
}

bool User::IsArmorActive() const {
    return armor_active; // 갑옷 상태 반환
}

const unordered_map<string, int>& User::GetInventory() const {
    return inventory; // 인벤토리 반환
}

void User::SetInventoryItem(const string& item, int count) {
    inventory[item] = count; // 아이템 설정
}
