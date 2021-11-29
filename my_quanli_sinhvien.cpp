#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct date{
	int ngay;
	int thang;
	int nam;
};
struct sinhvien{
	int id;
	char lop[5];
	char ten[20];
	date ngaysinh;
	int tuoi;
	float diemmon1;
	float diemmon2;
	float diemmon3;
	float diemtrungbinh;
	char hocluc[12];
	
};
void xoaxuongdong(char x[]){	//<------------------------xoa xuong dong  
	size_t len=strlen(x);
	if(x[len-1]=='\n')
		x[len-1]='\0';
}
typedef sinhvien SV;

void tinhtuoi(SV &sv){			//<--------------------------tinh tuoi 
	time_t TIME= time(0);
	tm* now=localtime(&TIME);
	int thoigianhientai=now->tm_year +1900;
	sv.tuoi=thoigianhientai-sv.ngaysinh.nam;
}

void tinhdiemtb(SV &sv ){
	sv.diemtrungbinh=(sv.diemmon1+sv.diemmon2+sv.diemmon3)/3;	//<-------tinh diem trung binh
}
void xeploai(SV &sv){
	if(sv.diemtrungbinh>=8)
		strcpy(sv.hocluc,"GIOI");
	if(sv.diemtrungbinh<8 && sv.diemtrungbinh>=6.5)
		strcpy(sv.hocluc,"TRUNG BINH");
	if(sv.diemtrungbinh<6.5)
		strcpy(sv.hocluc,"YEU");
}

void nhapthongtin(SV &sv){
	printf("\nID :"); scanf("%d",&sv.id);
	printf("Lop :");fflush(stdin);fgets(sv.lop,sizeof(sv.lop),stdin);xoaxuongdong(sv.lop);	//<-------------nhap thong tin
	printf("Ten :");fflush(stdin);fgets(sv.ten,sizeof(sv.ten),stdin);xoaxuongdong(sv.ten);
	printf("Ngay sinh :\n");scanf("%d%d%d",&sv.ngaysinh.ngay,&sv.ngaysinh.thang,&sv.ngaysinh.nam);
	printf("diem mon 1 :");scanf("%f",&sv.diemmon1);
	printf("diem mon 2 :");scanf("%f",&sv.diemmon2);
	printf("diem mon 3 :");scanf("%f",&sv.diemmon3);
	
}
void xuatthongtin(SV sv){
	printf("%3d \t %3s \t %20s \t %3d/%d/%d \t %5d \t %5.2f \t\t %5.2f \t\t %5.2f \t\t %5.2f \t\t %10s",sv.id,sv.lop,sv.ten,sv.ngaysinh.ngay,sv.ngaysinh.thang,sv.ngaysinh.nam,sv.tuoi,sv.diemmon1,sv.diemmon2,sv.diemmon3,sv.diemtrungbinh,sv.hocluc);
	printf("\n");					//<-------------------------------------------------------xuat thong tin
}
void capnhatsinhvien(SV &sv){		//<----------cap nhat sinh vien
	nhapthongtin(sv);
	tinhtuoi(sv);
	tinhdiemtb(sv);
	xeploai(sv);
}
void nhapdanhsach(SV ds[], int &n){		// sai o day/ thieu&
	do{
		printf("nhap so luong sinh vien :");		//<-------------nhap danh sach sinh vien
		scanf("%d",&n);
	}while(n<=0);
	for(int i=0 ; i<n ;i++){
		printf("sinh vien thu %d :",i+1);
		capnhatsinhvien(ds[i]);
	}
}
void xuatdanhsach(SV ds[],int n){
	printf("%3s \t %3s \t %20s \t %10s \t %5s \t %5s\t %2s \t %2s \t %2s \t %10s ","ID","Lop","Ten","Ngaysinh","Tuoi","Diemmon1","Diemmon2","Diemmon3","Diemtrungbinh","Hocluc");
	printf("\n");
	for(int i=0; i<n; i++){		//<--------------------------------xuat danh sach sinh vien
		xuatthongtin(ds[i])	;
	}
}

void sapxeptheodiemtb(SV ds[], int n){
	for(int i=0;i<n-1;i++){
		int j;
		for(j=i+1;j<n;j++){
			if(ds[i].diemtrungbinh<ds[j].diemtrungbinh){		//<--------------------sap xep theo diem trung binh
				SV temp;
				temp= ds[i];
				ds[i]=ds[j];
				ds[j]=temp;
			}
		}
	}
}
float timmaxdiemtb(SV ds[] ,int n){			//<--------------------------tim max diem trung binh
	float max=ds[0].diemtrungbinh;
	for(int i=1;i<n;i++){
		if(ds[i].diemtrungbinh>max){
			max=ds[i].diemtrungbinh;
		}
	}
	return max;
}

int timmintuoi(SV ds[],int n){		//<-----------------------------------tim min tuoi
	int min=ds[0].tuoi;
	for(int i=1;i<n;i++){
		if(min>ds[i].tuoi){
			min=ds[i].tuoi;
		}
	}
	return min;
}

int timsinhvientheoten(SV ds[],int n, char ten[20]){		//<-------------tim sinh vien theo ten
	printf("%3s \t %3s \t %20s \t %10s \t %5s \t %5s\t %2s \t %2s \t %2s \t %10s ","ID","Lop","Ten","Ngaysinh","Tuoi","Diemmon1","Diemmon2","Diemmon3","Diemtrungbinh","Hocluc");
	printf("\n");
	for(int i=0;i<n;i++){
		if(strcmp(strlwr(ten),strlwr(ds[i].ten))==0){
			xuatthongtin(ds[i]);
		}
	}
}

