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
|        ���� ó���� (B+ TREE)       |\n\
|      ������(artwarez@paran.com)    |\n\
+------------------------------------+\n");
	printf("|         B+ Tree�� ���� : %d         |\n", M);
	while (1) {    // �޴�
		printf("\
+------------------------------------+\n\
|        M     E      N     U        |\n\
+------------------------------------+\n\
|      1. B+ TREE Ű�������         |\n\
|      2. B+ TREE �˻�               |\n\
|      3. B+ TREE ����               |\n\
|      4. B+ TREE ���               |\n\
|      5. B+ TREE ����(����)         |\n\
|      6. B+ TREE ���(����)         |\n\
|      7. ����                       |\n\
+------------------------------------+\n\
|   ���� �޴��� �ϳ��� �����ϼ���.   |\n\
+------------------------------------+\n\
         �޴� �Է�(1-5): ");

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
				printf("	���� �����Ͻðڽ��ϱ�?(y/n)");
				gets(buff);
			} while (!strlen(buff));
			if (strcmp(buff, "y") == 0)
				break;
			if (buff != "y")
				system("cls");
		}
	}
}