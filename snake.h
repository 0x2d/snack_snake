#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#define size 15
using namespace std;

int speed = 500, score = 0;
bool flag = true, flag_food = false;

class block{
public:
	block() = default;
	block(int m, int n) :x(m), y(n) {}
	block(int m, int n, char d) :x(m), y(n), dir(d) {}
	int num() const { return (size * (y - 1) + x); };
	int x;
	int y;
	char dir;
};

bool create_food(class block &food, vector<class block> snack, int n);
bool create_map(class block &food, vector<class block> snack);
bool increase_snack(vector<class block> &snack);
bool move_snack(vector<class block> &snack, char d);//friend

bool create_food(class block &food, vector<class block> snack, int n)
{
	srand((unsigned int)time(0) + score*n);
	food.x = (rand() % (size-1)) + 1;
	srand((unsigned int)time(0) + n);
	food.y = (rand() % (size - 1)) + 1;
	for (auto index: snack)
	{
		if (index.num() == food.num())
		{
			if (create_food(food, snack,++n))
				break;
			else
				return false;
		}
	}
	return true;
}

bool create_map(class block &food, vector<class block> snack)
{
	int tempx, tempy, tempnum;
	bool flag_map;
	for (tempy = 1; tempy <= size; tempy++)
	{
		for (tempx = 1; tempx <= size; tempx++)
		{
			tempnum = size * (tempy - 1) + tempx;
			flag_map = false;
			for (auto index: snack)
			{
				if (index.num() == tempnum)
				{
					if (index.dir == 'a' || index.dir == 'd')
						printf("-");
					else
						printf("|");
					flag_map = true;
					break;
				}
			}
			if (flag_map == false)
			{
				if (food.num() == tempnum)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("|\n");
	}
	printf("---------------/\n");
	return true;
}//snack过长时刷新速度明显降低

bool increase_snack(vector<class block> &snack)
{
	auto last = snack.back();
	switch (last.dir)
	{
	case 'w':
		snack.push_back(block(last.x, last.y+1, 'w'));
		break;
	case 'a':
		snack.push_back(block(last.x+1, last.y, 'a'));
		break;
	case 's':
		snack.push_back(block(last.x, last.y-1, 's'));
		break;
	case 'd':
		snack.push_back(block(last.x-1, last.y, 'd'));
		break;
	}
	return true;
}

bool move_snack(vector<class block> &snack, char d)
{
	auto first = snack.front();
	switch (d)
	{
	case 'w':
		snack.insert(snack.begin(), block(first.x, first.y - 1, 'w'));
		break;
	case 'a':
		snack.insert(snack.begin(), block(first.x - 1, first.y, 'a'));
		break;
	case 's':
		snack.insert(snack.begin(), block(first.x, first.y + 1, 's'));
		break;
	case 'd':
		snack.insert(snack.begin(), block(first.x + 1, first.y, 'd'));
		break;
	}
	snack.pop_back();
	return true;
}