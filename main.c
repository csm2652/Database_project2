#include "bpt.c"
#define file_path "data.db"
int main() {

	if (0 == access(file_path, F_OK))
	{
		open_db(file_path);
	}
	else {
		open_db(file_path);
		Header_Page_init();
	}

	
	char buff[2];
	int choice;
	head = NULL;
	printf("\
+------------------------------------+\n\
|        파일 처리론 (B+ TREE)       |\n\
|      신현범(artwarez@paran.com)    |\n\
+------------------------------------+\n");
	printf("|         B+ Tree의 차수 : %d         |\n", M);
	while (1) {    // 메뉴
		printf("\
+------------------------------------+\n\
|        M     E      N     U        |\n\
+------------------------------------+\n\
|      1. B+ TREE 키보드삽입         |\n\
|      2. B+ TREE 검색               |\n\
|      3. B+ TREE 삭제               |\n\
|      4. B+ TREE 출력               |\n\
|      5. B+ TREE 삽입(파일)         |\n\
|      6. B+ TREE 출력(파일)         |\n\
|      7. 종료                       |\n\
+------------------------------------+\n\
|   위의 메뉴중 하나를 선택하세요.   |\n\
+------------------------------------+\n\
         메뉴 입력(1-5): ");

		choice = (gets(buff));
		switch (choice)
		{
		case '1':
			system("cls");
			insertkey();
			clrscr();
			break;
		case '2':
			system("cls");
			findkey();
			clrscr();
			break;

		case '3':
			system("cls");
			delkey();
			clrscr();
			break;

		case '4':
			system("cls");
			printall();
			clrscr();
			break;

		case '5':
			system("cls");
			insertfile();
			clrscr();
			break;

		case '6':
			system("cls");
			printfile();
			clrscr();
			break;

		case '7':
			break;

		default:

			system("cls");
			break;
		}

		if (strcmp(buff, "7") == 0)
		{
			do {
				printf("	정말 종료하시겠습니까?(y/n)");
				gets(buff);
			} while (!strlen(buff));
			if (strcmp(buff, "y") == 0)
				break;
			if (buff != "y")
				system("cls");
		}
	}
}