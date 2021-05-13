#include <iostream>
using namespace std;
class Vector
{
private:
    int size;
    int* arr;
public:
    class Iterator
    {
    private:
        int*it;
    public:
        Iterator(int *temp):it(temp){};
        Iterator & operator++(){
            it++;
            return *this;
        }
        Iterator  operator++(int){
            Iterator temp(it);
            it++;
            return temp;
        }
        Iterator & operator--(){
            it--;
            return *this;
        }
        Iterator & operator--(int){
            Iterator temp(it);
            it--;
            return temp;
        }
        Iterator operator+(int n){
            it+=n;
            return *this;
        }
        int&operator*()
        {
            return *it;
        }
        int *operator->(){
            return it;
        }
        bool operator>=(const Iterator &it2){
            return it>=it2.it;
        }
        bool operator<=(const Iterator &it2){
            return it<=it2.it;
        }
        bool operator==(const Iterator &it2){
            return it==it2.it;
        }
        bool operator!=(const Iterator &it2){
            return it!=it2.it;
        }
    };
    Iterator begin(){
        return Iterator(&arr[0]);
    }
    Iterator end(){
        return Iterator(&arr[size]);
    }
    Vector(const Vector& other);
    Vector(const initializer_list<int> &list);
    Vector();
    int& operator[](const int index);
    void Resize(int n);
    int Size();
    Vector  operator=(const Vector& other);
    void Push_back(int number);
    void Push_front(int number);
    void Insert_at_index(int number, int index);
    void Pop_back();
    void Delete_at_index(int index);
    void Delete_array();
    bool Empty();
    int Find_index(int number);
    ~Vector();
};
void Vector ::Push_back(int number)
{
    int* arr2 = new int[size + 1];
    for (int i = 0; i < size; i++) {
        arr2[i] = arr[i];
    }
    arr2[size] = number;
    size++;
    delete[]arr;
    arr = arr2;
}
void Vector::Push_front(int number)
{
    int* arr2 = new int[size + 1];
    arr2[0] = number;
    for (int i = 1; i < size + 1; i++) {
        arr2[i] = arr[i - 1];
    }
    size++;
    delete[]arr;
    arr = arr2;
}
void Vector::Insert_at_index(int number, int index)
{
    if (index == 0) {
        Push_front(number);
        return;
    }
    if (index == size - 1) {
        Push_back(number);
        return;
    }
    int* arr2 = new int[size + 1];
    for (int i = 0; i < index; i++) {
        arr2[i] = arr[i];
    }
    arr2[index] = number;
    for (int i = index; i < size + 1; i++) {
        arr2[i + 1] = arr[i];
    }
    size++;
    delete[]arr;
    arr = arr2;
}

void Vector::Pop_back()
{
    int* arr2 = new int[size - 1];
    for (int i = 0; i < size - 1; i++) {
        arr2[i] = arr[i];
    }
    size--;
    arr = arr2;
    delete[]arr;
    arr = arr2;
}
void Vector ::Delete_at_index(int index)
{
    if (size != 0) {
        int* arr2 = new int[size - 1];
        for (int i = 0; i < index; i++) {
            arr2[i] = arr[i];
        }
        for (int i = index + 1; i < size; i++) {
            arr2[i - 1] = arr[i];
        }
        size--;
        delete[]arr;
        arr = arr2;
    }
}
void Vector::Delete_array()
{
    int* arr2 = new int[0];
    size = 0;
    delete[]arr;
    arr = arr2;
}
int Vector::Find_index(int number)
{
    int element;
    for (int i = 0; i < size; i++) {
        if (arr[i] == number) {
            element = i;
        }
    }
    return element;
}
Vector::Vector(const Vector& other)
{
    size = other.size;
    arr = new int[other.size];
    for (int i = 0; i < other.size; i++) {
        arr[i] = other.arr[i];
    }
}
Vector::Vector()
{
    size = 0;
    arr = new int[size];
}
Vector::Vector(const initializer_list<int> &list)
{
    size=list.size();
    arr=new int[size];
    int count=0;
    for(auto element:list){
        arr[count]=element;
        count++;
    }
}
Vector Vector:: operator=(const Vector& other)
{
    delete[]arr;
    size = other.size;
    for (int i = 0; i < other.size; i++) {
        arr[i] = other.arr[i];
    }
    delete[]other.arr;
    return *this;
}
void Vector::Resize(int n)
{
    if(size<n){
        int *arr2=new int[n];
        for(int i=0;i<n;i++){
            if(i<size){
                arr2[i]=arr[i];
            }
            else{
                arr2[i]= 0;
            }
        }
        size=n;
        delete[]arr;
        arr=arr2;
    }else{
        int *arr2=new int[n];
        for(int i=0;i<n;i++){
            arr2[i]=arr[i];
        }
        size=n;
        delete[]arr;
        arr=arr2;
    }
}
int Vector::Size()
{
    return this->size;
}
bool Vector::Empty()
{
    if(size==0){
        return true;
    }else return false;
}
int& Vector:: operator[](const int index)
{
    return arr[index];
}
Vector::~Vector()
{
    delete []arr;
    
}
int main(int argc, const char* argv[]) {
    Vector arr;
    arr.Push_back(5);
    arr.Push_back(7);
    arr.Push_back(3);
    for (int i = 0; i < 3; i++) {
        cout << arr[i];
    }
    cout << endl;
    Vector arr2={2,4,5,6};
    for (int i = 0; i < 4; i++) {
        cout << arr2[i];
    }
    cout<<endl;
    arr2.Resize(5);
    for (int i = 0; i < 5; i++) {
        cout << arr2[i];
    }
    auto It=Vector::Iterator(arr.begin());
    for(;It!=arr.end();It++){
        cout<<*It;
    }
    return 0;
}


