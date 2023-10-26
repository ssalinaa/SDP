#include <iostream>
#include <vector>
#include <string>
#include <cassert>

template <class T>
class DynamicArray {
private:
    static const std::size_t INCREASE_STEP = 2;
    static const std::size_t INITIAL_CAPACITY = 2;

    T* arr;
    std::size_t size;
    std::size_t capacity;

    void copy(const DynamicArray& other) {
        this->arr = new T[other.capacity];
        for (std::size_t i = 0; i < other.size; i++) {
            this->arr[i] = other.arr[i];
        }
        this->size = other.size;
        this->capacity = other.capacity;
    }

    void destroy() {
        delete[] this->arr;
    }

    void resize() {
        T* newArr = new T[capacity * INCREASE_STEP];
        for (std::size_t i = 0; i < this->size; i++) {
            newArr[i] = arr[i];
        }
        delete[] this->arr;
        this->arr = newArr;
        this->capacity *= INCREASE_STEP;
    }

public:
    DynamicArray() : arr(new T[INITIAL_CAPACITY]), size(0), capacity(INITIAL_CAPACITY) {}

    DynamicArray(const DynamicArray& other) {
        this->copy(other);
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            this->copy(other);
            this->destroy();
        }
        return *this;
    }

    ~DynamicArray() {
        this->destroy();
    }

    T& front() {
        assert(this->size > 0);
        return this->arr[0];
    }

    const T& front() const {
        assert(this->size > 0);
        return this->arr[0];
    }

    T& back() {
        assert(this->size > 0);
        return this->arr[this->size - 1];
    }

    const T& back() const {
        assert(this->size > 0);
        return this->arr[this->size - 1];
    }

    T& operator[](std::size_t index) {
        assert(index >= 0 && index < this->size);
        return this->arr[index];
    }

    const T& operator[](std::size_t index) const {
        assert(index >= 0 && index < this->size);
        return this->arr[index];
    }

    std::size_t getSize() const {
        return this->size;
    }

    std::size_t getCapacity() const {
        return this->capacity;
    }

    bool empty() const {
        return this->size == 0;
    }

    void clear() {
        this->size = 0;
    }

    void push_back(const T& element) {
        if (this->size == this->capacity) {
            this->resize();
        }
        this->arr[this->size++] = element;
    }

    void pop_back() {
        assert(this->size > 0);
        --this->size;
    }

    class DynamicArrayIterator {
    private:
        friend class DynamicArray;
        T* pointer;

        DynamicArrayIterator(T* pointer) : pointer(pointer) {}

    public:
        T& operator*() {
            return *pointer;
        }

        const T& operator*() const {
            return *pointer;
        }

        T* operator->() {
            return pointer;
        }

        const T* operator->() const {
            return pointer;
        }

        DynamicArrayIterator& operator++() { //++it
            ++pointer;
            return *this;
        }

        DynamicArrayIterator operator++(int) { // it++
            DynamicArrayIterator old = *this;
            ++(*this);
            return old;
        }

        DynamicArrayIterator& operator--() {
            --pointer;
            return *this;
        }

        DynamicArrayIterator operator--(int) {
            DynamicArrayIterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const DynamicArrayIterator& other) const {
            return pointer == other.pointer;
        }

        bool operator!=(const DynamicArrayIterator& other) const {
            return pointer != other.pointer;
        }

        bool operator<(const DynamicArrayIterator& other) const {
            return pointer < other.pointer;
        }

        bool operator>(const DynamicArrayIterator& other) const {
            return pointer > other.pointer;
        }

        bool operator<=(const DynamicArrayIterator& other) const {
            return pointer <= other.pointer;
        }

        bool operator>=(const DynamicArrayIterator& other) const {
            return pointer >= other.pointer;
        }

        DynamicArrayIterator& operator+=(int offset) {
            pointer += offset;
            return *this;
        }

        DynamicArrayIterator& operator-=(int offset) {
            pointer -= offset;
            return *this;
        }

        DynamicArrayIterator operator+(int offset) const {
            DynamicArrayIterator copy = *this;
            copy += offset;
            return copy;
        }

        DynamicArrayIterator operator-(int offset) const {
            DynamicArrayIterator copy = *this;
            copy -= offset;
            return copy;
        }

        T& operator[](int offset) {
            return *(pointer + offset);
        }

        const T& operator[](int offset) const {
            return *(pointer + offset);
        }
    };

    DynamicArrayIterator begin() {
        return DynamicArrayIterator(this->arr);
    }

    DynamicArrayIterator end() {
        return DynamicArrayIterator(this->arr + this->size);
    }

    void insert(DynamicArrayIterator pos, const T& value) {
        if (pos == this->end() && this->size == this->capacity) {
            resize();
        }
        for (DynamicArrayIterator it = this->end(); it != pos; --it) {
            *it = *(it - 1);
        }
        *pos = value;
        ++this->size;
    }

    void erase(DynamicArrayIterator first, DynamicArrayIterator last) // [first, last)
    {
        std::size_t difference = last.pointer - first.pointer;
        assert(difference <= this->size);
        this->size -= difference;
        for (DynamicArrayIterator it = first; it != this->end(); ++it) {
            *it = *(it + difference);
        }
    }

    void erase(DynamicArrayIterator pos) {
        this->erase(pos, pos + 1);
    }
};

class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& name = "", int age = 0) : name(name), age(age) {}

    void print() const {
        std::cout << "My name is " << this->name << " and I am " << this->age << " years old." << std::endl;
    }
};

int main()
{
    DynamicArray<int> v;

    v.push_back(1);
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    v.push_back(9);
    v.push_back(11);

    for (std::size_t i = 0; i < v.getSize(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    for (DynamicArray<int>::DynamicArrayIterator it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (int currentElement : v)
    {
        std::cout << currentElement << " ";
    }
    std::cout << std::endl;

    DynamicArray<Person> people;

    people.push_back(Person("Pesho", 22));
    people.push_back(Person("Vasko", 21));
    people.push_back(Person("Gosho", 23));

    for (std::size_t i = 0; i < people.getSize(); ++i)
    {
        people[i].print();
    }

    for (DynamicArray<Person>::DynamicArrayIterator it = people.begin(); it != people.end(); ++it)
    {
        it->print();
    }

    for (const Person& currentPerson : people)
    {
        currentPerson.print();
    }

    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.insert(arr.begin() + 1, 12);
    arr[1] = 12;

    for (int el : arr)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    return 0;
}
