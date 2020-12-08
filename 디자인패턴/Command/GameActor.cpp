#include "GameActor.h"
#include <iostream>

void GameActor::Skill1()
{
	std::cout << "Skill1 사용 \n";
}

void GameActor::Skill2()
{
	std::cout << "Skill2 사용 \n";
}

void GameActor::Skill3()
{
	std::cout << "Skill3 사용 \n";
}

void GameActor::Skill4()
{
	std::cout << "Skill4 사용 \n";
}

void GameActor::Attack()
{
	std::cout << "공격 \n";
}

void GameActor::moveTo(int x, int y)
{
	this->x = x;
	this->y = y;
	std::cout << "( " << x << ", " << y << ") 로 이동했습니다.\n";
}

GameActor::GameActor(int x, int y) : x(x), y(y)
{
	std::cout << "현재 위치는 ( " << x << ", " << y << ") 입니다.\n";
}