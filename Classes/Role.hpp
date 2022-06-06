#pragma once
#include "cocos2d.h"
USING_NS_CC;
struct Bigattack :public Attack{
	Bigattack() :Attack() {}
	Bigattack(int attack_damge, int attack_range, int attack_speed, int attack_distance)
		:Attack(attack_damge, attack_range, attack_speed, attack_distance) {}
};
struct Normalattack :public Attack{
	Normalattack():Attack() {}
	Normalattack(int attack_damge, int attack_range, int attack_speed, int attack_distance)
		:Attack(attack_damge, attack_range, attack_speed, attack_distance){}
};
class Attack {
protected:
	Attack():_damage(0), _range(0), _speed(0), _distance(0){}
	Attack(int attack_damge,int attack_range,int attack_speed,int attack_distance) :
		_damage(attack_damge), _range(attack_range), _speed(attack_speed), _distance(attack_distance) {}
	int _get_damage() const{
		return _damage;
	}
	int _get_range() const{
		return _range;
	}
	int _get_speed() const {
		return _speed;
	}
	int _get_distance() const {
		return _distance;
	}
	void _set_damage(const int &damage) {
		_damage = damage;
	}
	void _set_range(const int& range) {
		_range = range;
	}
	void _set_speed(const int& speed) {
		_speed = speed;
	}
	void _set_distance(const int& distance) {
		_distance = distance;
	}

	//还需要添加攻击动画
private:
	int _damage;
	int _range;
	int _speed;
	int _distance;
};
class Role :public Sprite  {
public:
	Role();
	virtual ~Role()=0;
protected:
	int _get_hp() const{
		return Role::_hp;
	};
	int _get_force() const {
		return _force;
	};
	int _get_defence() const {
		return _defence;
	};
	int _get_speed() const {
		return _speed_walk;
	};
	//int _get_level() {};
	//int _get_exp() {};
	//int _get_money() {};
	void _set_hp(const int &myhp) {
		Role::_hp = myhp;
	}
	void _set_force(const int &myforce) {
		_force = myforce;
	}
	void _set_defence(const int &mydefence) {
		_defence = mydefence;
	}
	void _set_speed_walk(const int &myspeed) {
		_speed_walk = myspeed;
	}
	Bigattack _bigattack;
	Normalattack _normalattack;
private:
	int _hp;
	int _force;
	int _speed_walk;
	int _defence;
	//int _exp;
	//int _level;
	//int _money;
};

