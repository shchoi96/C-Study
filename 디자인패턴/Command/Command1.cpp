#include <iostream>
#include <conio.h>
#include "GameActor.h"

using namespace std;

class Command
{
public:
	virtual void execute(GameActor& actor) = 0;
	virtual ~Command() {}
};

class AttackCommand : public Command
{
public:
	virtual void execute (GameActor& actor)
	{
		actor.Attack();
	}
};

class Skill1Command : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.Skill1();
	}
};

class Skill2Command : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.Skill2();
	}
};

class Skill3Command : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.Skill3();
	}
};

class Skill4Command : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		actor.Skill4();
	}
};

class NullCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		cout << "아무 동작도 하지 않습니다.\n";
	}
};

class InputHandler
{
public:
	Command* button_Q;
	Command* button_W;
	Command* button_E;
	Command* button_R;
	Command* button_A;

	Command* handleInput(int pressed)
	{
		switch (pressed)
		{
		case 'q':
		case 'Q':
			return button_Q;
		case 'w':
		case 'W':
			return button_W;
		case 'e':
		case 'E':
			return button_E;
		case 'r':
		case 'R':
			return button_R;
		case 'a':
		case 'A':
			return button_A;
		}

		return new NullCommand();
	}
};

bool getkey();
void ChangeButton(Command** A, Command** B);
int pressed;

int main()
{
	// 필요한 변수 선언
	InputHandler inputHandler;
	GameActor actor;
	Command* command;
	int count = 0;

	// 기본 키 세팅
	inputHandler.button_A = new AttackCommand();
	inputHandler.button_Q = new Skill1Command();
	inputHandler.button_W = new Skill2Command();
	inputHandler.button_E = new Skill3Command();
	inputHandler.button_R = new Skill4Command();

	// 명령 수행
	while (getkey() && count++ < 10)
	{
		command = inputHandler.handleInput(pressed);
		command->execute(actor);
	}

	// 키 세팅 수정. 명령 변환
	cout << "세팅 변환 \n";
	ChangeButton(&inputHandler.button_A, &inputHandler.button_Q);
	ChangeButton(&inputHandler.button_W, &inputHandler.button_R);

	// 명령 수행
	count = 0;
	while (getkey() && count++ < 10)
	{
		command = inputHandler.handleInput(pressed);
		command->execute(actor);
	}

	return 0;
}


bool getkey()
{
	pressed = _getch();
	if (pressed == 27) // ESC 누르면 종료
		return false;
	cout << "입력 : " << (char)pressed << '\n';
	return true;
}

void ChangeButton(Command** A, Command** B)
{
	Command* temp = *A;
	*A = *B;
	*B = temp;
}