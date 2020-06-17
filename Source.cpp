#include<iostream>
#include<ctime>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include<map>
#include<vector>
#include<string>

static const int X = 10;
static char ship_id = 'a';
static std::map<char, int> ships{};

void gotoxy(int x, int y);
bool is_ship(char map[X][X], int  x, int y, int dir, int size);
void Set_Ships(int x, int y, int direction, int size, int count_ship);
bool ship_in_map(int x, int y, int dir, int size);
int newMenu(std::vector<std::string> menu);
void set_rand_ships(char map[X][X], int ship_size, int count_ships);
void ShowMap(char map[X][X], int mask[X][X]);
void ShowMap1(char map[X][X], int mask[X][X]);
void manual_placement(char map[X][X], int mask[X][X], int count_ships, int size);
void Coordinates(int shoot_x, int shoot_y);
int Shot(char map[X][X], int mask[X][X], int shoot_x, int shoot_y);
bool Search(char map[X][X]);
void AI_Shot(char map[X][X], int mask[X][X], int shoot_x, int shoot_y);
void RulesShow();
void Check(int result);

int main()
{

	setlocale(0, "");

	char map[X][X]{};
	int mask[X][X]{};
	int mask1[X][X]{};
	char map2[X][X]{};
	int shoot_x, shoot_y;
	int res_shot=0;
	bool turn = true;
	std::vector <std::string> items{"Play","Rules","Exit"};
	std::vector <std::string> items1{ "Easy","Hard","Back" };
	std::vector <std::string> items2{ "Manual","Auto", };
	int choose;
	bool flag1, flag2;
	bool game = true;
	int bot_shot;
	
	int choose2=0;
	int choose3;
	while (game)
	{
		
		do
		{
			choose = newMenu(items);
			if (choose == 0)
			{
				choose2 = newMenu(items1);
				if (choose2!=2)
				{

				choose3 = newMenu(items2);
				system("cls");
				}
			}
			if (choose==1)
			{
				system("cls");
				RulesShow();
				_getch();
				
			}
			if (choose == 2)
			{
				exit(0);

			}
		} while (choose2==2);
		
		set_rand_ships(map2, 4, 1);
		set_rand_ships(map2, 3, 2);
		set_rand_ships(map2, 2, 3);
		set_rand_ships(map2, 1, 4);
		
		if (choose3==0)
		{
		manual_placement(map, mask, 1, 4);
		manual_placement(map, mask, 2, 3);
		manual_placement(map, mask, 3, 2);
		manual_placement(map, mask, 4, 1);

		}
		if (choose3 == 1)
		{
			set_rand_ships(map, 4, 1);
			set_rand_ships(map, 3, 2);
			set_rand_ships(map, 2, 3);
			set_rand_ships(map, 1, 4);

		}

		while(game)
		{
		do 
		{

			ShowMap(map, mask);
			ShowMap1(map2, mask1);
			gotoxy(0, 14);
			if (turn)
			{
				std::cout << "Shoot by coordinates:" << std::endl;
				std::cin >> shoot_x >> shoot_y;
				res_shot = Shot(map2, mask1, shoot_x, shoot_y);
				Check(res_shot);
			flag1=Search(map2);
			if (flag1==false)
			{
				std::cout << "\nYou win!!!\n";
				game = false;
				break;
			}
			}
			else
			{
				std::cout << "Computers turn:" << std::endl;
				Sleep(1000);
				shoot_x = rand() % X;
				shoot_y = rand() % X;
				if (choose2==1)
				{
				AI_Shot(map, mask, shoot_x, shoot_y);
				
				}
				else if(choose2==0)
				{
						
					bot_shot=Shot(map, mask, shoot_x, shoot_y);
					Check(bot_shot);
				}

				flag2 = Search(map);
				if (flag2 == false)
				{
					std::cout << "\nComputer wins!!!\n";
					game = false;
					break;
				}
			}

			Sleep(1000);
			system("cls");
		} while (res_shot);

		turn = !turn;
	}
		_getch();
		system("cls");
		

	}

	return 0;
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool is_ship(char map[X][X], int  x, int y, int dir, int size)
{
	bool flag = true;

	int tmp_x = x;
	int tmp_y = y;

	for (size_t i = 0; i < size; i++)
	{

		if (x < 0 || y < 0 || x >= X || y >= X)
		{
			flag = NULL;
			break;
		}
		
		if (map[x][y] >= 97)
		{
			flag = NULL;
			break;
		}
		if (y < X - 1)
			if (map[x][y + 1] >= 97)
			{
				flag = NULL;
				break;
			}
		if (y > 0)
		{
			if (map[x][y - 1] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		if (x < X - 1)
		{
			if (map[x][y - 1] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		if (x < X - 1 && y < X - 1)
		{
			if (map[x + 1][y + 1] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		if (x < X - 1 && y > 0)
		{
			if (map[x + 1][y - 1] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		if (x > 0)
		{
			if (map[x - 1][y] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		if (x > 0 && y < X - 1)
		{
			if (map[x - 1][y + 1] >= 97)
			{
				flag = NULL;
				break;
			}
		}
		switch (dir)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		default:
			break;
		}

	}
	if (flag)
	{
		x = tmp_x;
		y = tmp_y;
		for (size_t i = 0; i < size; i++)
		{
			map[x][y] = ship_id;
			switch (dir)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default:
				break;
			}
		}
		ships.insert(std::pair<char, int>(ship_id, size));

		ship_id++;
	}
	return flag;
}

void Set_Ships(int x, int y, int direction, int size, int count_ship)
{

	for (size_t i = 0; i < size; i++)
	{
		gotoxy(x + 1, y + 1);
		std::cout << "#";

		switch (direction)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		default:
			break;
		}
	}


}


bool ship_in_map(int x, int y, int dir, int size)
{
	bool flag = true;

	for (size_t i = 0; i < size; i++)
	{

		if (x < 0 || y < 0 || x >= X || y >= X)
		{
			flag = NULL;
			break;
		}



		switch (dir)
		{
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		default:
			break;
		}

	}
	return flag;
}

int newMenu(std::vector<std::string> menu)
{

	int selection = 0;

	while (true)
	{
		system("cls");
		/*gotoxy(20, 10);*/
		for (int i = 0; i < menu.size(); i++)
		{
			if (i == selection)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 124);
				std::cout << menu[i] << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else
			{
				std::cout << menu[i] << std::endl;
			}
		}

		int key = _getch();
		if (key == 224)
		{
			key = _getch();
			if (key == 72)
			{
				selection--;
				if (selection < 0)
					selection = 2;
			}
			if (key == 80)
			{
				selection++;
				selection = selection % 3;
			}
		}
		else if (key == 13)
		{
			return selection;
		}
	}
}

void set_rand_ships(char map[X][X], int ship_size, int count_ships)
{
	int x, y;
	int tmp_x, tmp_y;
	int direction = 0;
	bool flag;
	int counter = 0;
	int iteration = 0;
	while (counter < count_ships)
	{
		iteration++;
		if (iteration > 1000)
		{
			break;
		}
		x = rand() % X;
		y = rand() % X;
		tmp_x = x;
		tmp_y = y;
		direction = rand() % 4;
		flag = true;

		for (size_t i = 0; i < ship_size; i++)
		{

			if (x < 0 || y < 0 || x >= X || y >= X)
			{
				flag = NULL;
				break;
			}

			if (map[x][y] >= 97)
			{
				flag = NULL;
				break;
			}
			if (y < X - 1)
				if (map[x][y + 1] >= 97)
				{
					flag = NULL;
					break;
				}
			if (y > 0)
			{
				if (map[x][y - 1] >= 97)
				{
					flag = NULL;
					break;
				}
			}
			if (x < X - 1)
			{
				if (map[x][y - 1] >= 97)
				{
					flag = NULL;
					break;
				}
			}
			if (x < X - 1 && y < X - 1)
			{
				if (map[x + 1][y + 1] >= 97)
				{
					flag = NULL;
					break;
				}
			}
			if (x < X - 1 && y > 0)
			{
				if (map[x + 1][y - 1] >= 97)
				{
					flag = NULL;
					break;
				}
			}
			if (x > 0)
			{
				if (map[x - 1][y] >= 97)
				{
					flag = NULL;
					break;
				}
			}
			if (x > 0 && y < X - 1)
			{
				if (map[x - 1][y + 1] >= 97)
				{
					flag = NULL;
					break;
				}
			}


			switch (direction)
			{
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			default:
				break;
			}

		}
		if (flag)
		{
			x = tmp_x;
			y = tmp_y;
			for (size_t i = 0; i < ship_size; i++)
			{
				map[x][y] = ship_id;
				switch (direction)
				{
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				default:
					break;
				}
			}
			ships.insert(std::pair<char, int>(ship_id, ship_size));
			counter++;
			ship_id++;
		}


	}
}

void ShowMap(char map[X][X], int mask[X][X])
{


	std::cout << " ";
	for (size_t i = 0; i < X; i++)
	{

		std::cout << i;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < X; i++)
	{
		std::cout << i;
		for (size_t j = 0; j < X; j++)
		{
			//if (mask[j][i]==1)
			{

				if (map[j][i] == 0)
				{
					std::cout << '-';
				}
				else if (map[j][i] == -1)
				{
					std::cout << 'X';
				}

				else if (map[j][i] == -2)
				{
					std::cout << '*';
				}
				else
				{
					std::cout << map[j][i];
				}
			}
			/*else
			{
				std::cout << ' ';
			}*/
		}
		std::cout << std::endl;

	}
	gotoxy(0, 0);
}

void ShowMap1(char map[X][X], int mask[X][X])
{

	std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t ";

	for (size_t i = 0; i < X; i++)
	{

		std::cout << i;
	}
	std::cout << std::endl;
	std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t";
	for (size_t i = 0; i < X; i++)
	{
		std::cout << i;
		for (size_t j = 0; j < X; j++)
		{
			if (mask[j][i] == 1)
			{

				if (map[j][i] == 0)
				{
					std::cout << '-';
				}
				else if (map[j][i] == -1)
				{
					std::cout << 'X';
				}
				else if (map[j][i] == -2)
				{
					std::cout << '*';
				}
				else
				{
					std::cout << map[j][i];
				}
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
		std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t";
	}
	std::cout << '\b';
}

void manual_placement(char map[X][X], int mask[X][X], int count_ships, int size)
{
	int counter = 0;
	int x = 0, y = 0;
	int temp_x, temp_y, temp_dir;
	int ch;
	int dir = 1;
	while (counter < count_ships)
	{
		ShowMap(map, mask);

		Set_Ships(x, y, dir, size, 4);
		temp_x = x;
		temp_y = y;
		temp_dir = dir;

		ch = _getch();
		switch (ch)
		{
		case 100:
			x++;
			break;
		case 115:
			y++;
			break;
		case 97:
			x--;
			break;
		case 119:
			y--;
			break;
		case 114:
			dir = !dir;
			break;
		case 13:
			if (is_ship(map, x, y, dir, size))
			{
				x = 0;
				y = 0;
				dir = 0;

				counter++;
			}
			break;
		default:
			break;
		}
		if (!ship_in_map(x, y, dir, size))
		{
			x = temp_x;
			y = temp_y;
			dir = temp_dir;


		}
		system("cls");
	}
}

void Coordinates(int shoot_x, int shoot_y)
{
	std::cout << "x:" << shoot_x << std::endl;
	std::cout << "y:" << shoot_y << std::endl;
}

int Shot(char map[X][X], int mask[X][X], int shoot_x, int shoot_y)
{
	int result = 0;
	Coordinates(shoot_x, shoot_y);
	if (map[shoot_y][shoot_x] >= 97)
	{
		ships[map[shoot_y][shoot_x]]--;

		if (ships[map[shoot_y][shoot_x]] <= 0)
		{
			result = 2;

		}
		else
		{
			result = 1;


		}
		map[shoot_y][shoot_x] = -1;
	}
	else if (map[shoot_y][shoot_x] == -1)
	{

		result = -1;

	}
	else
	{
		map[shoot_y][shoot_x] = -2;
	}

	mask[shoot_y][shoot_x] = 1;
	return result;
}

bool Search(char map[X][X])
{

	for (size_t i = 0; i < X; i++)
	{
		for (size_t j = 0; j < X; j++)
		{
			if (map[i][j] >= 97)
			{
				return true;
			}
		}

	}
	return false;
}

void AI_Shot(char map[X][X], int mask[X][X], int shoot_x, int shoot_y)
{
	int dir = 0;
	int memoryX = 0;
	int memoryY = 0;
	int CPU = 0;

	std::vector <int> dirs;

	dirs.push_back(3);
	dirs.push_back(2);
	dirs.push_back(1);
	dirs.push_back(0);

	do {
		if (CPU == 0) {



			Coordinates(shoot_x, shoot_y);

			if (map[shoot_y][shoot_x] >= 1) {
				CPU = 1;
				map[shoot_y][shoot_x] = -1;
				memoryX = shoot_x;
				memoryY = shoot_y;

				ships[map[shoot_y][shoot_x]]--;

				if (!dirs.empty()) {
					dir = dirs[dirs.size() - 1];
					dirs.pop_back();
				}

				std::cout << "\nBoom!";
			}
			else {
				map[shoot_y][shoot_x] = -2;
				std::cout << "\nMiss!" << std::endl;
			}

		}

		else if (CPU == 1) {

			bool ChangeSMethod = 0;

			if (dir == 0) {
				if (shoot_x > 0)
					shoot_x--;

				else {
					ChangeSMethod = 1;
				}
			}

			else if (dir == 1) {
				if (shoot_x < X - 1)
					shoot_x++;


				else {
					ChangeSMethod = 1;
				}
			}
			else if (dir == 2) {
				if (shoot_y > 0)
					shoot_y--;


				else {
					ChangeSMethod = 1;
				}
			}
			else if (dir == 3) {
				if (shoot_y < X - 1)
					shoot_y++;


				else {
					ChangeSMethod = 1;
				}
			}

			if (ChangeSMethod == 1) {
				if (!dirs.empty()) {

					dir = dirs[dirs.size() - 1];
					dirs.pop_back();
				}
				shoot_x = memoryX;
				shoot_y = memoryY;

				continue;
			}


			if (map[shoot_y][shoot_x] >= 97 && ships[map[shoot_y][shoot_x]] > 1) {
				map[shoot_y][shoot_x] = -1;
				std::cout << "\nHit!" << std::endl;
				ships[map[shoot_y][shoot_x]]--;
			}
			else if (map[shoot_y][shoot_x] >= 97 && ships[map[shoot_y][shoot_x]] == 1) {
				map[shoot_y][shoot_x] = -1;
				std::cout << "\nKilled" << std::endl;
				CPU = 0;
				ships[map[shoot_y][shoot_x]] = 0;
			}
			else {
				map[shoot_y][shoot_x] = -2;

				if (!dirs.empty()) {
					dir = dirs[dirs.size() - 1];
					dirs.pop_back();
				}
				shoot_x = memoryX;
				shoot_y = memoryY;

				std::cout << "\nMiss!" << std::endl;
				break;
			}
		}



		Sleep(1000);

	} while (ships[map[shoot_y][shoot_x]] != 0);


}

void RulesShow()
{
	std::cout << "Sea battle ”- a game for two participants, in which players take turns calling the coordinates on an unknown map.\nIf you have an opponent in these coordinates, there is a ship (coordinates are busy), then the ship or part of it is “drowned”, and the person who gets it gets the right to make another move.\nThe goal of the player is the first to sink all enemy ships.\n"
		<< "Placed:\n1 ship - a row of 4 cells (“four-deck”; battleship)\n2 ships - a row of 3 cells (\"three - deck\"; cruisers)\n3 ships - a row of 2 cells (\"two - deck\"; destroyers)\n4 ships - 1 cell (\"single deck\"; torpedo boats)";

}

void Check(int result)
{
	switch (result)
	{
	case -1:
		std::cout << "You have already killed this";
		break;
	case 1:
		std::cout << "Hit!" << std::endl;
		break;
	case 2:
		std::cout << "Killed!" << std::endl;
		break;
	default:
		std::cout << "Miss!";
		break;
	}
}