void xoasinhvientheoid(SV ds[], int &n, int id){
	for(int i=0; i<n; i++){
		if(ds[i].id==id){
			for(int j=i; j<n; j++){
				ds[j]=ds[j+1];
			}
			n-=1;
			return;
		}
	}
}

void sapxeptheoten(SV ds[],int n){
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(strcmp(strlwr(ds[i].ten),strlwr(ds[j].ten))>0){
				SV temp;
				temp=ds[i];
				ds[i]=ds[j];
				ds[j]=temp;			
			}
		}
	}
}
void timsinhvientheohocluc(SV ds[], int n, char hocluc[12]){
	printf("%3s \t %3s \t %20s \t %10s \t %5s \t %5s\t %2s \t %2s \t %2s \t %10s ","ID","Lop","Ten","Ngaysinh","Tuoi","Diemmon1","Diemmon2","Diemmon3","Diemtrungbinh","Hocluc");
	printf("\n");
	for(int i=0; i<n; i++){
		if(strcmp(strupr(ds[i].hocluc),strupr(hocluc))==0){
			xuatthongtin(ds[i]);
		}
	}
}

void ghivaofile(SV ds[],int n){
	char tenfile[100];
	printf("nhap duong dan :");
	fflush(stdin);fgets(tenfile,sizeof(tenfile),stdin);xoaxuongdong(tenfile);
	FILE *fp;
	fp=fopen(tenfile,"wb");
	if(fp==NULL){
		printf("loi mo file !");
		return;
	}
	fwrite(&n,sizeof(n),1,fp);
	for(int i=0;i<n; i++){
		fwrite(&ds[i],sizeof(SV),1,fp);
	}
	fclose(fp);
}
void nhaptufile(SV ds[],int &n){
	char tenfile[100];
	printf("nhap duong dan :");
	fflush(stdin);fgets(tenfile,sizeof(tenfile),stdin);xoaxuongdong(tenfile);
	FILE *fp;
	fp=fopen(tenfile,"rb");
	if(fp==NULL){
		printf("loi mo file !");
		return;
	}
	fread(&n,sizeof(n),1,fp);
	for(int i=0;i<n;i++){
		fread(&ds[i],sizeof(SV),1,fp);		//sai o day/ fp chu khong phai stdin
	}
	fclose(fp);
}


void nhapphimbatki(){
	 printf("\nNhap phim bat ki de tiep tuc !");		//<---------nhap phim bat ki
	 getch();
}
int main(){
	SV ds[100];		//sai o day/ SV ds[] chu khong phai SV sv
	int n;
	int chon;
	char tensv[20];
	int id;
	char hocluc[12];
	do{
		printf("\nMENU\n");
		printf("1-nhap danh sach sinh vien \n");
		printf("2-in danh sach sinh vien \n");
		printf("3-sap xep danh sach theo diem trung binh \n");
		printf("4-tim diem trung binh cao nhat\n");
		printf("5-tim tuoi be nhat\n");
		printf("6-tim sinh vien theo ten\n");
		printf("7-xoa sinh vien theo id\n");
		printf("8-sap xep danh sach theo ten\n");
		printf("9-tim sinh vien theo hoc luc\n");
		printf("10-in danh sach vao file\n");
		printf("11-nhap danh sach tu file\n");
		printf("moi nhap lua chon cua ban :");
		scanf("%d",&chon);
		switch(chon){
			case 1:
				nhapdanhsach(ds,n);
				nhapphimbatki();
				break;
			case 2:
				xuatdanhsach(ds,n);
				nhapphimbatki();
				break;
			case 3:
				sapxeptheodiemtb(ds,n);
				xuatdanhsach(ds,n);
				nhapphimbatki();
				break;
			case 4:
				printf("diem trung binh lon nhat la : %.2f",timmaxdiemtb(ds,n)); //sai o day/ %f chu khong phai %d
				nhapphimbatki();
				break;
			case 5:
				printf("tuoi nho nhat la : %d",timmintuoi(ds,n));
				nhapphimbatki();
				break;
			case 6:
				printf("nhap ten sinh vien can tim :");
				fflush(stdin); fgets(tensv,sizeof(tensv),stdin);xoaxuongdong(tensv);
				timsinhvientheoten(ds,n,tensv);
				nhapphimbatki();
				break;
			case 7:
				printf("nhap id sinh vien can xoa :");
				scanf("%d",&id);
				xoasinhvientheoid(ds,n,id);
				xuatdanhsach(ds,n);
				nhapphimbatki();
				break;
			case 8:
				sapxeptheoten(ds,n);
				xuatdanhsach(ds,n);
				nhapphimbatki();
				break;
			case 9:
				
				printf("nhap hoc luc cua hoc sinh can tim :");
				fflush(stdin);fgets(hocluc,sizeof(hocluc),stdin);xoaxuongdong(hocluc);
				timsinhvientheohocluc(ds,n,hocluc);
				nhapphimbatki();
				break;
			case 10:
				ghivaofile(ds,n);
				nhapphimbatki();
				break;
			case 11:
				nhaptufile(ds,n);
				nhapphimbatki();
				break;
				
			default :
				printf("ban hay nhap dung lua chon !");	
		}
		
	}while(chon!=0);
	return 0;
}
