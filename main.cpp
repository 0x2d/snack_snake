#include "snake.h"

bool core(block &food, vector<block> &snack);
bool is_alive(vector<block> &snack);

int main()
{
	while (true)
	{
		char input;
		cout << "=====SNACK SNAKE=====\n，Play game: y\n，Setting: s\n，Help: h\n，Quit: q" << endl;
		cin >> input;
		getchar();
		system("cls");

		if (input == 'y')
		{
			vector<block> snack{ block(3, 9, 'd'), block(2, 9, 'd') };
			class block food;
			char dir;

			while (is_alive(snack))
			{
				create_map(food, snack);
				while (!_kbhit() && is_alive(snack))
				{
					move_snack(snack, snack.front().dir);
					core(food, snack);
					create_map(food, snack);
				}
				if (!is_alive(snack))
					break;

				dir = _getch();
				if (dir == 'a'||dir == 's'||dir == 'd'||dir == 'w')
				{
					move_snack(snack, dir);
					core(food, snack);
				}
				else if (dir == 'p')
				{
					if (_getch() == 'r')
						continue;
				}
				else
					continue;
			}
			cout << "Game over.\nYour score:"<< score << "\n" << endl;
			flag = true, flag_food = false, score = 0;
		}
		else if (input == 's')
		{
			cout << "You can change the speed of the snack by enter a new number. Now the speed is " << speed << "ms.\n" << endl;
			cin >> speed;
			system("cls");
			cout << "Change applied.Now the speed is " << speed << "ms" << endl;
			getchar();
			continue;
		}
		else if (input == 'h')
		{
			cout << "Use 'w' 's' 'a' 'd' to control the movement of the snack.\nUse 'p' to pause when you're in the game, 'r' to resume.\nPress enter..." << endl;
			getchar();
			system("cls");
			continue;
		}
		else if (input == 'q')
			break;
		else
			continue;
	}
	return 0;
}

bool core(block &food, vector<block> &snack)
{
	if (!flag_food)
	{
		create_food(food, snack, score);
		flag_food = true;
	}
	if (snack.front().num() == food.num())
	{
		increase_snack(snack);
		food.x = 0, food.y = 0;
		flag_food = false;
		score++;
	}
	system("cls");
	create_map(food, snack);
	Sleep(speed/4);
	system("cls");
	return true;
}

bool is_alive(vector<block> &snack)
{
	int num = snack.front().num();
	if (find_if(++snack.begin(), snack.end(), [num](block &a) {return a.num() == num; }) != snack.end())
		flag = false;
	return snack.front().x != 0 && snack.front().x != size+1 && snack.front().y != 0 && snack.front().y != size+1 && flag;
}