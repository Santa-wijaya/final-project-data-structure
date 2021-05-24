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
	struct queue *prev;
}queue;

queue seat[MAX];
queue *queue_head = NULL;
node *head = NULL;
node *tail = NULL;
node *now = NULL;

void init_seat(){
	for(int i=0;i<MAX;i++){
		seat[i].seat_resv = 999;
	}
}

void insert_antrian(char nama[],char dest[], char from[], int seat);

void clear();
bool is_full();
unsigned int hash(int *num);
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
	char nama[100];
	char dest[50];
	char from[50];
	int seat;
	bool found = false;
	init_seat();
	read_file();
	do{
		title();
		printf("Menu:\n");
		printf("\t1. Tambah Jalur Bus\n\t2. Lihat Jalur Bus\n\t3. Menu Penumpang\n\t4. Berangkat\n\t5. Reset Jalur\n\t6. Keluar\nPilihan: ");
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
					printf("Masukkan jarak dari kota %s (dalam KM): ",tail->nama);
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
					printf("\t\t3. Masuk Bus\n");
					printf("\t\t4. Keluar\n");
					printf("Pilihan: ");
					scanf("%d",&pil2);
					switch(pil2){
						case 1:
						{
							node *bantu;
							fflush(stdin);
							printf("Masukkan data:\n");
							printf("Nama: ");
							scanf("%100[^\n]s",&nama);
							fflush(stdin);
							strcpy(from,now->nama);
							do{
								fflush(stdin);
								bantu = head;
								printf("Tujuan: ");
								scanf("%50[^\n]s",&dest);
								fflush(stdin);
								while(bantu!=NULL){
									if(strcmp(dest,bantu->nama) == 0){
										found = true;
										break;
									}
									bantu = bantu->next;
								}
							}while(found == false);
							do{
								printf("Kursi yang hendak dipesan: ");
								scanf("%d",&seat);
							}while(seat>=999);
							printf("PERHATIAN!\nKURSI YANG DIPESAN DAPAT SECARA OTOMATIS DI RELOKASI KE KURSI YANG TERSEDIA\nAPABILA KURSI YANG DIPESAN TELAH TERISI!\n");
							insert_antrian(nama,dest,from,seat);
							break;
						}
						case 2:
						{
							seat_view();
							break;
						}
						case 3:
						{
							bus_enter();
							break;
						}
					}
					if(pil2>=1 && pil2<=3)system("pause");
				}while(pil2!=4);
				break;
			}
			case 4:
			{
				depart();
				break;
			}
			case 5:
			{
				head = NULL;
				tail = NULL;
				write();
				break;
			}
			case 6:
			{
				write();
				break;
			}
		}
	if(pil>=1 && pil<=5 && pil2!=3)system("pause");
	pil2 = 0;
	}while(pil!=6);
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
		if(seat[i].seat_resv == 999) return false;
	}
	return true;
}


unsigned int hash(int *num){
	int hash_value = (*num)%MAX;
	return hash_value;
}


void insert_antrian(char nama[],char dest[], char from[], int seat){
	queue *baru = (queue*)malloc(sizeof(queue));
	queue *bantu;

	strcpy(baru->nama,nama);
	strcpy(baru->dest,dest);
	strcpy(baru->from,from);
	baru->seat_resv = seat;
	baru->next=NULL;
	baru->prev=NULL;

	bantu = queue_head;
	if(queue_head == NULL){
		queue_head = baru;
	}else{
		while(bantu->next!=NULL){
			bantu = bantu->next;
		}
		bantu->next = baru;
		baru->prev = bantu;
	}
}

void bus_enter(){
	queue *bantu;
	queue *hapus = (queue*)malloc(sizeof(queue));
	int index;
	bool found = false;

	bantu = queue_head;
	if(is_full() == true) printf("BUS SUDAH PENUH    1!\n");
	else{
		while(bantu!=NULL){
			if(strcmp(now->nama,bantu->from) == 0){
				index = hash(&bantu->seat_resv);
				printf("in %d\n",index);
				for(int i=0;i<MAX;i++){
					if(seat[index].seat_resv == 999){
						found = true;
						break;
					} 
					else{
						index = (index+1)%MAX;
					}
				}
				if(found == false) break;
				else{
					strcpy(seat[index].nama, bantu->nama);
					strcpy(seat[index].dest, bantu->dest);
					strcpy(seat[index].from, bantu->from);
					seat[index].seat_resv = bantu->seat_resv;



					if(bantu == queue_head){
						queue_head = bantu->next;
						hapus = bantu;
						bantu = queue_head;
						free(hapus);
					}else{
						hapus = bantu;
						bantu = bantu->prev;
						bantu->next = hapus->next;
						hapus->next->prev=bantu;
						free(hapus);
						bantu = bantu->next;
					}
				}
				if(found == false) printf("BUS SUDAH PENUH      2!\n");
			
			
			}else{
				bantu = bantu->next;
			}
		found = false;
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
				insert(location,dist);
			}
		}
	}fflush(stdin);
}

void depart(){
	int arrived = 0;
	node *bantu;
	bantu = now;
	bool found = false;
	if(is_empty() == false){
		if(head == tail){
			printf("Bus telah berada di rute terakhir!\n");
		}else if(bantu == tail){
			printf("Bus telah berada di rute terakhir!(Otomatis membalikkan rute...)\n");
			reverse();
		}else{
			int count = 2;
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
			printf("\nBus telah sampai pada kota %s!\n",bantu->nama);
			arrived = 1;
		}
		if(arrived == 1){
			printf("Penumpang yang turun: \n");
			for(int i = 0;i<MAX;i++){
				if(strcmp(seat[i].dest,now->nama) == 0){
					printf("Nama: %s\n",upper(seat[i].nama));
					printf("Kota keberangkatan: %s\n",upper(seat[i].from));
					printf("Kota tujuan: %s\n",upper(seat[i].dest));
					printf("----------------------------------------------\n");
					seat[i].seat_resv = 999;
					found = true;
				}
			}
			if(found == false) printf("--tidak ada penumpang yang turun!--\n");
		}
	}
}
void reverse(){
	node *bantu;
	FILE *fp;
	float buff = 0;
	fp = fopen("databases/kota.txt","w+");
	bantu = tail;
	if(tail == head) printf("Hanya ada 1 kota pada database!\n");
	else{
		while(bantu!=NULL){
			fprintf(fp,"%s;%.2f\n",bantu->nama,buff);
			if(bantu->prev != NULL){
				printf("Jarak kota %s ke %s: ",bantu->nama,bantu->prev->nama);
				scanf("%f",&buff);
			}
			bantu = bantu->prev;
		}
	}
	fclose(fp);
	head = NULL;
	tail = NULL;
	read_file();
}
void seat_view(){
	printf("+----+---------+\n");
	printf("| NO | KONDISI |\n");
	printf("+----+---------+\n");
	for(int i=0;i<MAX;i++){
		if(seat[i].seat_resv == 999){
			printf("| %2d |    -    |\n",i+1);
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
		fprintf(fp,"%s;%.2f\n",bantu->nama,bantu->distance);
		bantu = bantu->next;
	}
	fclose(fp);
}