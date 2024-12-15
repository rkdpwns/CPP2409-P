#include "enemy.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Enemy goblin("Goblin", 10, 5, 2);
Enemy orc("Orc", 20, 8, 5);
Enemy dragon("Dragon", 50, 15, 10);

Enemy::Enemy(const string& name, int hp, int attack, int defense)
    : name(name), hp(hp), attack(attack), defense(defense) {}
Enemy CreateRandomEnemy() {
    int random = rand() % 3; // 0, 1, 2 중 랜덤 선택
    if (random == 0) return goblin;
    else if (random == 1) return orc;
    else return dragon;
}

string Enemy::GetName() const {
    return name;
}

int Enemy::GetHP() const {
    return hp;
}

int Enemy::GetAttack() const {
    return attack;
}

int Enemy::GetDefense() const {
    return defense;
}

void Enemy::TakeDamage(int damage, bool ignoreDefense) {
    int effectiveDamage;

    if (ignoreDefense) {
        effectiveDamage = damage; // 방어력 무시
    } else {
        effectiveDamage = max(1, damage - defense); // 방어력 고려
    }

    hp -= effectiveDamage;
    cout << name << "이(가) " << effectiveDamage << " 피해를 입었습니다! 남은 HP: " << hp << endl;
}


bool Enemy::IsAlive() const {
    return hp > 0;
}
