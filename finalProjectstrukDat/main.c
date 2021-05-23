#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"

#define MAX 40

void clear(){
	#ifdef _WIN32
		std: system("cls");
	#else
		std: system("clear");
	#endif
}
typedef struct node{
	char nama[50];
	double distance;
	struct node *next;
	struct node *prev;
}node;

typedef struct queue{
	char nama[150];
	char from[50];
	char dest[50];
	struct queue *next;
}queue;

bool is_full(){
	for(int i = 0; i<MAX;i++){
		if(seat[i] == NULL) return false;
	}
	return true;
}

queue *seat[MAX];

unsigned int hash(int *num){
	int hash_value = (*num)%MAX;
	return hash_value;
}


void bus_enter(){
	if(is_full() == true){
		printf("Bus sudah penuh! harap gunakan bus lain!\n");
	}else{

	}
}

node *head = NULL;
node *tail = NULL;
node *now = NULL;

bool is_empty(){
	if(head == NULL) return true;
	else return false;
}

void insert(){
	char tmp[100];
	node *baru = (node*)malloc(sizeof(node));
	baru->next=NULL;
	baru->prev=NULL;
	printf("Masukkan data kota: \n");
	if(is_empty() == true){
		printf("Nama Kota Awal: ");
		scanf("%[^\n]s",&baru->nama);
		baru->distance = 0;
		head = baru;
		tail = head;
		now = head;
	}else{
		printf("Nama kota: ");
		scanf("%[^\n]s",&baru->nama);
		printf("Masukkan jarak dari kota %s (dalam KM)",tail->nama);
		scanf("%f",&tail->distance);
		tail->next = baru;
		baru->prev=tail;
		tail = baru;
	}
}

void read_file(){
	FILE *fp;
	node *bantu;
	node *baru = (node*)malloc(sizeof(node*));
	char tmp[5];
	fp = fopen("./databases/kota.txt","a+");
	while(fgets(tmp,50,fp)!=NULL){
		if(strcmp(tmp," ") != 0){
			if(is_empty() == true){
				sscanf(tmp,"%[^;]s;%d\n",baru->nama,baru->distance);
				baru->next=NULL;
				baru->prev=NULL;
				head = baru;
				tail = head;
				bantu = head;
				now = head;
			}else{
				sscanf(tmp,"%[^;]s;%d\n",baru->nama,baru->distance);
				bantu->next=baru;
				baru->prev=bantu;
				bantu = baru;
				tail = baru;
			}
		}
	}
	fclose(fp);
}

void display(){
	node *bantu;
	printf("Jalur Bus saat ini: \n");
	bantu = head;
	if(bantu == NULL){
		printf("-----KOSONG-----\n");
		printf("Harap input rute bus terlebih dahulu!\n");
	}else{
		while(bantu!=NULL){
			if(head == tail && bantu == tail){
				printf("%s",bantu->nama);
				printf("Masukkan minimal 2 kota!\n");
			}else if(bantu == head){
				printf("%s--",bantu->nama);
				bantu = bantu->next;
			}else if(bantu == tail){
				printf("%f km--%s",bantu->distance,bantu->nama);
			}else{
				printf("%f km--%s--",bantu->distance,bantu->nama);
				bantu = bantu->next;
			}
		}
	}
}

void depart(){
	node *bantu;
	if(is_empty() == false){
		if(bantu == tail){
			printf("Bus telah berada di rute terakhir!\n");
		}else{
			int count = 3;
			while(count!=0){
				title();
				printf("Bus berangkat ");
				for(int i=0;i<5;i++){
					sleep(1);
					printf(". ");
				}
				count = count - 1;
			}
			bantu = bantu->next;
			now = bantu;
			printf("Bus telah sampai pada kota %s!",bantu->nama);
		}
	}
}
void reverse(){
	node *bantu;
	FILE *fp;
	fp = fopen("databases/kota.txt","w+");
	bantu = tail;
	if(tail == head) printf("Hanya ada 1 kota pada database!\n");
	else{
		while(tail!=head){
			fprintf(fp,"%s;%f\n",bantu->nama,bantu->distance);
			tail = tail->prev;
		}
	}
	fclose(fp);
	read_file();
}

void title(){
	printf("+------------------------------------------------------------+\n");
	printf("|                 PROGRAM SIMULASI BUS KOTA                  |\n");
	printf("+------------------------------------------------------------+\n");
}

int main(){
	int pil,pil2;
	read_file();
	title();
	printf("Menu:\n");
	printf("\t1. Tambah Jalur Bus\n\t2. Lihat Jalur Bus\n\t3. Menu Penumpang\n\t4. Berangkat\n\t5. Selesai\nPilihan: ");
	scanf("%d",&pil);
	switch(pil){
		case 1:
		{
			display();
			insert();
			break;
		}
		case 2:
		{
			display();
			break;
		}
		case 3:
		{
			printf("Menu Penumpang: \n");
			printf("\t\t1. Antri\n");
			printf("\t\t2. Lihat isi bus\n");
			printf("\t\t3. Keluar\n");
			printf("Pilihan: ");
			scanf("%d",&pil2);
			switch(pil2){
				case 1:
				{
					break;
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					break;
				}
				default:{
					break;
				}
			}
		}
		case 4:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

