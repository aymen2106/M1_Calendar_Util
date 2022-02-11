/*References: https://www.youtube.com/watch?v=oFINZymUK04&t=5s
The reference was printing calendar upto 2020. 
I have added the years upto 2999
/*
In this Calender project,3-important operations are done:
1. Find the day corresponding to a given date.
2. Open full month calendar
3. Add notes  */

#include<stdio.h>
#include<conio.h>
#include<windows.h>
struct Date{
    int dd;
    int mm;
    int yy;
};
struct Date date;

struct Remainder{
    int dd;
    int mm;
    char note[100];
};
struct Remainder R;


COORD xy = {0, 0};

void gotoxy (int x, int y)//This function allows you to print text in any place of screen.//
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

//This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearColor(){
    SetColor(15);
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     //A return value... indicating how many chars were written
     //   not used but we need to capture this since it will be
     //   written anyway (passing NULL causes an access violation).
     DWORD count;

     //This is a structure containing all of the console info
     // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //Set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //Fills the buffer with a given character (in this case 32=space).//
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          //Set our cursor position for the next print statement.
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

int check_leapYear(int year){ //check leap year//
    if(year % 400 == 0 || (year % 100!=0 && year % 4 ==0))
       return 1;
    return 0;
}

void increase_month(int *mm,  int *yy){ //increase month by 1
    ++*mm;
    if(*mm > 12){
        ++*yy;
        *mm = *mm - 12;
    }
}

void decrease_month(int *mm,  int *yy){ //decrease month by 1
    --*mm;
    if(*mm < 1){
        --*yy;
        if(*yy<1600){
            printf("RECORDS NOT AVAILABLE!");
            return;
        }
        *mm = *mm + 12;
    }
}


int getNumberOfDays(int month,int year){ //number of days in the given month
   switch(month){                          //and year
      case 1 : return(31);
      case 2 : if(check_leapYear(year)==1)
		 return(29);
	       else
		 return(28);
      case 3 : return(31);
      case 4 : return(30);
      case 5 : return(31);
      case 6 : return(30);
      case 7 : return(31);
      case 8 : return(31);
      case 9 : return(30);
      case 10: return(31);
      case 11: return(30);
      case 12: return(31);
      default: return(-1);
   }
}

char *getName(int day){ //return name of the day//
   switch(day){
      case 0 :return("SUNDAY!");
      case 1 :return("MONDAY!");
      case 2 :return("TUESDAY!");
      case 3 :return("WEDNESDAY!");
      case 4 :return("THURSDAY!");
      case 5 :return("FRIDAY!");
      case 6 :return("SATURDAY!");
      default:return("Error in getName() module.Invalid argument passed");
   }
}

