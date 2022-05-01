
// OSS mini project team 21 (�Ű�� �Ű���)

#include <stdio.h>
#include <string.h>

typedef struct{
    char name[30]; // �޴� �̸�
    int price; // �޴� ����
    int payment; // ���� ���� -  1 : ī�� / 2 : Ǫ������Ʈ / 3 : ���� 
    int take_out; // ���� ���� - 1 : ���� / 2 : �������.
} Menu;

int selectDataNo(Menu *s, int count);
void listMenu(Menu *s , int count);
int addMenu(Menu *s);
void readMenu(Menu s);
int updateMenu(Menu *s);
int deleteMenu(Menu *s); 
void searchMenu( Menu *s , int count);
//void saveData(Menu *s , int count);
//int loadData(Menu *s);

int selectMenu(){     
    int menu;
    printf("\n***** �а� �޴� *****\n");
    printf("1. �޴� ��ȸ\n");
    printf("2. �޴� �߰�\n");
    printf("3. �޴� ����\n");
    printf("4. �޴� ����\n");
    printf("5. ��������\n");
    printf("6. �޴� �̸��˻�\n");
    printf("0. ����\n\n");
    printf("=> ���ϴ� �޴���? ");
    scanf("%d", &menu);
    return menu;
}
int main(void){
    Menu slist[20];
    int count = 0, menu;
    int index = 0;

    //count = loadData(slist);
    index = count;

    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1){
            if(count > 0)
                listMenu(slist , index);
            else
                printf("�����Ͱ� �����ϴ�.\n");
        }
        else if (menu == 2){
            count += addMenu(&slist[index++]);

        }
        else if (menu == 3){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("=> ��ҵ�!\n");
                continue;
            }
            updateMenu(&slist[no-1]);
        }
        else if (menu == 4){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("=> ��ҵ�!\n");
                continue;
            }
            int deletok;
            printf("������ �����Ͻðڽ��ϱ�? (���� :1)");
            scanf("%d", &deletok);
            if(deletok == 1){
                if(deleteMenu(&slist[no-1])) count--;
            }
        }
        else if( menu == 5){
            //saveData(slist , index);
        }
        else if( menu == 6){
            searchMenu(slist , index); 
        }
    }
    printf("�����!\n");
    return 0;
}

void readMenu(Menu s){

    printf("  < %s > \n",s.name);
    printf("���� : %d\n",s.price);
    if(s.payment == 1)
        printf("�������� : ī��\n");
    else if(s.payment == 2)
        printf("�������� : Ǫ������Ʈ\n");
    else
        printf("�������� : ����\n");
    if(s.take_out == 1)
        printf("�������� : ����\n");
    else
        printf("�������� : �������\n");  
}

int addMenu(Menu *s){

    printf("�޴��̸���? ");
    scanf("%s",s->name);
    printf("������? ");
    scanf("%d",&s->price);
    printf("����������? (ī��:1, Ǫ������Ʈ:2, ����:3) ");
    scanf("%d",&s->payment);
    printf("������? (����:1, �������: 2) ");
    scanf("%d",&s->take_out);
    printf("=>�߰���!\n");
    return 1;
}

int updateMenu(Menu *s){


    printf("�޴��̸���? ");
    scanf("%s",s->name);
    printf("������? ");
    scanf("%d",&s->price);
    printf("����������? (ī��:1, Ǫ������Ʈ:2, ����:3) ");
    scanf("%d",&s->payment);
    printf("������? (����:1, �������: 2) ");
    scanf("%d",&s->take_out);
    printf("=> ������!\n");

    return 0;
}

int deleteMenu(Menu *s){
    s->price = -1;
    s->payment = -1;
    s->take_out = -1;
    printf("������!\n"); 

    return 1;
} 

void listMenu(Menu *s , int count){
    printf("================================\n");
    for(int i=0; i<count; i++){
        if(s[i].price == -1) continue;
        printf("====== %d�� menu ======\n",i+1);
        readMenu(s[i]);
    }
    printf("\n");
}

int selectDataNo(Menu *s, int count){
    int no;
    listMenu(s, count);
    printf("��ȣ�� (��� :0)? ");
    scanf("%d",&no);
    return no;
}



void searchMenu( Menu *s , int count){
    int scnt = 0;
    char search[20];

    printf("�˻��� �޴��̸�? ");
    scanf("%s",search);

    printf("================================\n");
    for( int i=0; i<count; i++){
        if(s[i].price == -1) continue;
        if(strstr(s[i].name,search)){
            printf("====== %d�� menu ======\n",i+1);
            readMenu(s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> �˻��� ������ ����!");
    printf("\n");
}