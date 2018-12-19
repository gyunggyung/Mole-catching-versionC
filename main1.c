#pragma warning(disable: 4996)
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input_output.h"
#define X_MAX 26	//가로칸수
#define SPACE 25
int node_down(int b);
void clearscreen();  //화면 플리커 예방

char map[60][X_MAX];
char obstacle = 'O'; //노드
int y = 18, x = 9;
int	 a = 0;
int main()
{
	int top, i;
	struct gamers **top10;
	top10 = (struct gamers**)calloc(10 , sizeof(struct gamers*));
	top = ReadFile(top10);

	int c = rand() % (X_MAX - 1) + 3;
	int	b = rand() % (X_MAX - 1) + 3;			//노드 좌표
	char name[1000];
	int deathcounter = 0;
	//맵 생성
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < X_MAX; ++j) {
			map[i + SPACE][0] = '|';
			map[i + SPACE][X_MAX - 2] = '|';
			map[i + SPACE][j] = ' ';
		}
	}

	srand(time(0));

	int points = 0;
	int speed = 100;					//노드, 유저 스피드
	int cashcheck = 0;					//캐시
	int cashpickedup = 0;				//돈 먹으면 ++
	int startup = 1;
	int point = 0;


	char car = 'X';
	map[y + SPACE][x] = car;

	//PlaySound(TEXT("123.wav"), NULL, SND_FILENAME | SND_ASYNC );  //음악 출력 하면서 내용진행 
	//하지만 실패

	for (;;) {
		clearscreen(); //화면 플리커 예방
					   //플레이어
		map[y + SPACE][x] = 'X';
		map[y + SPACE][x + 1] = '|';
		map[y + SPACE][x - 1] = '|';

		//노드 내려오기
		b = node_down(b);

		//화면 출력
		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j < X_MAX; ++j) {
				printf("%c", map[i + SPACE][j]);
				if (j >= X_MAX - 1) {
					printf("\n");
				}
			}
		}//점수 출력
		point = deathcounter + (cashpickedup * 10);
		printf("Points: %d  Deathcounter: %d \n", point, deathcounter);
		printf("\nDeathcounter가 2000이 되면 종료됨니다. ");

		//게임종료
		if (deathcounter == 2000)
		{
			printf("\n\n이름을 입력하세요\n\n");
			scanf("%s", name);
			system("cls");
			user_input_output(name, point, top10, top);//파일에 저장
													   //cin.get();
			return 0;
		}

		if (startup) {
			getchar(); //키 받기
			startup = 0;
		}

		//왼쪽 이동
		if (GetAsyncKeyState(VK_LEFT)) {
			if (map[y + SPACE][x - 3] == obstacle) {
				goto lost;		//닿을시
			}
			else if (map[y + SPACE][x - 3] != '|') {
				//맵 밖으로 나가지 않을때 출력
				map[y + SPACE][x] = ' ';
				map[y + SPACE][x + 1] = ' ';
				map[y + SPACE][x - 1] = ' ';

				x -= 3;
				map[y + SPACE][x] = 'X';
				map[y + SPACE][x + 1] = '|';
				map[y + SPACE][x - 1] = '|';

			}
		}

		//오른쪽 이동
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (map[y + SPACE][x + 3] == obstacle) {
				goto lost;		//닿을시
			}
			else if (map[y + SPACE][x + 3] != '|') {
				//맵 밖으로 나가지 않을때 출력
				map[y + SPACE][x] = ' ';
				map[y + SPACE][x + 1] = ' ';
				map[y + SPACE][x - 1] = ' ';

				x += 3;
				map[y + SPACE][x] = 'X';
				map[y + SPACE][x + 1] = '|';
				map[y + SPACE][x - 1] = '|';

			}
		}

		//노드과 닿을때
		if (map[y + SPACE][x] == obstacle || map[y + SPACE][x - 1] == obstacle || map[y + SPACE][x + 1] == obstacle) {
		lost:
			++cashpickedup;
		}

		deathcounter++;

		//속도 상승
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
	HANDLE hOut;	//void 포인터 정도로 생각
	COORD Position;	//좌표 받는 구조체

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//쓰레기 값

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);	//커서 이동용
												//핸들 값을 첫번재로 받고, 두번째로 커서를 이동하고자 하는 좌표값의 정보를 담은 구조체 COORD를 받는다.
}	//화면 깜빡이는거 예방

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
	//노드 모형
	for (int j = 0; j < node_num; j++)
	{
		map[a - j + SPACE][b] = obstacle;
		map[a - j + SPACE][b + 1] = obstacle;
		map[a - j + SPACE][b - 1] = obstacle;
	}
	//다 움직이면 새로 시작
	if (a > 28) {
		a = 0;
		b = rand() % 15 + 2;
	}

	return b;
}