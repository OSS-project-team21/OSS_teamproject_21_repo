// OSS mini project team 21 (신경식 신건훈)

#include <stdio.h>
#include <string.h>

typedef struct{
    char name[30]; // 메뉴 이름
    int price; // 메뉴 가격
    int payment; // 결제 수단 -  1 : 카드 / 2 : 푸드포인트 / 3 : 현금 
    int take_out; // 포장 유무 - 1 : 포장 / 2 : 포장안함.
    int id_num; // 학번
    int orderNum; //포장 대기번호

} Menu;

int selectDataNo(Menu *s, int count);
void listMenu(Menu *s , int count);
int addMenu(Menu *s, int count);
void readMenu(Menu s);
int updateMenu(Menu *s, int count);
int deleteMenu(Menu *s); 
void searchMenu( Menu *s , int count);
void paymentMethod(Menu *s);
void takeOut(Menu *s, int count);
void saveFile(Menu *s, int count);
void loadFile(Menu *s, int count);

int selectMenu(){     
    int menu;
    printf("\n***** 학관 메뉴 *****\n");
    printf("1. 메뉴 조회\n");
    printf("2. 메뉴 추가\n");
    printf("3. 메뉴 수정\n");
    printf("4. 메뉴 삭제\n");
    printf("5. 파일저장\n");
    printf("6. 메뉴 이름검색\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}
int main(void){
    Menu slist[20];
    int count = 0, menu;
    int index = 0;
    FILE *file;
    if((file=fopen("menu.txt","rt"))){
      printf("==>로딩 성공");
      while(!feof(file)){
          char c=getc(file);
          if(c=='\n'){
              count++;
          }
      }
      loadFile(slist,count);
    }
    else{
      printf("==>파일 없음");
    }
    index = count;

    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1){
            if(count > 0)
                listMenu(slist , index);
            else
                printf("데이터가 없습니다.\n");
        }
        else if (menu == 2){
            count += addMenu(&slist[index++], count);

        }
        else if (menu == 3){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("=> 취소됨!\n");
                continue;
            }
            updateMenu(&slist[no-1], count);
        }
        else if (menu == 4){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("=> 취소됨!\n");
                continue;
            }
            int deletok;
            printf("정말로 삭제하시겠습니까? (삭제 :1)");
            scanf("%d", &deletok);
            if(deletok == 1){
                if(deleteMenu(&slist[no-1])) count--;
            }
        }
        else if( menu == 5){
            saveFile(slist , index);
        }
        else if( menu == 6){
            searchMenu(slist , index); 
        }
    }
    printf("종료됨!\n");
    return 0;
}
void readMenu(Menu s){

    printf("  < %s > \n",s.name);
    printf("가격 : %d\n",s.price);
    if(s.payment == 1)
        printf("결제수단 : 카드\n");
    else if(s.payment == 2){
        printf("결제수단 : 푸드포인트\n");
        printf("학생번호 : %d\n", s.id_num);
    }
    else
        printf("결제수단 : 현금\n");
    if(s.take_out == 1){
        printf("포장유무 : 포장\n");
        printf("포장번호 : %d\n", s.orderNum);
    }
    else
        printf("포장유무 : 포장안함\n");  
}
int addMenu(Menu *s, int count){

    printf("메뉴이름은? ");
    scanf("%s",s->name);
    printf("가격은? ");
    scanf("%d",&s->price);
    printf("결제수단은? (카드:1, 푸드포인트:2, 현금:3) ");
    scanf("%d",&s->payment);
    if(s->payment==2){
        paymentMethod(s);
    }
    printf("포장은? (포장:1, 포장안함: 2) ");
    scanf("%d",&s->take_out);
    if(s->take_out==1){
        takeOut(s, count);
    }
    printf("=>추가됨!\n");
    return 1;
}
int updateMenu(Menu *s, int count){


    printf("메뉴이름은? ");
    scanf("%s",s->name);
    printf("가격은? ");
    scanf("%d",&s->price);
    printf("결제수단은? (카드:1, 푸드포인트:2, 현금:3) ");
    scanf("%d",&s->payment);
    if(s->payment==2){
        paymentMethod(s);
    }
    printf("포장은? (포장:1, 포장안함: 2) ");
    scanf("%d",&s->take_out);
    if(s->take_out==1){
        takeOut(s, count);
    }
    printf("=> 수정됨!\n");

    return 0;
}
int deleteMenu(Menu *s){
    s->price = -1;
    s->payment = -1;
    s->take_out = -1;
    s->id_num = -1;
    s->orderNum = 0;
    printf("삭제됨!\n"); 

    return 1;
} 
void listMenu(Menu *s , int count){
    printf("================================\n");
    for(int i=0; i<count; i++){
        if(s[i].price == -1) continue;
        printf("====== %d번 menu ======\n",i+1);
        readMenu(s[i]);
    }
    printf("\n");
}
int selectDataNo(Menu *s, int count){
    int no;
    listMenu(s, count);
    printf("번호는 (취소 :0)? ");
    scanf("%d",&no);
    return no;
}
void searchMenu(Menu *s , int count){
    int scnt = 0;
    char search[20];

    printf("검색할 메뉴이름? ");
    scanf("%s",search);

    printf("================================\n");
    for( int i=0; i<count; i++){
        if(s[i].price == -1) continue;
        if(strstr(s[i].name,search)){
            printf("====== %d번 menu ======\n",i+1);
            readMenu(s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}
void saveFile(Menu *s, int count){
    FILE *fp;
    fp=fopen("menu.txt", "wt");
    for(int i=0; i<count;i++){
        fprintf(fp,"%s %d %d %d %d %d", s[i].name, s[i].price,
            s[i].payment, s[i].id_num, s[i].take_out, 
            s[i].orderNum);
    }
    printf("파일 저장!\n");
}
void loadFile(Menu *s, int count){
    FILE *fp;
    fp=fopen("menu.txt", "r");
    for(int i=0; i<count;i++){
        fscanf(fp,"%s %d %d %d %d %d", s[i].name, &s[i].price,
            &s[i].payment, &s[i].id_num, &s[i].take_out, 
            &s[i].orderNum);
    }
}
void paymentMethod(Menu *s){
    printf("학번은? : ");
    scanf("%d", &s->id_num);
}
void takeOut(Menu *s, int count){
    int x=0;
    for(int i=0;i<count;i++){
        if(s[i].take_out==1){
            x++;
        }
    }
    s->orderNum=x;
    printf("포장번호 : %d", s->orderNum);
}