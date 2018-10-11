#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
using namespace std;
char map[40][120] = { ' ' };

class Map {
private:
	int roomNum;
	int roomOfDoor[7] = { 0 };
	struct Door {
		int x;
		int y;
		bool Isconnect;
		Door() {
			x = 0;
			y = 0;
			Isconnect = 0;
		}
	};
	struct room {
		int width = 3 + rand() % 4;
		int length = 3 + rand() % 13;
		int x = rand() % (39 - width);
		int y = rand() % (119 - length);
	};
public:
	Door door[50];
	Map();
	void connect(int doornum, int roomnum);
	void printmap();
};
class Monster {
private:
	int hp;
	int atk;
	int posmx;
	int posmy;
public:
	Monster();
	void beattacked(char a);
	void move();
	int died();
};
class Player {
private:
	int hp = 0;
	int atk = 0;
	int def = 0;
	int posx;
	int posy;
public:
	Map themap;
	Monster m[10];
	Player();//人物初始hp=10，atk=1，def=0
	int returnHp();//获得人物血量用于判断游戏结束条件
	void beattacked();
	void move(char a);//人物进行移动
	void use();
	void rest();
	void operate(char a);
	void backpack();
	int gameover();
	int win();
};
Map::Map() {
	srand((unsigned)time(NULL));
	roomNum = 4 + rand() % 4;//生成4-7个房间
	int i = 0, j = 0;
	int k = roomNum;
	int doorNum = 0;
	while (k) {
		room theRoom;
		for (i = 0; i < theRoom.width + 2; i++) {
			for (j = 0; j < theRoom.length + 2; j++) {
				if (map[theRoom.x + i][theRoom.y + j] == 'X' || map[theRoom.x + i][theRoom.y + j] == '.')
					break;
			}
			if (j < theRoom.length + 2)
				break;
		}
		if (i < theRoom.width + 2)
			continue;
		for (i = 0; i < theRoom.width + 2; i++) {
			for (j = 0; j < theRoom.length + 2; j++) {
				if (i == 0 || i == theRoom.width + 1 || j == 0 || j == theRoom.length + 1) {
					if ((i == 0 || i == theRoom.width + 1) && (j == 0 || j == theRoom.length + 1))
						map[theRoom.x + i][theRoom.y + j] = 'X';
					else {
						map[theRoom.x + i][theRoom.y + j] = rand() % (theRoom.width + theRoom.length) ? 'X' : '#';
						if (map[theRoom.x + i][theRoom.y + j] == '#') {
							door[doorNum].x = theRoom.x + i;
							door[doorNum].y = theRoom.y + j;
							doorNum++;
							roomOfDoor[roomNum - k]++;
						}
					}
				}
				else
					map[theRoom.x + i][theRoom.y + j] = '.';
			}
		}
		if (roomOfDoor[roomNum - k] == 0) {
			i = rand() % 2 ? theRoom.x + theRoom.width + 1 : theRoom.x;
			j = theRoom.y + 1 + rand() % theRoom.length;
			map[i][j] = '#';
			door[doorNum].x = i;
			door[doorNum].y = j;
			doorNum++;
			i = theRoom.x + 1 + rand() % theRoom.width;
			j = rand() % 2 ? theRoom.y + theRoom.length + 1 : theRoom.y;
			map[i][j] = '#';
			door[doorNum].x = i;
			door[doorNum].y = j;
			doorNum++;
			roomOfDoor[roomNum - k] = 2;
		}
		k--;
	}
}

void Map::connect(int doornum, int roomnum) {
	int sum;
	int m, n;
	int ax, ay, bx, by;
	for (n = 0; n < doornum; n++) {
		if (door[n].x == 0 || door[n].x == 39 || door[n].y == 0 || door[n].y == 119)
			door[n].Isconnect = 1;
		if (!door[n].Isconnect) {
			door[n].Isconnect = 1;
			ax = door[n].x;
			ay = door[n].y;
			sum = 0;
			m = 0;
			while (m < roomnum) {
				sum += roomOfDoor[m];
				if (sum > n)
					break;
				m++;
			}
			if (m != roomnum - 1) {
				while (door[sum].Isconnect) {
					sum++;
				}
				door[sum].Isconnect = 1;
				bx = door[sum].x;
				by = door[sum].y;
			}
			else {
				sum = rand() % n;
				bx = door[sum].x;
				by = door[sum].y;
			}
		}
	}
}

void Map::printmap() {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 120; j++)
			cout << map[i][j];
		cout << endl;
	}
}

Monster::Monster() {
	hp = 10;
	atk = 5;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 120; j++) {
			if (map[i][j] == '.' && (!(rand() % 50))) {
				map[i][j] = 'M';
				posmx = i;
				posmy = j;
				break;
			}
		}
		if (posmx == i)
			break;
	}
}
void Monster::beattacked(char a) {
	switch (a) {
	case '1':
		if (map[posmx - 1][posmy + 1] == '@')
			hp--;
		break;
	case'2':
		if (map[posmx - 1][posmy] == '@')
			hp--;
		break;
	case'3':
		if (map[posmx - 1][posmy - 1] == '@')
			hp--;
		break;
	case'4':
		if (map[posmx][posmy + 1] == '@')
			hp--;
		break;
	case'6':
		if (map[posmx][posmy - 1] == '@')
			hp--;
		break;
	case'7':
		if (map[posmx + 1][posmy + 1] == '@')
			hp--;
		break;
	case'8':
		if (map[posmx + 1][posmy] == '@')
			hp--;
		break;
	case'9':
		if (map[posmx + 1][posmy - 1] == '@')
			hp--;
		break;
	}
}