void print_date(int mm, int yy){ //print name of month and year//
    printf("........................\n");
    gotoxy(25,6);
    switch(mm){
        case 1: printf("JANUARY"); 
		break;
        case 2: printf("FEBRUARY"); 
		break;
        case 3: printf("MARCH"); 
		break;
        case 4: printf("APRIL"); 
		break;
        case 5: printf("MAY"); 
		break;
        case 6: printf("JUNE"); 
		break;
        case 7: printf("JULY"); 
		break;
        case 8: printf("AUGUST"); 
		break;
        case 9: printf("SEPTEMBER"); 
		break;
        case 10: printf("OCTOBER"); 
		break;
        case 11: printf("NOVEMBER"); 
		break;
        case 12: printf("DECEMBER"); 
		break;
    }
    printf(" - %d", yy);
    gotoxy(20,7);
    printf(".........................");
}
int getDayNumber(int day,int mon,int year){ //retuns day number
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while(year >= 100){
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year-1)-t1;
    t1 = (t1*2)+t2;
    t1 = (t1%7);
    res = res + t1;
    res = res%7;
    t2 = 0;
    for(t1 = 1;t1 < mon; t1++){
        t2 += getNumberOfDays(t1,y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if(y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

char *getDay(int dd,int mm,int yy){
    int day;
    if(!(mm>=1 && mm<=12)){
        return("MONTH VALUE IS INVALID!");
    }
    if(!(dd>=1 && dd<=getNumberOfDays(mm,yy))){
        return("DATE IS INVALID!");
    }
    if(yy>=1600){
        day = getDayNumber(dd,mm,yy);
        day = day%7;
        return(getName(day));
    }else{
        return("PLEASE ENTER A YEAR 1600-2999");
    }
}

int checkNote(int dd, int mm){
    FILE *fp;
    fp = fopen("note.dat","rb");
    if(fp == NULL){
        printf("ERROR WHILE OPENING THE FILE!");
    }
    while(fread(&R,sizeof(R),1,fp) == 1){
        if(R.dd == dd && R.mm == mm){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printMonth(int mon,int year,int x,int y){ //print month with days
    int nod, day, cnt, d = 1, x1 = x, y1 = y, isNote = 0;
    if(!(mon>=1 && mon<=12)){
        printf("INVALID MONTH!");
        getch();
        return;
    }
    if(!(year>=1600)){
        printf("INVALID YEAR!");
        getch();
        return;
    }
    gotoxy(999,y);
    print_date(mon,year);
    y += 3;
    gotoxy(x,y);
    printf("S   M   T   W   T   F   S   ");
    y++;
    nod = getNumberOfDays(mon,year);
    day = getDayNumber(d,mon,year);
    switch(day){ //starting day in a calender
        case 0 :
            x=x;
            cnt=1;
            break;
        case 1 :
            x=x+4;
            cnt=2;
            break;
        case 2 :
            x=x+8;
            cnt=3;
            break;
        case 3 :
            x=x+12;
            cnt=4;
            break;
        case 4 :
            x=x+16;
            cnt=5;
            break;
        case 5 :
            x=x+20;
            cnt=6;
            break;
        case 6 :
            x=x+24;
            cnt=7;
            break;
        default :
            printf("INVALID DATA FROM THE getOddNumber()MODULE");
            return;
    }
    gotoxy(x,y);
    if(cnt == 1){
        SetColor(12);
    }
    if(checkNote(d,mon)==1){
            SetColorAndBackground(15,12);
    }
    printf("%02d",d);
    SetColorAndBackground(15,1);
    for(d=2;d<=nod;d++){
        if(cnt%7==0){
            y++;
            cnt=0;
            x=x1-4;
        }
        x = x+4;
        cnt++;
        gotoxy(x,y);
        if(cnt==1){
            SetColor(12);
        }else{
            ClearColor();
        }
        if(checkNote(d,mon)==1){
            SetColorAndBackground(15,12);
        }
        printf("%02d",d);
        SetColorAndBackground(15,1);
    }
    gotoxy(8, y+2);
    SetColor(14);
    printf("Press 'n'  to Next, Press 'p' to Previous and 'q' to Quit");
    gotoxy(8,y+3);
    printf("RED Background indicates the NOTE, Press 's' to see note: ");
    ClearColor();
}

void AddNote(){
    FILE *fp;
    fp = fopen("note.dat","ab+");
    system("cls");
    gotoxy(5,7);
    printf("ENTER THE DATE (DD/MM): ");
    scanf("%d%d",&R.dd, &R.mm);
    gotoxy(5,8);
    printf("ENTER THE NOTE (100-CHARECTAR MAX): ");
    fflush(stdin);
    scanf("%[^\n]",R.note);
    if(fwrite(&R,sizeof(R),1,fp)){
        gotoxy(5,12);
        puts("NOTE SAVED SUCCESSFULLY!");
        fclose(fp);
    }else{
        gotoxy(5,12);
        SetColor(12);
        puts("\aFAILED TO SAVE!!\a");
        ClearColor();
    }
    gotoxy(5,15);
    printf("PRESS ANY KEY........");
    getch();
    fclose(fp);
}

void showNote(int mm){
    FILE *fp;
    int i = 0, isFound = 0;
    system("cls");
    fp = fopen("note.dat","rb");
    if(fp == NULL){
        printf("ERROR WHILE OPENING THE FILE!");
    }
    while(fread(&R,sizeof(R),1,fp) == 1){
        if(R.mm == mm){
            gotoxy(10,5+i);
            printf("NOTE %d DAY = %d: %s", i+1, R.dd,  R.note);
            isFound = 1;
            i++;
        }
    }
    if(isFound == 0){
        gotoxy(10,5);
        printf("THIS MONTH DOES NOT CONTAINS ANY NOTE!");
    }
    gotoxy(10,7+i);
    printf("PRESS ANY KEY TO GO BACK.......");
    getch();

}
//Main function starts here//
int main(){
    ClearConsoleToColors(15, 1);
    SetConsoleTitle("THE CALENDAR PROJECT - MOHMAD AYMEN NAQASH");
    int choice;
    char ch = 'a';
    while(1){
        system("cls");
        printf("CALENDAR 1600 TO 2999\n");
        printf("1. FIND OUT THE DAY FOR A GIVEN DATE\n");
        printf("2. TO PRINT All THE DAYS OF A MONTH\n");
        printf("3. TO ADD A NOTE\n");
        printf("4. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d",&choice);
        system("cls");
        switch(choice){
            case 1://Find the day which you want to search//
                printf("ENTER DATE (DD MM YYYY) : ");
                scanf("%d %d %d",&date.dd,&date.mm,&date.yy);
                printf("DAY IS : %s",getDay(date.dd,date.mm,date.yy));
                printf("\nPRESS ANY KEY TO CONTINUE...");
                getch();
                break;
            case 2 ://print all the days of a month//
                printf("ENTER MONTH AND YEAR (MM YYYY) : ");
                scanf("%d %d",&date.mm,&date.yy);
                system("cls");
                while(ch!='q'){
                    printMonth(date.mm,date.yy,20,5);
                    ch = getch();
                    if(ch == 'n'){
                        increase_month(&date.mm,&date.yy);
                        system("cls");
                        printMonth(date.mm,date.yy,20,5);
                    }else if(ch == 'p'){
                        decrease_month(&date.mm,&date.yy);
                        system("cls");
                        printMonth(date.mm,date.yy,20,5);
                    }else if(ch == 's'){
                        showNote(date.mm);
                        system("cls");
                    }
                }
                break;
            case 3://add the Note//
                AddNote();
                break;
            case 4 ://exit
                exit(0);
        }
    }
    return 0;
}//end of main
