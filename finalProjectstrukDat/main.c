#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAX 40

//int init_seat = 0;
typedef struct node{
	char nama[50];
	float distance;
	struct node *next;
	struct node *prev;
}node;

typedef struct queue{
	char nama[150];
	char from[50];
	char dest[50];
	int seat_resv;
	struct queue *next;
}queue;

queue *seat[MAX];
queue *queue_head = NULL;
node *head = NULL;
node *tail = NULL;
node *now = NULL;

void clear();
bool is_full();
unsigned int hash(int *num);
void antri();
void bus_enter();
bool is_empty();
void insert(char namae[], float dist);
void read_file();
void display();
void depart();
void reverse();
void seat_view();
void title();
char* lower(char str[]);
char* upper(char str[]);
void write();

int main(){
	int pil,pil2;
	char location[50];
	float dist;
	read_file();
	do{
		title();
		printf("Menu:\n");
		printf("\t1. Tambah Jalur Bus\n\t2. Lihat Jalur Bus\n\t3. Menu Penumpang\n\t4. Berangkat\n\t5. Selesai\nPilihan: ");
		scanf("%d",&pil);
		switch(pil){
			case 1:
			{
				display();
				printf("Masukkan data kota: \n");
				if(is_empty() == true){
					fflush(stdin);
					printf("Nama Kota Awal: ");
					scanf("%[^\n]s",&location);
					lower(location);
					printf("\n");
					fflush(stdin);
				}else{
					fflush(stdin);
					printf("Nama kota: ");
					scanf("%[^\n]s",&location);
					lower(location);
					fflush(stdin);
					printf("Masukkan jarak dari kota %s (dalam KM)",tail->nama);
					scanf("%f",&dist);

				}
				insert(location,dist);
				break;
			}
			case 2:
			{
				display();
				break;
			}
			case 3:
			{
				do{
					title();
					printf("Menu Penumpang: \n");
					printf("\t\t1. Antri\n");
					printf("\t\t2. Lihat isi bus\n");
					printf("\t\t3. Keluar\n");
					printf("Pilihan: ");
					scanf("%d",&pil2);
					switch(pil2){
						case 1:
						{
							antri();
							break;
						}
						case 2:
						{
							seat_view();
							break;
						}
					}
					if(pil2 == 1 || pil2 == 2)system("pause");
				}while(pil2!=3);
			}
			case 4:
			{
				depart();
				break;
			}
			case 5:
			{
				//write();
				break;
			}
		}
	if(pil>=1 && pil<=4 && pil2!=3)system("pause");
	pil2 = 0;
	}while(pil!=5);
}

void clear(){
	#ifdef _WIN32
		std: system("cls");
	#else
		std: system("clear");
	#endif
}

bool is_full(){
	for(int i = 0; i<MAX;i++){
		if(seat[i] == NULL) return false;
	}
	return true;
}


unsigned int hash(int *num){
	int hash_value = (*num)%MAX;
	return hash_value;
}

void antri(){
	queue *baru = (queue*)malloc(sizeof(queue));
	queue *bantu;
	node *bantu2;
	int found = 0;
	fflush(stdin);
	if(is_empty() == false){
		printf("Masukkan nama: ");
		scanf("%[^\n]s",&baru->nama);
		lower(baru->nama);
		fflush(stdin);
		while(1){

			printf("Masukkan destinasi: ");
			scanf("%[^\n]s",&baru->dest);
			lower(baru->dest);
			fflush(stdin);
			while(bantu2 != NULL){
				if(strcmp(baru->dest,bantu2->nama) == 0) found = 1;
			}
			if(found == 1) break;
		}
		printf("Masukkan nomor kursi yang hendak diduduki: ");
		scanf("%d",&baru->seat_resv);
		strcpy(baru->from,now->nama);
		baru->next = NULL;
		bantu = queue_head;
		if(queue_head == NULL){
			queue_head = baru;
		}else{
			while(bantu->next!=NULL){
				bantu = bantu->next;
			}
			bantu->next = baru;
		}
	}else{
		printf("Belum ada jalur bus! harap tambahkan jalur...\n");
	}
}