void Monster::move() {
	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			if (map[posmx + i][posmy + j] == '@') {
				int x = posmx + i;
				int y = posmy + j;
				if (x >= posmx&&y > posmy) {
					map[posmx][posmy] = '.';
					if (x != posmx)
						posmx++;
					posmy++;
					map[posmx][posmy] = 'M';
				}
				if (x >= posmx&&y < posmy) {
					map[posmx][posmy] = '.';
					if (x != posmx)
						posmx++;
					posmy--;
					map[posmx][posmy] = 'M';
				}
				if (x < posmx&&y <= posmy) {
					map[posmx][posmy] = '.';
					if (y != posmy)
						posmy--;
					posmx--;
					map[posmx][posmy] = 'M';
				}
				if (x > posmx&&y <= posmy) {
					map[posmx][posmy] = '.';
					if (y != posmy)
						posmy--;
					posmx++;
					map[posmx][posmy] = 'M';
				}
			}
		}
	}
}

int Monster::died() {
	if (hp <= 0) {
		map[posmx][posmy] = '.';
		return 1;
	}
	return 0;
}

Player::Player() {
	hp = 10;
	atk = 1;
	def = 0;
	posx = themap.door[0].x;
	posy = themap.door[0].y;
	map[posx][posy] = '@';
}
int Player::returnHp() {
	return hp;
}
void Player::beattacked() {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map[posx + i][posy + j] == 'M')
				hp -= 5;
		}
	}
}
void Player::move(char a) {
	if ((map[posx + 1][posy] == 'X'&&map[posx - 1][posy] == 'X') || (map[posx][posy + 1] == 'X'&&map[posx][posy - 1] == 'X'))
		map[posx][posy] = '#';
	else if ((map[posx + 1][posy] == '\0'&&map[posx - 1][posy] == '\0') || (map[posx][posy + 1] == '\0'&&map[posx][posy - 1] == '\0'))
		map[posx][posy] = ' ';
	else
		map[posx][posy] = '.';
	switch (a) {
	case 'h':
		if (map[posx][posy - 1] != 'X')
			posy--;
		break;
	case 'j':
		if (map[posx + 1][posy] != 'X')
			posx++;
		break;
	case 'k':
		if (map[posx - 1][posy] != 'X')
			posx--;
		break;
	case 'l':
		if (map[posx][posy + 1] != 'X')
			posy++;
		break;
	case 'y':
		if (map[posx - 1][posy - 1] != 'X') {
			posx--;
			posy--;
		}
		break;
	case 'u':
		if (map[posx - 1][posy + 1] != 'X') {
			posx--;
			posy++;
		}
		break;
	case 'b':
		if (map[posx + 1][posy - 1] != 'X') {
			posx++;
			posy--;
		}
		break;
	case 'n':
		if (map[posx + 1][posy + 1] != 'X') {
			posx++;
			posy++;
		}
		break;
	}
	if (posx < 0)posx = 0;
	if (posx > 39)posx = 39;
	if (posy < 0)posy = 0;
	if (posy > 119)posy = 119;
	map[posx][posy] = '@';
}
void Player::rest() {
	if (hp < 10)
		hp++;
}
void Player::use() {

}
void Player::backpack() {

}
int monnum() {
	int num = 0;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 120; j++) {
			if (map[i][j] == 'M')
				num++;
		}
	}
	return num;
}
int Player::win() {
	if (monnum() == 0)
		return 1;
	else
		return 0;
}
int Player::gameover() {
	if (hp <= 0)
		return 1;
	else
		return 0;
}

void Player::operate(char a) {
	int n = 0;
	switch (a) {
	case 'h':case 'j':case 'k':case 'l':case 'y':case 'u':case 'b':case 'n':
		move(a);
		break;
	case '5':
		rest();
		break;
	case 'e':
		use();
		break;
	case 'q':
		backpack();
		break;
	default:break;
	}
	beattacked();
	n = 0;
	while (n<monnum()) {
		m[n].move();
		n++;
	}
}

int main() {
	Player p1;
	p1.themap.printmap();
	while (!p1.gameover()) {
		char oper = _getch();
		int n = 0;
		switch (oper) {
		case '1':case'2':case'3':case'4':case'6':case'7':case'8':case'9':
			while (n < monnum()) {
				p1.m[n].beattacked(oper);
				if (p1.m[n].died());
				n++;
			}
			break;
		default:
			p1.operate(oper);
			break;
		}
		system("cls");
		p1.themap.printmap();
		if (p1.win()) {
			cout << "Win!" << endl;
			return 0;
		}
	}
	cout << "Game over!" << endl;
	return 0;
}