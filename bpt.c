#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define true 1
#define false 0
#define MM 15 //이값으로 차수 변경
#define M (MM * 2 +1) //홀수 차수 생성
#define one_page 4096
int open_db(char *pathname);
int insert(int64_t key, char* value);
char *find(int64_t key);
int delete(int64_t key);
void clrscr();	// 화면을 클리어 하는 함수 (출력 화면과 입력 화면을 구분시켜줌 ^^:)

extern int fd;
extern Header_Page *head;

typedef struct Page_Getter {
	char bytes[0x1000];
}Page_Getter;
typedef struct record
{
	int64_t key;
	char value[120];
}record;
typedef struct i_record {
	int64_t key;
	int64_t page_offset;
}i_record;
typedef struct Header_Page {
	int64_t free_page_off;
	int64_t root_page_off;
	int64_t number_of_page;
	char Reserved[4072];
}Header_Page;

typedef struct Free_Page
{
	int64_t Next_Free_Page_Offset;
}Free_Page;

typedef struct Leaf_Page
{
	int64_t Parent_Page_Offset;
	int isLeaf;
	int Number_of_Keys;
	int64_t Reserved[13];
	int64_t Right_Sibling_Page_Offset;
	record record_arr[31];
}Leaf_Page;

typedef struct Internal_Page
{
	int64_t Parent_Page_Offset;
	int isLeaf;
	int Number_of_Keys;
	int64_t Reserved[13];
	int64_t Front_child_offset;
	i_record i_record_arr[248];
}Internal_Page;

void Header_Page_init()
{
	Header_Page *init_header = malloc(sizeof(Header_Page));
	memset(init_header, 0, sizeof(Header_Page));
	init_header->free_page_off = one_page * 1;
	init_header->root_page_off = one_page * 5;
	init_header->number_of_page = 1;

	pwrite(fd, init_header, sizeof(Header_Page),0);
}

void Free_Page_init(int64_t Next_offset)
{

}

void Print_All(int64_t offset) {
	printf("\n");
	Leaf_Page *leaf;
	Internal_Page *internal;
	Page_Getter *block = malloc(sizeof(Page_Getter));
	pread(fd, &block, sizeof(Page_Getter), head->root_page_off);
	internal = block;
	if (internal->isLeaf == true) {
		leaf = internal;
		int j;
		for (j = 0; j < leaf->Number_of_Keys; j++) {
			printf("%d | ", leaf->record_arr[j].key);
		}
	}
	else {
		int i;
		for (i = 0; i < internal->Number_of_Keys; i++) {
			if (i == 0) {
				printf("%d | ", internal->i_record_arr[i]);
				Print_All(internal->Front_child_offset);
			}
			else {
				printf("%d | ", internal->i_record_arr[i]);
				Print_All(internal->i_record_arr[i].page_offset);
			}
		}
	}
}

Leaf_Page* Leaf_Page_init(int64_t parent_offset, int64_t right_sibling_offset)
{
	Leaf_Page *init_leaf = malloc(sizeof(Leaf_Page));
	init_leaf->Number_of_Keys = 0;
	init_leaf->isLeaf = true;
	init_leaf->Parent_Page_Offset = parent_offset;
	init_leaf->Right_Sibling_Page_Offset = right_sibling_offset;
	return init_leaf;
}
Internal_Page* Internal_Page_init(int64_t parent_offset, int64_t front_page_offset)
{
	Internal_Page *init_internal = malloc(sizeof(Internal_Page));
	init_internal->isLeaf = false;
	init_internal->Number_of_Keys = 0;
	init_internal->Parent_Page_Offset = parent_offset;
	init_internal->Front_child_offset = front_page_offset;
	return init_internal;
}

int open_db(char *pathname)
{
	fd = open(pathname, O_RDWR | O_CREAT | O_SYNC, 0666);
	if (fd == -1) {
		printf("FD ERROR....\n");
		return -1;
	}
	else {
		printf("FD Succes..! fd is : %d\n", fd);
		return 0;
	}
}
int insert_split(int64_t key, Page_Getter* block) {

}
int insert_downside(int64_t key, Page_Getter* block) {

}
int insert(int64_t key, char* value)//성공시 0리턴,실패시 -1
{
	record insert;
	insert.key = key;
	memcpy(insert.value, value, 120);
	Leaf_Page *leaf;
	Internal_Page *internal;
	Page_Getter *block = malloc(sizeof(Page_Getter));
	Page_Getter *block2 = malloc(sizeof(Page_Getter));

	pread(fd, &block, sizeof(Page_Getter),head->root_page_off);
	internal = block;
	if (internal->isLeaf == true) {
		leaf = internal;
		memcpy(leaf->record_arr + leaf->Number_of_Keys, &insert, sizeof(record));
	}
	else {
		int j;
		for (j = 0; j < internal->Number_of_Keys; j++) {
			if (j == 0 && key < internal->i_record_arr[j].key) {
				insert_downside(key, block2);
			}
			if (key < internal->i_record_arr[j].key) {
				
			}
		}
	}

}
char *find(int64_t key)// 성공시 value 리턴 실패시 NULL;
{
	Leaf_Page *leaf;
	Internal_Page *internal;
	Page_Getter *block = malloc(sizeof(Page_Getter));
	pread(fd, &block, head->root_page_off, sizeof(Page_Getter));
	internal = block;
	if (internal->isLeaf == true) {
		leaf = internal;

		while (1) {
			int j;
			for (j = 0; j < leaf->Number_of_Keys; j++) {
				if (key == leaf->record_arr[j].key)
					return leaf->record_arr[j].value;
			}
		}
	}
	else {
		while (1) {
			int i;
			for (i = 0; i < internal->Number_of_Keys; i++) {
				if (key < internal->i_record_arr[i].key) {
					return findkey(key, internal->i_record_arr[i].page_offset);
					//pread(fd, block, sizeof(Page_Getter), internal->i_record_arr[i].page_offset);
				}
			}
		}
	}	
}
char *findkey(int64_t key, int64_t offset) {
	
	Leaf_Page *leaf;
	Internal_Page *internal;
	Page_Getter *block = malloc(sizeof(Page_Getter));
	pread(fd, &block, sizeof(Page_Getter), offset);
	internal = block;
	if (internal->isLeaf == true) {
		leaf = internal;

		while (1) {
			int j;
			for (j = 0; j < leaf->Number_of_Keys; j++) {
				if (key == leaf->record_arr[j].key)
					return leaf->record_arr[j].value;
			}
		}
	}
	else {
		while (1) {
			int i;
			for (i = 0; i < internal->Number_of_Keys;i++ ) {
				if (key < internal->i_record_arr[i].key) {
					if (i == 0) {
						return findkey(key, internal->Front_child_offset);
					}
					else {
						return findkey(key, internal->i_record_arr[i - 1].page_offset);	
					}
					break;
				}
				else if (key == internal->i_record_arr[i].key)
					return findkey(key, internal->i_record_arr[i].page_offset);
			}
		}
	}
}
int delete(int64_t key)// 성공시 0리턴, 실패시 -1;
{

}