#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class User {
private:
    int hp;
    unordered_map<string, int> inventory; // 아이템 저장

public:
    User();
    void DecreaseHP(int dec_hp);
    void IncreaseHP(int inc_hp);
    int GetHP() const;

    // 인벤토리
    void AddItem(const string& item);
    void UseItem(const string& item);
    void DisplayInventory() const;
};

#endif
