#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"
#define MAX 40


typedef struct node{
	char nama[50];
	double distance;
	struct node *next;
}node;

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
		if(is_empty() == true){
			sscanf(tmp,"%[^;]s;%d;",baru->nama,baru->distance);
			head = baru;
			tail = head;
			bantu = head;
			now = head;
		}else{
			sscanf(tmp,"%[^;]s;%d;",baru->nama,baru->distance);
			bantu->next=baru;
			bantu = baru;
			tail = baru;
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
	printf("\t1. Tambah Jalur Bus\n\t2. Lihat Jalur Bus\n\t3. Menu Penumpang\n\t4. Selesai\nPilihan: ");
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
		default:
		{
			break;
		}
	}
}

