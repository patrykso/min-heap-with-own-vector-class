#include <iostream>
#include <string>

using namespace std;

class Person {
    int day, month, year;
    string name, date;
    void setIntDate(string date);
public:
    Person();
    Person(string name, string date);
    string getName();
    string getDate();
    int getDay();
    int getMonth();
    int getYear();
    void print();
};

Person::Person() {
    Person("null", "00-00-0000");
}

Person::Person(string name, string date) {
    this->name = name;
    this->date = date;
    setIntDate(date);
}

void Person::setIntDate(string date) {
    string copy = date.substr(0, 2);
    this->day = stoi(copy);
    copy = date.substr(3, 2);
    this->month = stoi(copy);
    copy = date.substr(6, 4);
    this->year = stoi(copy);
}

string Person::getName() {
    return this->name;
}

string Person::getDate() {
    return this->date;
}

int Person::getDay() {
    return this->day;
}

int Person::getMonth() {
    return this->month;
}

int Person::getYear() {
    return this->year;
}

void Person::print() {
    cout << this->date << " " << this->name;
}

class Vector {
    Person* array;
    int size;
    int maxSize;
    int comparator; //0 for names, 1 for dates
    int parent(int i);
    int left(int i);
    int right(int i);
    int compareNames(Person person1, Person person2);
    int compareDates(Person person1, Person person2);
    void swap(int first, int second);
    void heapify(int i);
    void push(Person person);
public:
    Vector();
    ~Vector();
    Person get(int index);
    void print();
    void changeComparator();
    void removeMin();
    void buildHeap();
    void heapInsert(Person person);
};

Vector::Vector() {
    size = 0;
    comparator = 0;
    maxSize = 1;
    array = new Person[maxSize];
}

Person Vector::get(int index) {
    if (index < size) return array[index];
    return array[0];
}

void Vector::print() {
    for (int i = 0; i < size; i++) {
        array[i].print();
        cout << endl;
    }
}

void Vector::swap(int first, int second) {
    Person tmp = get(first);
    array[first] = array[second];
    array[second] = tmp;
}

Vector::~Vector() {
    delete[] array;
}

void Vector::changeComparator() { //0 names 1 dates
    if (this->comparator == 0) this->comparator = 1;
    else comparator = 0;
}

int Vector::compareNames(Person person1, Person person2) { //0 for person1 name being before in alphabet order person2 date, 2 for equal, else 1
    string name1 = person1.getName();
    string name2 = person2.getName();
    if (name1 == name2) return 2;
    int i = 0;
    while (name1[i] != '\0' || name2[i] != '\0') {
        if(int(name1[i] < int(name2[i]))) return 0;
        else if(int(name1[i] > int(name2[i]))) return 1;
        i++;
    }
    return 0;
}

int Vector::compareDates(Person person1, Person person2) { //0 for person1 date being before person2 date, 2 for equal, else 1
    if (person1.getDate() == person2.getDate()) return 2;
    else if (person1.getYear() < person2.getYear()) return 0;
    else if (person1.getYear() > person2.getYear()) return 1;
    else if (person1.getMonth() < person2.getMonth()) return 0;
    else if (person1.getMonth() > person2.getMonth()) return 1;
    else if (person1.getDay() < person2.getDay()) return 0;
    else if (person1.getDay() > person2.getDay()) return 1;
    else return 2;
}

void Vector::removeMin() {
    get(0).print();
    cout << endl;
    array[0] = array[size - 1];
    this->size--;
    heapify(0);
}

void Vector::buildHeap() {
    for (int i = Vector::parent(size - 1); i >= 0; i--) {
        heapify(i);
    }
}

void Vector::heapInsert(Person person) {
    if (size == maxSize) {
        maxSize = maxSize * 2;
        Person* tmp_array = array;
        array = new Person[maxSize];
        for (int i = 0; i < size; i++) array[i] = tmp_array[i];
        delete [] tmp_array;
    }
    size++;
    if (size == 1) array[0] = person;
    else {
        int i = size - 1;
        array[i] = person;
        if (comparator == 0) { //names
            while (i > 0 && compareNames(get(parent(i)), get(i)) == 1) {
                swap(i, parent(i));
                i = Vector::parent(i);
            }
        }
        else { //dates
            while (i > 0 && compareDates(get(parent(i)), get(i)) == 1) {
                swap(i, parent(i));
                i = Vector::parent(i);
            }
        }
    }
}

void Vector::heapify(int i) {
    int left = Vector::left(i);
    int right = Vector::right(i);
    int pos = i;
    if (this->comparator == 0) { //names
        if (left < this->size && compareNames(Vector::get(left), Vector::get(i)) == 0) {
            pos = left;
        }
        if (right < this->size && compareNames(Vector::get(right), Vector::get(pos)) == 0) {
            pos = right;
        }
        if (pos != i) {
            swap(i, pos);
            heapify(pos);
        }
    }
    else { //dates
        if (left < this->size && compareDates(Vector::get(left), Vector::get(i)) == 0) {
            pos = left;
        }
        if (right < this->size && compareDates(Vector::get(right), Vector::get(pos)) == 0) {
            pos = right;
        }
        if (pos != i) {
            swap(i, pos);
            heapify(pos);
        }
    }
}

int Vector::right(int i) {
    return ((2 * i) + 2);
}

int Vector::left(int i) {
    return ((2 * i) + 1);
}

int Vector::parent(int i) {
    if (i > 0) return ((i - 1) / 2);
    else return i;
}

int main() {
    string command, date, name;
    Vector people;
    int n;
    while (cin >> command) {
        if (command == "q") break;
        else if (command == "+") {
            cin >> n;
            for (int i = 0; i < n; i++) {
                cin >> date >> name;
                people.heapInsert(Person(name, date));
            }
        }
        else if (command == "p") {
            people.print();
            cout << endl;
        }
        else if (command == "-") {
            cin >> n;
            for (int i = 0; i < n; i++) {
                people.removeMin();
            }
            cout << endl;
        }
        else if (command == "r") {
            people.changeComparator();
            people.buildHeap();
        }
        else continue;
    }
    return 0;
}