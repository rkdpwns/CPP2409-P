#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class User {
private:
    int hp;
    string characterType; // 전사 또는 마법사
    unordered_map<string, int> inventory; // 인벤토리
    bool armor_active;

public:
    const unordered_map<string, int>& GetInventory() const; // 인벤토리 반환
    void SetInventoryItem(const string& item, int count);   // 아이템 설정
    User();
    void Initialize(const string& type); // 캐릭터 초기화
    void DecreaseHP(int dec_hp);
    void IncreaseHP(int inc_hp);
    int GetHP() const;
    int GetInventoryCount(const string& item) const;
    string GetCharacterType() const;

    // 인벤토리 관련 함수
    void AddItem(const string& item); // 아이템 추가
    void UseItem(const string& item);
    void DisplayInventory() const;
    void ActivateArmor(); // 갑옷 활성화
    bool IsArmorActive() const { return armor_active; }  
    void DeactivateArmor() { armor_active = false; }  
    
};

#endif
