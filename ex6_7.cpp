#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

/*
6.    ���������� �������, ������������ ��� �������� ������, ��������������� ���������� ��������, 
      � ���� ���������� ������. �������� ������ ������������ ��� ��������� �� �������, ����������� 
      � �������� ��������� ������� ������.
7.    ��������� ��� �� ����������� �������, ����������� ������ 5 ��������� ������, ������� ��������� 
      ����� ����� � ������ ���� ����� ������. ���������� ������ ���� ����������� ��� ������� 
      �������������� ��������� ���� �����.

*/

int average_x, average_y; // ��� ���������� ���������� - ���������� ������ ����� 

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
int is_in_range(Node n, r_min, r_max) { // ���������, �������� �� ����� n � ������ [r_min; r_max)
    // �� ����� ����� ���������� ������ - ��� ����� ������� (r_mix � r_max ��� ���� ��������)
    // �������� ������� ���������� 
    int r = (n.x-average_x)**2 + (n.y-average_y)**2;
    if (r_min <= r < r_max)
        return 1;
    return 0;

}

List * filter(List * l) { // �������-������ ������ ������ �� ��� 5 ���������, ������� �����
                          // ���� � ������ ����
    List * result = new List;
    result->head = result->tail = NULL;
    max_r = 0;
    Node * current = l->head;
    for (int i=0; i<20; i++) { ��������� ������� ������������� ���������� �� ������
        int r = (current->x - average_x)**2 + (current->y - average_y)**2; 
        if (max_r <r) 
            max_r = r;
    }
    int count = 0; // ������� �� 5
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
    // ��������� ����� ������ ����
    average_x = average_y =0;
    for (int i=0;i<20;i++) {
         average_x += nodes[i].x;
         average_y += nodes[i].y;
    }
    average_x = (int) (average_x/20);
    average_y = (int) (average_y/20);
    cout << "AVERAGE X,Y = (" << average_x << ", " << average_y << ")" << endl;

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



