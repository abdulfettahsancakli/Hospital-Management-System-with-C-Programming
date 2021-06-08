#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>



struct patient{
    char IDNumber[12];
    char name[30];
    char address[20];
    char bloodType[20]; 
    char gender[20]; 
    char contactPersonName[20];
    long unsigned int phone_no;
};
struct patient _pat;
void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = {0, 0};
     DWORD count;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; 
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void window(){
    drawRectangle();
    gotoxy(24,2);
    SetColor(50);
    printf("Hospital Management System");
    gotoxy(20,3);
    printf("ABDULFETTAH HOSPITAL, ISTANBUL, TURKEY");
    gotoxy(35,4);
    printf("2020");
    gotoxy(25,24);
    SetColor(17);

}
void print_heading(const char st[]){
    SetColorAndBackground(31,20);
    gotoxy(45,8);printf("HMS : %s",st);
    SetColorAndBackground(17,15);
}

void add_patient(){
    clearWindow();
    print_heading("Add Record");
    int print = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("IDNumber: ");gets(_pat.IDNumber);
        gotoxy(print,12);printf("Name: ");gets(_pat.name);
        gotoxy(print,14);printf("Address: ");gets(_pat.address);
        gotoxy(print,16);printf("Blood Type: ");gets(_pat.bloodType);
        gotoxy(print,18);printf("Gender: ");gets(_pat.gender);
        gotoxy(print,20);printf("Contact Person Name: ");gets(_pat.contactPersonName);
        gotoxy(print,22);printf("Phone Number: ");scanf("%d",&_pat.phone_no);
        fwrite(&_pat, sizeof(_pat), 1, fp);
        gotoxy(40,24); printf("%s's record is sucessfully added", _pat.name);
    }
    SetColor(28);
    fclose(fp);
    return;
}
void search_patient(){
    clearWindow();
    print_heading("Search Record");
    SetColor(45);
    char p_IDNumber[12];
    int isFound = 0;
    gotoxy(37,10);printf("Enter IDNumber to Search: ");fflush(stdin);
    gets(p_IDNumber);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&_pat,sizeof(_pat),1,fp) == 1){
        if(strcmp(p_IDNumber,_pat.IDNumber) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("The record is Found");
        gotoxy(37,14);printf("IDNumber: %s",_pat.IDNumber);
        gotoxy(37,15);printf("Name: %s",_pat.name);
        gotoxy(37,16);printf("Address: %s",_pat.address);
        gotoxy(37,17);printf("Blood Type: %s",_pat.bloodType);
        gotoxy(37,18);printf("Gender: %s",_pat.gender);
        gotoxy(37,19);printf("Contat Person Name: %s",_pat.contactPersonName);
        gotoxy(37,20);printf("Phone No: %1d",_pat.phone_no);
    }else{
        gotoxy(37,12);printf("Sory, No record found in the database");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void modify_patient(){
    clearWindow();
    print_heading("Modify Record");
    SetColor(45);
    char p_IDNumber[12];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter IDNumber to Modify: ");fflush(stdin);
    gets(p_IDNumber);
    FILE *fp;
    fp = fopen("record.txt","rb+");
    while(fread(&_pat, sizeof(_pat),1,fp) == 1){
        if(strcmp(p_IDNumber, _pat.IDNumber) == 0){
            fflush(stdin);
            gotoxy(print,12);printf("IDNumber: ");gets(_pat.IDNumber);
            gotoxy(print,13);printf("Name: ");gets(_pat.name);
            gotoxy(print,14);printf("Address: ");gets(_pat.address);
            gotoxy(print,15);printf("Blood Type: ");gets(_pat.bloodType);
            gotoxy(print,16);printf("Gender: ");gets(_pat.gender);
            gotoxy(print,17);printf("Contat Person Name: ");gets(_pat.contactPersonName);
            gotoxy(print,18);printf("Phone Number: ");scanf("%ld",&_pat.phone_no);
            fseek(fp,-sizeof(_pat), SEEK_CUR);
            fwrite(&_pat,sizeof(_pat), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
    }
    fclose(fp);
    SetColor(28);
    return;
}

void delete_patient(){
    clearWindow();
    print_heading("Delete Record");
    SetColor(45);
    char p_IDNumber[12];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter ID to Delete: ");fflush(stdin);
    gets(p_IDNumber);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&_pat, sizeof(_pat),1,fp) == 1){
        if(strcmp(p_IDNumber, _pat.IDNumber) != 0){
            fwrite(&_pat,sizeof(_pat),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(37,12);printf("The record is sucessfully deleted");
    SetColor(28);
    return;
}





void main_window(){
    int choice;
    SetColor(28);
    int x = 2;
    while(1){
        gotoxy(x,8); printf("1. Record Patient");
        gotoxy(x,10);printf("2. Search Patient");
        gotoxy(x,12);printf("3. Modify Patient Record");
        gotoxy(x,14);printf("4. Delete Patient");
        gotoxy(x,20);printf("5. Exit");
        gotoxy(x,22);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_patient();
                break;
            case 2:
                search_patient();
                break;
            case 3:
                modify_patient();
                break;
            case 4:
            	delete_patient();
                break;           
            case 5:
                exit(0);
                break;
            default:
                break;
        }

    }

}




int main(){
	ClearConsoleToColors(17,15); 
    window(); 
    main_window();
    return 0;
}

