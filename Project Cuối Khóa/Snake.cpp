#include <iostream>
#include "HoangLibrary.h"
#define SODOT 100
using namespace std;
int toadox[SODOT] = { 0 };
int toadoy[SODOT] = { 0 };
int sl = 3;
int xfruit, yfruit;
int score = 0;

void wall()
{
	char c = 205;
	for (int x = 10; x <= 95; x++) {
		gotoXY(x, 1);
		cout << c;
		gotoXY(x, 25);
		cout << c;
	}
	char d = 186;
	for (int y = 1; y <= 25; y++) {
		gotoXY(10, y);
		cout << d;
		gotoXY(95, y);
		cout << d;
	}
	char e = 201; //trentrai 
	gotoXY(10, 1);
	cout << e;
	char f = 187;//trenphai
	gotoXY(95, 1); cout << f;
	char g = 200; //duoitrai 
	gotoXY(10, 25);
	cout << g;
	char h = 188;//duoiphai
	gotoXY(95, 25); cout << h;
}

void initial_snake()
{
	int x_start = 50;
	int y_start = 13;
	for (int i = 0; i <= sl; i++) {
		toadox[i] = x_start--;
		toadoy[i] = y_start;
	}
}

void draw_snake()
{
	char k = 153;
	for (int i = 0; i < sl; i++)
	{
		gotoXY(toadox[i], toadoy[i]);
		if (i == 0) {
			cout << k;
		}
		else {
			cout << "o";
		}
	}
}

void move_snake(int x, int y)
{
	for (int i = sl; i > 0; i--)
	{
		toadox[i] = toadox[i - 1];
		toadoy[i] = toadoy[i - 1];
	}
	toadox[0] = x;
	toadoy[0] = y;
}

bool bite_wall()
{
	if (toadox[0] == 10 || toadox[0] == 95 || toadoy[0] == 1 || toadoy[0] == 25) {
		return true;
	}return false;
}
bool bite_tail()
{
	for (int i = 1; i <= sl; i++)
	{
		if (toadox[0] == toadox[i] && toadoy[0] == toadoy[i]) {
			return true;
		}
	}return false;
}

void make_random_fruit()
{
	xfruit = rand() % (94 - 11 + 1) + 11;
	yfruit = rand() % (24 - 2 + 1) + 2;
}
void draw_fruit()
{
	char c = 254;
	gotoXY(xfruit, yfruit);
	cout << c;
}

void play()
{
	ShowCur(0);
	SetColor(11);
	wall();
	initial_snake();
	make_random_fruit();
	draw_fruit();
	int x = toadox[0];
	int y = toadoy[0];
	int direction = 2;
	while (true) {
		//xóa đốt cuối khi di chuyển
		gotoXY(toadox[sl], toadoy[sl]);
		cout << " ";
		//hiển thị rắn ra màn hình
		draw_snake();
		//điều khiển = bàn phím
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
				if (c == 72 && direction != 0) {
					direction = 1;
				}
				else if (c == 80 && direction != 1) {
					direction = 0;
				}
				else if (c == 75 && direction != 2) {
					direction = 3;
				}
				else if (c == 77 && direction != 3) {
					direction = 2;
				}
			}
		}
		//di chuyển rắn
		if (direction == 0) {
			y++;
		}
		else if (direction == 1) {
			y--;
		}
		else if (direction == 2) {
			x++;
		}
		else if (direction == 3) {
			x--;
		}
		//
		if (toadox[0] == xfruit && toadoy[0] == yfruit) {
			sl++; //tăng đốt
			gotoXY(0, 0);
			cout << "Score: " << ++score;
			//tạo quả mới
			make_random_fruit();
			draw_fruit();
		}
		move_snake(x, y);
		Sleep(80);
		//game over
		if (bite_wall()) {
			ShowCur(0);
			gotoXY(48, 12);
			cout << "GAME OVER";
			gotoXY(46, 13);
			cout << "Your score: " << score;
			break;
		}
		else if (bite_tail()) {
			gotoXY(48, 12);
			cout << "GAME OVER";
			gotoXY(46, 13);
			cout << "Your score: " << score;
			ShowCur(0);
			break;
		}
	}
}

void bang_menu()
{
	int x = 0;
	int y = 3;
	int choose = 0;
	char c;
	ShowCur(0);
	SetColor(11);
	gotoXY(x, y - 1);
	cout << "Student: Nguyen Minh Hoang\n"
		<< "Mentor:  Mr.Pham Thien and Mr.Bui Quang Dang";
	SetColor(6);
	gotoXY(x, y + 2);
	cout << "         1. Start game               ";
	gotoXY(x, y + 3);
	cout << "         2. Exit       ";
	while (true)
	{
		if (_kbhit())
		{
			c = _getch();

			if (c == '1')
			{
				ShowCur(0);
				SetColor(6);
				gotoXY(x, y + 2);
				cout << "         1. Start game               ";
				gotoXY(x, y + 3);
				cout << "         2. Exit       ";
				SetColor(11);
				gotoXY(x + 6, y + 2);
				cout << ">";
				choose = 1;
			}
			else if (c == '2')
			{
				ShowCur(0);
				SetColor(6);
				gotoXY(x, y + 2);
				cout << "         1. Start game               ";
				gotoXY(x, y + 3);
				cout << "         2. Exit       ";
				SetColor(11);
				gotoXY(x + 6, y + 3);
				cout << ">";
				choose = 2;

			}

			else {
				if (choose == 1)
				{
					ShowCur(0);
					system("cls");
					play();
					if (bite_wall()) {
						break;
					}
					else if (bite_tail()) {
						break;
					}
				}
				else if (choose == 2) {
					ShowCur(0);
					system("cls");
					gotoXY(53, 13);
					cout << "GOOD BYE!!!";
					break;
				}
			}

		}
	}
}

int main()
{
	srand(time(NULL)); //spawn quả không bị trùng nhau
	bang_menu();
	_getch();
}
