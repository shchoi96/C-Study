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
		cout << "되돌렸습니다.\n";
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
		cout << "아무 동작도 하지 않습니다.\n";
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
		case 's': // Actor를 한 칸 아래로 이동
			return new MoveUnitCommand(actor, actor->x, actor->y + 1);
		case 'w': // Actor를 한 칸 위로 이동
			return new MoveUnitCommand(actor, actor->x, actor->y - 1);
		case 'd': // Actor를 한 칸 오른쪽으로 이동
			return new MoveUnitCommand(actor, actor->x + 1, actor->y);
		case 'a': // Actor를 한 칸 왼쪽으로 이동
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
	// 필요한 변수 선언
	InputHandler inputHandler;
	GameActor actor;
	stack<Command*> commands;
	Command* command;
	int count = 0;

	// 명령 수행
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