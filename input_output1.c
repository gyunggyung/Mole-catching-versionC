#include <stdio.h>
#include <string>
#include "input_output1.h"
struct gamers {
	char *name;
	int point;
};
int ReadFile(struct gamers **s) {//���ο��� top10gamers ����ü�����Ҵ� �޾ƿ���, ���� �������� top10gamers �ڷ� �ҷ��� ����ü�� ����
	int i=0, u, p, t;
	char k[101];
	struct gamers ss, sx;
	char fn[] = "TOP10.txt";

	s = (struct gamers**)malloc(sizeof(struct gamers*) * 10);
	FILE *fp = fopen(fn, "r");
	while (!feof(fp)) {
		if (i == 10) {//10�� �� ä��� ��
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

	return i;//���� ��Ͽ� ����� �ÿ��̾� ��(0<=i<=10) �Ʒ� �Լ����� �� top�� �ش�
}


void user_input_output(char name, int points, struct gamers **s, int k)//������ ������ ������ ���Ͽ� ����
{
	int i = 0, u, p, t, top;
	char playername[101];
	struct gamers sx;
	char fn[] = "TOP10.txt";
	FILE *fp;

	gets(playername);//gets�� �ǰ� ���ּ���.
	for (t = 0; t < top; ++t) {//���� ��Ϻ��� ���� ������ ���
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
		if (top < 10 && top == t) {//���� ������ �ƴ����� top10�ȿ� �ִ� ���(��Ͽ� ����� top�� 10�� �̸��� ���)
			strcpy(s[t]->name, playername);
			s[t]->point = points;
		}
		if (t == 10)//top���� ��� ���
			printf("you are loser lol\n");
	}

	fp = fopen(fn, "w");//����� ������ ���Ͽ� ����
	for (i = 0; ; ++i) {
		fprintf(fp, "%s %d\n", s[i]->name, s[i]->point);
		fclose(fp);
	}
	fclose(fp);
	/*
		ifstream logFile2("log.txt");			   //���� �б�
		ofstream  logFile("log.txt", ios::app);    //���� ����, ���� �߰�
		string Rname, stop;
		logFile << name << "   " << point << endl; //���Ͽ� �̸�, ����Ʈ ����
		cout << "gamers name and point \n\n";
		while (1)
		{
			logFile2 >> Rname;					//���� �б�
			if (stop == Rname)					//�ߺ� ����
				break;
			cout << setw(12) << Rname << "   ";	//���� ���� ���
			logFile2 >> Rname;
			cout << Rname << endl;

			stop = Rname;
		}

		//����� ���� �� ������ �ݾ��ݴϴ�.
		logFile2.close();
		logFile.close();
		cout << "\n\n�ƹ�Ű�� �Է��ϼ���\n";
		cin.get();
		*/
	while (1){
		printf("���ϴ� ����� �Է��Ͻÿ�. 0:����, 1: �̸� �˻�, 2: top10���� �˻� \n");
		scanf("%d\n", &p);
		if (p == 1)
			intop(top, s);
		else if (p == 2)
			toprank(top, s);
		else
			break;
	}
}


void intop(int k, struct gamers **s) {
	char Name[100];
	FILE *fp;
	char fn[] = "TOP10.txt";
	int i, top;

	printf("What's your nickname???: ");
	gets(Name);

	for (i = 0; i < top; ++i) {
		if (strcmp(s[i]->name, Name) == 0)
			printf("%s %d %d��\n", s[i]->name, s[i]->point, i + 1);
	}
	if (i == top)
		printf("your name not in TOP10 LOL\n");

	fclose(fp);
}

void toprank(int k, struct gamers **s) {
	int n, i, top;

	scanf("%d", &n);

	printf("%d�� ������ %s %d��\n", i + 1, s[i]->name, s[i]->point);
}
