#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

/*
    3.    ���������� ������� ������ ������� � ���������� ��������, ������� ���������.
*/

struct Node       //��������� ���������� ������ ������
{
        int x;     // �������� x ����� ������������ � ������
        int y;     // �������� y
        Node *next,*prev; // ��������� �� ������ ���������� � ����������� ��������� ������
};


struct List   //������� ��� ������ ������
{
        Node *head;
        Node *tail;  //��������� �� ������ ������ ������ � ��� �����
};


void add( List *list, Node n )
{
        Node *temp = new Node; // ��������� ������ ��� ����� ������� ���������
        temp->next = NULL;       // ���������, ��� ���������� �� ���������� ������ �����
        temp->x = n.x;             // ���������� �������� � ���������
        temp->y = n.y;

        if ( list->head != NULL ) // ���� ������ �� ����
        {
                temp->prev = list->tail; // ��������� ����� �� ���������� ������� � �����. ����
                list->tail->next = temp; // ��������� ����� ���������� �� ������� ��������
                list->tail = temp;       //������ ����� ������
        }
        else //���� ������ ������
        {
                temp->prev = NULL; // ���������� ������� ��������� � �������
                list->head = list->tail = temp;    // ������=�����=��� �������, ��� ������ ��������
        }
}
void print( List * list )
{
        Node * temp = list->head;  // �������� ��������� �� ����� ������� ��������
        while( temp != NULL )      // ���� �� �������� ������ ��������
        {
                cout << "(" << temp->x <<", " << temp->y << ") "; //������� �������� �� �����
                temp = temp->next;     //����� ������ �� ����� ���������� ��������
        }
        cout<<"\n";
}

int find_first( List * list, Node * n) // ����� ������� ���������� - ���������� ������ ��� -1
{
        int i=0;
        Node * temp = list->head;  // �������� ��������� �� ����� ������� ��������
        while( temp != NULL )      // ���� �� �������� ������ ��������
        {
               if (temp->x == n->x && temp->y == n->y) {
                           return i;
               }            
               i++;
               temp = temp->next;
        }
        return -1;
}    
int find_last( List * list, Node * n) // ����� ���������� ���������� - ���������� ������ ��� -1
{
        int i=0;
        int last_find = -1; // ��� ����� ����� ��������� �����
        Node * temp = list->head;  // �������� ��������� �� ����� ������� ��������
        while( temp != NULL )      // ���� �� �������� ������ ��������
        {
               if (temp->x == n->x && temp->y == n->y) {
                                last_find = i;
               }            
               i++;
               temp = temp->next;
        }
        return last_find;
}    


int main()
{

    srand(time(NULL)); //������������� ��������� ��������� �����, ����� ����������� �� �����

    List * my_list = new List;
    my_list->head = my_list->tail = NULL;
    Node * nodes = new Node[20];
    for (int i=0; i<20;i++) {  // ������ 20 ��������� ���������
        nodes[i].x = rand()%100;
        nodes[i].y = rand()%100;
        add(my_list, nodes[i]);
    } 
    print(my_list);  // ������� ������ �� �����
    int rand_ind = rand()%20;  // ��������� ������� ������ ��������
    Node * ff = &nodes[rand_ind];
    cout << "find first (" << ff->x << "," << ff->y << ") found index " << find_first(my_list, ff) << "\n";
    // ��� �������� ������ ���������� �������� ������ - ��������� ���������� �������
    Node * tmp = my_list->tail;
    tmp->x = nodes[0].x;
    tmp->y = nodes[0].y;
    Node * fl = &nodes[0];
    cout << "find last (" << fl->x << "," << fl->y << ") found index " << find_last(my_list, fl) << "\n";

   
    // ����� ���� �� ����������� ����� � ����
    cout << "The end. Enter integer number....";
    int final;
    cin >> final;
    return 0;
}



