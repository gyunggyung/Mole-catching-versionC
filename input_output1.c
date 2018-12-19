#include <stdio.h>
#include <string>
#include "input_output.h"
struct gamers {
	char *name;
	int point;
};
int ReadFile(struct gamers **s) {//메인에서 top10gamers 구조체동적할당 받아오기, 게임 실행전에 top10gamers 자료 불려와 구조체에 저장
	int i=0, u, p, t;
	char k[101];
	struct gamers ss, sx;
	char fn[] = "TOP10.txt";

	s = (struct gamers**)malloc(sizeof(struct gamers*) * 10);
	FILE *fp = fopen(fn, "r");
	while (!feof(fp)) {
		if (i == 10) {//10명 다 채우면 끝
			break;
		}
		s[i] = (struct gamers*)malloc(sizeof(struct gamers));
		fscanf(fp, "%s", k);
		ss.name = (char*)malloc(sizeof(char)*(strlen(k) + 1));
		s[i]->name = (char*)malloc(sizeof(char)*(strlen(k) + 1));
		strcpy(ss.name, k);
		fscanf(fp, "%d", &p);
		s[i]->point = p;
		u = i;
		i = i + 1;
		for (t = 0; t < i; ++t)
			if (strcmp(s[t]->name, ss.name) > 0) {
				for (u; t < u; --u) {
					sx.name = (char*)malloc((strlen(s[u - 1]->name) + 1) * sizeof(char));
					strcpy(sx.name, s[u - 1]->name);
					*s[u] = sx;
				}
				*s[u] = ss;
				break;
			}
		if (t == i)
			*s[t - 1] = ss;
	}

	fclose(fp);

	return i;//현재 기록에 저장된 플에이어 수(0<=i<=10) 아래 함수인자 중 top에 해당
}


void user_input_output(char name, int points, struct gamers **s, int top)//게임이 끝나고 점수를 파일에 저장
{
	int i = 0, u, p, t;
	char playername[101];
	struct gamers sx;
	char fn[] = "TOP10.txt";
	FILE *fp;

	gets(playername);//gets가 되게 해주세요.
	for (t = 0; t < top; ++t) {//현재 기록보다 높은 점수일 경우
		if (s[t]->point < points) {
			for (u = 10; t < u; --u) {
				sx.name = (char*)malloc((strlen(s[u - 1]->name) + 1) * sizeof(char));
				strcpy(sx.name, s[u - 1]->name);
				sx.point = s[u - 1]->point;
				*s[u] = sx;
			}
			strcpy(s[t]->name, playername);
			s[t]->point = points;
			break;
		}
		if (top < 10 && top == t) {//높은 점수는 아니지만 top10안에 있는 경우(기록에 저장된 top이 10명 미만일 경우)
			strcpy(s[t]->name, playername);
			s[t]->point = points;
		}
		if (t == 10)//top에서 벗어난 경우
			printf("you are loser lol\n");
	}

	fp = fopen(fn, "w");//변경된 내용을 파일에 저장
	for (i = 0; ; ++i) {
		fprintf(fp, "%s %d\n", s[i]->name, s[i]->point);
		fclose(fp);
	}
	fclose(fp);
	/*
		ifstream logFile2("log.txt");			   //파일 읽기
		ofstream  logFile("log.txt", ios::app);    //파일 쓰기, 내용 추가
		string Rname, stop;
		logFile << name << "   " << point << endl; //파일에 이름, 포인트 쓰기
		cout << "gamers name and point \n\n";
		while (1)
		{
			logFile2 >> Rname;					//파일 읽기
			if (stop == Rname)					//중복 제거
				break;
			cout << setw(12) << Rname << "   ";	//읽은 내용 출력
			logFile2 >> Rname;
			cout << Rname << endl;

			stop = Rname;
		}

		//사용이 끝난 뒤 파일을 닫아줍니다.
		logFile2.close();
		logFile.close();
		cout << "\n\n아무키나 입력하세요\n";
		cin.get();
		*/
	printf("원하는 기능을 입력하시오. 0:종료, 1: 이름 검색, 2: top10점수 검색 ");
	scanf("%d\n", &p);
	if (p == 1)
		intop(top, s);
	if(p == 2)
		toprank(top, s);
}


void intop(int top, struct gamers **s) {
	char Name[100];
	FILE *fp;
	char fn[] = "TOP10.txt";
	int i;

	printf("What's your nickname???: ");
	gets(Name);

	for (i = 0; i < top; ++i) {
		if (strcmp(s[i]->name, Name) == 0)
			printf("%s %d %d위\n", s[i]->name, s[i]->point, i + 1);
	}
	if (i == top)
		printf("your name not in TOP10 LOL\n");

	fclose(fp);
}

void toprank(int top, struct gamers **s) {
	int n, i;

	scanf("%d", &n);

	printf("%d위 점수는 %s %d점\n", i + 1, s[i]->name, s[i]->point);
}
