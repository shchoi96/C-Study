#ifndef __GAMEACTOR_H__
#define __GAMEACTOR_H__
#include <iostream>

class GameActor
{
public:
	int x;
	int y;
	void Skill1();
	void Skill2();
	void Skill3();
	void Skill4();
	void Attack();
	void moveTo(int x, int y);

	GameActor(int x = 0, int y = 0);

};

#endif // !__GAMEACTOR_H__
