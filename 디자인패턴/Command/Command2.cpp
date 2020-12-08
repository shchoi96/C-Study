#include <iostream>
#include <stack>
#include <conio.h>
#include "GameActor.h"

using namespace std;

class Command
{
public:
	virtual void execute(GameActor& actor) = 0;
	virtual void undo() = 0;
	virtual ~Command() {}
};

class MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(GameActor* actor, int x, int y) : actor(actor), x(x), y(y), xBefore(0), yBefore(0) {}
	
	virtual void execute(GameActor& actor)
	{
		xBefore = actor.x;
		yBefore = actor.y;
		actor.moveTo(x, y);
	}

	virtual void undo()
	{
		cout << "�ǵ��Ƚ��ϴ�.\n";
		actor->moveTo(xBefore, yBefore);
	}

private:
	GameActor* actor;
	int x;
	int y;
	int xBefore;
	int yBefore;
};

class NullCommand : public Command
{
public:
	virtual void execute(GameActor& actor)
	{
		cout << "�ƹ� ���۵� ���� �ʽ��ϴ�.\n";
	}
	virtual void undo() {}
};

class InputHandler
{
public:
	Command* handleInput(GameActor* actor, int pressed)
	{
		switch (pressed)
		{
		case 's': // Actor�� �� ĭ �Ʒ��� �̵�
			return new MoveUnitCommand(actor, actor->x, actor->y + 1);
		case 'w': // Actor�� �� ĭ ���� �̵�
			return new MoveUnitCommand(actor, actor->x, actor->y - 1);
		case 'd': // Actor�� �� ĭ ���������� �̵�
			return new MoveUnitCommand(actor, actor->x + 1, actor->y);
		case 'a': // Actor�� �� ĭ �������� �̵�
			return new MoveUnitCommand(actor, actor->x - 1, actor->y);
		}
		// Null Object
		return new NullCommand();
	}
};

bool getkey();
int pressed;

int main()
{
	// �ʿ��� ���� ����
	InputHandler inputHandler;
	GameActor actor;
	stack<Command*> commands;
	Command* command;
	int count = 0;

	// ��� ����
	while (getkey() && count++ < 10)
	{
		command = inputHandler.handleInput(&actor, pressed);
		command->execute(actor);
		commands.push(command);
	}

	// undo
	while (!commands.empty())
	{
		command = commands.top();
		command->undo();
		commands.pop();
	}
	return 0;
}

bool getkey()
{
	pressed = _getch();
	if (pressed == 27) // ESC ������ ����
		return false;
	cout << "�Է� : " << (char)pressed << '\n';
	return true;
}

void ChangeButton(Command** A, Command** B)
{
	Command* temp = *A;
	*A = *B;
	*B = temp;
}