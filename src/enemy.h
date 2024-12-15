#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;

class Enemy {
private:
    string name;     // 적 이름
    int hp;          // 체력
    int attack;      // 공격력
    int defense;     // 방어력

public:
    Enemy(const string& name, int hp, int attack, int defense);
    string GetName() const;
    int GetHP() const;
    int GetAttack() const;
    int GetDefense() const;
    void TakeDamage(int damage, bool ignoreDefense = false);
    bool IsAlive() const;
};
Enemy CreateRandomEnemy();

#endif
