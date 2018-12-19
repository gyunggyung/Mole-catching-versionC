#pragma warning(disable: 4996)
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input_output.h"
#define X_MAX 26	//����ĭ��
#define SPACE 25
int node_down(int b);
void clearscreen();  //ȭ�� �ø�Ŀ ����

char map[60][X_MAX];
char obstacle = 'O'; //���
int y = 18, x = 9;
int	 a = 0;
int main()
{
	int top, i;
	struct gamers **top10;
	top10 = (struct gamers**)calloc(10 , sizeof(struct gamers*));
	top = ReadFile(top10);

	int c = rand() % (X_MAX - 1) + 3;
	int	b = rand() % (X_MAX - 1) + 3;			//��� ��ǥ
	char name[1000];
	int deathcounter = 0;
	//�� ����
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < X_MAX; ++j) {
			map[i + SPACE][0] = '|';
			map[i + SPACE][X_MAX - 2] = '|';
			map[i + SPACE][j] = ' ';
		}
	}

	srand(time(0));

	int points = 0;
	int speed = 100;					//���, ���� ���ǵ�
	int cashcheck = 0;					//ĳ��
	int cashpickedup = 0;				//�� ������ ++
	int startup = 1;
	int point = 0;


	char car = 'X';
	map[y + SPACE][x] = car;

	//PlaySound(TEXT("123.wav"), NULL, SND_FILENAME | SND_ASYNC );  //���� ��� �ϸ鼭 �������� 
	//������ ����

	for (;;) {
		clearscreen(); //ȭ�� �ø�Ŀ ����
					   //�÷��̾�
		map[y + SPACE][x] = 'X';
		map[y + SPACE][x + 1] = '|';
		map[y + SPACE][x - 1] = '|';

		//��� ��������
		b = node_down(b);

		//ȭ�� ���
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < X_MAX; ++j) {
				printf("%c", map[i + SPACE][j]);
				if (j >= X_MAX - 1) {
					printf("\n");
				}
			}
		}//���� ���
		point = deathcounter + (cashpickedup * 10);
		printf("Points: %d  Deathcounter: %d \n", point, deathcounter);
		printf("\nDeathcounter�� 2000�� �Ǹ� ����ʴϴ�. ");

		//��������
		if (deathcounter == 2000)
		{
			printf("\n\n�̸��� �Է��ϼ���\n\n");
			scanf("%s", name);
			system("cls");
			user_input_output(name, point, top10, top);//���Ͽ� ����
													   //cin.get();
			return 0;
		}

		if (startup) {
			getchar(); //Ű �ޱ�
			startup = 0;
		}

		//���� �̵�
		if (GetAsyncKeyState(VK_LEFT)) {
			if (map[y + SPACE][x - 3] == obstacle) {
				goto lost;		//������
			}
			else if (map[y + SPACE][x - 3] != '|') {
				//�� ������ ������ ������ ���
				map[y + SPACE][x] = ' ';
				map[y + SPACE][x + 1] = ' ';
				map[y + SPACE][x - 1] = ' ';

				x -= 3;
				map[y + SPACE][x] = 'X';
				map[y + SPACE][x + 1] = '|';
				map[y + SPACE][x - 1] = '|';

			}
		}

		//������ �̵�
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (map[y + SPACE][x + 3] == obstacle) {
				goto lost;		//������
			}
			else if (map[y + SPACE][x + 3] != '|') {
				//�� ������ ������ ������ ���
				map[y + SPACE][x] = ' ';
				map[y + SPACE][x + 1] = ' ';
				map[y + SPACE][x - 1] = ' ';

				x += 3;
				map[y + SPACE][x] = 'X';
				map[y + SPACE][x + 1] = '|';
				map[y + SPACE][x - 1] = '|';

			}
		}

		//���� ������
		if (map[y + SPACE][x] == obstacle || map[y + SPACE][x - 1] == obstacle || map[y + SPACE][x + 1] == obstacle) {
		lost:
			++cashpickedup;
		}

		deathcounter++;

		//�ӵ� ���
		if (deathcounter == 100 || deathcounter == 200 || deathcounter == 300 || deathcounter == 400 || deathcounter == 500) {
			speed -= 18;
		}
		if (deathcounter == 1000)
			speed -= 8;
		if (deathcounter == 1800)
			speed -= 2;
		Sleep(speed);
	}
	return 0;

}
void clearscreen()
{
	HANDLE hOut;	//void ������ ������ ����
	COORD Position;	//��ǥ �޴� ����ü

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//������ ��

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);	//Ŀ�� �̵���
												//�ڵ� ���� ù����� �ް�, �ι�°�� Ŀ���� �̵��ϰ��� �ϴ� ��ǥ���� ������ ���� ����ü COORD�� �޴´�.
}	//ȭ�� �����̴°� ����

int node_down(int b)
{
	int node_num = 10;
	for (int j = 0; j < node_num; j++)
	{
		map[a - j + SPACE][b] = ' ';
		map[a - j + SPACE][b + 1] = ' ';
		map[a - j + SPACE][b - 1] = ' ';
	}
	++a;
	//��� ����
	for (int j = 0; j < node_num; j++)
	{
		map[a - j + SPACE][b] = obstacle;
		map[a - j + SPACE][b + 1] = obstacle;
		map[a - j + SPACE][b - 1] = obstacle;
	}
	//�� �����̸� ���� ����
	if (a > 28) {
		a = 0;
		b = rand() % 15 + 2;
	}

	return b;
}