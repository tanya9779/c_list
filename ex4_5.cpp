#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

/*
      4.    ���������� ������� ������� �������� � ��������� ������� � ������.
      5.    ���������� ������� �������� �������� �� ��������� ������� � ������.

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

//      4.    ���������� ������� ������� �������� � ��������� ������� � ������.

void insert(List * list, int index, Node * n) // ������� ������ �������� � ������� index
{                                           // ���� ����� ������� ��� �� � ����� ������

    Node *temp = new Node; // ��������� ������ ��� ����� ������� ���������
    temp->next = NULL;       // ���������, ��� ���������� �� ���������� ������ �����
    temp->x = n->x;             // ���������� �������� � ���������
    temp->y = n->y;
    int i =0;
    Node * current = list->head;  // �������� ��������� �� ����� ������� ��������
    while (i<index && current) { // ���� ���� ��� ����������
        current = current->next; // ��������� � ����������
        i++;
    }
    if (current) { // ��������� ����� ������� ����� current, �������� ������
        current->prev->next = temp; 
        temp->prev = current->prev;
        current->prev = temp;
        temp->next = current;
        if (list->head == current) {
             list->head = temp;
        }               
    }
    else { // ������� � �����
        add(list, *n); // � ��� ��� ���� ������� ����������
    }
}

void list_delete(List * list, int index) // ������� �� ������ ������� � ������� index
{
    int i =0;
    Node * current = list->head;   // �������� ��������� �� ����� ������� ��������
    while (i<index && current) {  // ���� ���� ��� ����������                     
        current = current->next;  // ��������� � ����������                       
        i++;
    }
    if (current) { // ������� ������� current, �������� ������ � ���� �����
         if (current->prev) {
             current->prev->next = current->next;
         }    
         if (current->next) {
             current->next->prev = current->prev;
         }    
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
    Node * nn = new Node;
    nn->x = rand()%1000+100;
    nn->y = rand()%1000+100;
    insert(my_list, rand_ind, nn);
    cout << "INSERT NEW NODE IN " << rand_ind << " POSITION" << endl;
    // ������� ���������� ������ �� �����
    print(my_list);  // ������� ������ �� �����
    rand_ind = rand()%20;  // ������ ��������� ������� ������ ��������
    cout << "DELETE NODE IN " << rand_ind << " POSITION" << endl;
    list_delete(my_list, rand_ind);
    // ������� ���������� ������ �� �����
    print(my_list);  // ������� ������ �� �����
    
    // ����� ���� �� ����������� ����� � ����
    cout << "The end. Enter integer number....";
    int final;
    cin >> final;
    return 0;
}



