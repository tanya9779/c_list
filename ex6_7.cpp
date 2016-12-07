#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

/*
6.    Реализуйте функцию, возвращающую все элементы списка, удовлетворяющие некоторому критерию, 
      в виде отдельного списка. Критерий должен передаваться как указатель на функцию, принимающую 
      в качестве параметра элемент списка.
7.    Используя код из предыдущего задания, рачечатайте первые 5 элементов списка, которые находятся 
      ближе всего к центру масс точек списка. Координаты центра масс вычисляются как среднее 
      арифметическое координат всех точек.

*/

int average_x, average_y; // это глобальные переменные - координаты центра массс 

struct Node       //Структура являющаяся звеном списка
{
        int x;     // Значение x будет передаваться в список
        int y;     // Значение y
        Node *next,*prev; // Указатели на адреса следующего и предыдущего элементов списка
};


struct List   //Создаем тип данных Список
{
        Node *head;
        Node *tail;  //Указатели на адреса начала списка и его конца
};


void add( List *list, Node n )
{
        Node *temp = new Node; // Выделение памяти под новый элемент структуры
        temp->next = NULL;       // Указываем, что изначально по следующему адресу пусто
        temp->x = n.x;             // Записываем значение в структуру
        temp->y = n.y;

        if ( list->head != NULL ) // Если список не пуст
        {
                temp->prev = list->tail; // Указываем адрес на предыдущий элемент в соотв. поле
                list->tail->next = temp; // Указываем адрес следующего за хвостом элемента
                list->tail = temp;       //Меняем адрес хвоста
        }
        else //Если список пустой
        {
                temp->prev = NULL; // Предыдущий элемент указывает в пустоту
                list->head = list->tail = temp;    // Голова=Хвост=тот элемент, что сейчас добавили
        }
}

//      4.    Реализуйте функцию вставки элемента в указанную позицию в списке.

void insert(List * list, int index, Node * n) // вставка нового элемента в позицию index
{                                           // если такой позиции нет то в конец списка

    Node *temp = new Node; // Выделение памяти под новый элемент структуры
    temp->next = NULL;       // Указываем, что изначально по следующему адресу пусто
    temp->x = n->x;             // Записываем значение в структуру
    temp->y = n->y;
    int i =0;
    Node * current = list->head;  // Временно указываем на адрес первого элемента
    while (i<index && current) { // пока есть что перебирать
        current = current->next; // двигаемся к следующему
        i++;
    }
    if (current) { // вставляем новый элемент перед current, разрывая список
        current->prev->next = temp; 
        temp->prev = current->prev;
        current->prev = temp;
        temp->next = current;
        if (list->head == current) {
             list->head = temp;
        }               
    }
    else { // вставка в конец
        add(list, *n); // у нас уже есть функция добавления
    }
}

void list_delete(List * list, int index) // уделяет из списка элемент с номером index
{
    int i =0;
    Node * current = list->head;   // Временно указываем на адрес первого элемента
    while (i<index && current) {  // пока есть что перебирать                     
        current = current->next;  // двигаемся к следующему                       
        i++;
    }
    if (current) { // удаляем элемент current, соединяя список в этом месте
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
        Node * temp = list->head;  // Временно указываем на адрес первого элемента
        while( temp != NULL )      // Пока не встретим пустое значение
        {
                cout << "(" << temp->x <<", " << temp->y << ") "; //Выводим значение на экран
                temp = temp->next;     //Смена адреса на адрес следующего элемента
        }
        cout<<"\n";
}
int find_first( List * list, Node * n) // поиск первого совпадения - возвращает индекс или -1
{
        int i=0;
        Node * temp = list->head;  // Временно указываем на адрес первого элемента
        while( temp != NULL )      // Пока не встретим пустое значение
        {
               if (temp->x == n->x && temp->y == n->y) {
                           return i;
               }            
               i++;
               temp = temp->next;
        }
        return -1;
}    
int find_last( List * list, Node * n) // поиск последнего совпадения - возвращает индекс или -1
{
        int i=0;
        int last_find = -1; // нам нужно самый последний найти
        Node * temp = list->head;  // Временно указываем на адрес первого элемента
        while( temp != NULL )      // Пока не встретим пустое значение
        {
               if (temp->x == n->x && temp->y == n->y) {
                                last_find = i;
               }            
               i++;
               temp = temp->next;
        }
        return last_find;
}    
int is_in_range(Node n, r_min, r_max) { // проверяет, попадает ли точка n в кольцо [r_min; r_max)
    // не будем брать квадратный корень - нам важен порядок (r_mix и r_max это тоже квадраты)
    // вычислим квадрат расстояния 
    int r = (n.x-average_x)**2 + (n.y-average_y)**2;
    if (r_min <= r < r_max)
        return 1;
    return 0;

}

List * filter(List * l) { // функция-фильтр вернет список из тех 5 элементов, которые ближе
                          // всех к центру масс
    List * result = new List;
    result->head = result->tail = NULL;
    max_r = 0;
    Node * current = l->head;
    for (int i=0; i<20; i++) { посчитаем квадрат максимального расстояния от центра
        int r = (current->x - average_x)**2 + (current->y - average_y)**2; 
        if (max_r <r) 
            max_r = r;
    }
    int count = 0; // считаем до 5
}

int main()
{

    srand(time(NULL)); //перезапускаем генератор случайных чисел, иначе случайности не будет

    List * my_list = new List;
    my_list->head = my_list->tail = NULL;
    Node * nodes = new Node[20];
    for (int i=0; i<20;i++) {  // первые 20 элементов случайный
        nodes[i].x = rand()%100;
        nodes[i].y = rand()%100;
        add(my_list, nodes[i]);
    } 
    print(my_list);  // выведем массив на экран
    // посчитаем коорд центра масс
    average_x = average_y =0;
    for (int i=0;i<20;i++) {
         average_x += nodes[i].x;
         average_y += nodes[i].y;
    }
    average_x = (int) (average_x/20);
    average_y = (int) (average_y/20);
    cout << "AVERAGE X,Y = (" << average_x << ", " << average_y << ")" << endl;

    int rand_ind = rand()%20;  // случайный элемент списка выбираем
    Node * nn = new Node;
    nn->x = rand()%1000+100;
    nn->y = rand()%1000+100;
    insert(my_list, rand_ind, nn);
    cout << "INSERT NEW NODE IN " << rand_ind << " POSITION" << endl;
    // выведем измененный массив на экран
    print(my_list);  // выведем массив на экран
    rand_ind = rand()%20;  // другой случайный элемент списка выбираем
    cout << "DELETE NODE IN " << rand_ind << " POSITION" << endl;
    list_delete(my_list, rand_ind);
    // выведем измененный массив на экран
    print(my_list);  // выведем массив на экран
    
    // чтобы окно не закрывалось сразу у меня
    cout << "The end. Enter integer number....";
    int final;
    cin >> final;
    return 0;
}



