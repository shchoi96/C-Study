#include "GameActor.h"
#include <iostream>

void GameActor::Skill1()
{
	std::cout << "Skill1 ��� \n";
}

void GameActor::Skill2()
{
	std::cout << "Skill2 ��� \n";
}

void GameActor::Skill3()
{
	std::cout << "Skill3 ��� \n";
}

void GameActor::Skill4()
{
	std::cout << "Skill4 ��� \n";
}

void GameActor::Attack()
{
	std::cout << "���� \n";
}

void GameActor::moveTo(int x, int y)
{
	this->x = x;
	this->y = y;
	std::cout << "( " << x << ", " << y << ") �� �̵��߽��ϴ�.\n";
}

GameActor::GameActor(int x, int y) : x(x), y(y)
{
	std::cout << "���� ��ġ�� ( " << x << ", " << y << ") �Դϴ�.\n";
}