void bus_enter(){
	queue *bantu;
	int index;
	if(is_full() == true){
		printf("Bus sudah penuh! harap gunakan bus lain!\n");
	}else{
		bantu = queue_head;
		while(bantu != NULL){
			if(is_full() == true){
				printf("Bus sudah penuh! harap gunakan bus lain!\n");
			}
			if(strcmp(bantu->from,now->nama) == 0){
				index = hash(&bantu->seat_resv);
				if(bantu->seat_resv>MAX){
					printf("Karena kursi %d tidak ada, maka akan dialihkan ke kursi lain jika tersedia!\n",bantu->seat_resv);
				}else{
					printf("Apabila kursi %d sudah terisi, akan otomatis dialihkan ke kursi lain!\n",bantu->seat_resv);
				}
				while(seat[index] != NULL){
					index = index+1;
				}
				seat[index] = bantu;
			}
		}
	}
}


bool is_empty(){
	if(head == NULL) return true;
	else return false;
}

void insert(char namae[], float dist){
	char tmp[100];
	node *baru = (node*)malloc(sizeof(node));
	strcpy(baru->nama,namae);
	baru->next=NULL;
	baru->prev=NULL;
	if(is_empty() == true){
		baru->distance = 0;
		head = baru;
		tail = head;
		now = head;
	}else{
		baru->distance = dist;
		tail->next = baru;
		baru->prev=tail;
		tail = baru;
	}
	fflush(stdin);
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
				printf("\nMasukkan minimal 2 kota!\n");
				break;
			}else if(bantu == head){
				printf("%s--",bantu->nama);
				bantu = bantu->next;
			}else if(bantu == tail){
				printf("%.2f km--%s\n",bantu->distance,bantu->nama);
				break;
			}else{
				printf("%.2f km--%s--",bantu->distance,bantu->nama);
				bantu = bantu->next;
			}
		}
	}
}

void read_file(){
	FILE *fp;
	char tmp[100];
	char location[50];
	float dist;
	fp = fopen("databases/kota.txt","r");
	if(fp == NULL){
		printf("Database \"kota.txt\" Not Found!\n");
	}else{
		while(fgets(tmp,100,fp)!=NULL){
			fflush(stdin);
			if(strcmp(" ",tmp)!=0){
				sscanf(tmp,"%[^;];%f\n",location,&dist);
				printf("%s %.2f\n",location,dist);
				insert(location,dist);
			}
		}
	}fflush(stdin);
	system("pause");
}

void depart(){
	int arrived = 0;
	node *bantu;
	if(is_empty() == false){
		if(head == tail){
			printf("Bus telah berada di rute terakhir!\n");
		}else if(bantu == tail){
			printf("Bus telah berada di rute terakhir!(Otomatis membalikkan rute...)\n");
			reverse();
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
			arrived = 1;
		}
		if(arrived == 1){
			printf("Penumpang yang turun: \n");
			for(int i = 0;i<MAX;i++){
				if(strcmp(seat[i]->dest,now->nama) == 0){
					printf("Nama: %s\n",upper(seat[i]->nama));
					printf("Kota keberangkatan: %s\n",upper(seat[i]->from));
					printf("Kota tujuan: %s\n",upper(seat[i]->dest));
					printf("----------------------------------------------\n");
					seat[i] = NULL;
				}
			}
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
void seat_view(){
	printf("+----+---------+\n");
	printf("| NO | KONDISI |\n");
	printf("+----+---------+\n");
	for(int i=0;i<MAX;i++){
		if(seat[i] == NULL){
			printf("| %2d | KOSONG  |\n",i+1);
		}else{
			printf("| %2d | TERISI  |\n",i+1);
		}
	}
	printf("+----+---------+\n");
}

void title(){
	clear();
	printf("+------------------------------------------------------------+\n");
	printf("|                 PROGRAM SIMULASI BUS KOTA                  |\n");
	printf("+------------------------------------------------------------+\n");
}

char* lower(char str[]){
   int i;
   for(i=0;i<=strlen(str);i++){
      if(str[i]>=65&&str[i]<=90)
         str[i]=str[i]+32;
   }
    return str;
}
char* upper(char str[]){
    int i;
    for (i = 0; str[i]!='\0'; i++) {
      if(str[i] >= 'a' && str[i] <= 'z') {
         str[i] = str[i] - 32;
      }
   }
    return str;
}

void write(){
	node *bantu;
	FILE *fp;
	fp = fopen("./databases/kota.txt","w");
	bantu = head;
	while(bantu!=NULL){
		fprintf(fp,"%s;%.2f;\n",bantu->nama,bantu->distance);
		bantu = bantu->next;
	}
	fclose(fp);
}