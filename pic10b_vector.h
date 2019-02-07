/*
 UID 704447499
 Name: Byung Jun Cho
 Pic 10C
 Professor Salazar
 */


#include <iostream>   // std::ostream, std::cout
#include <assert.h>
#include <cmath>
#include <typeinfo>

namespace Pic10b {
    template<typename T>
    class vector {
    private:
        T* the_data;
        size_t the_size;
        size_t the_capacity;
        
        static const int INIT_CAP = 10;
        
        
    public:
        // The big 4
        vector();
        vector(const vector&);
        vector& operator=(const vector& vec);
        ~vector();
        
        // Overloaded Operators
      
        // Other members [public]
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        T front() const;
        T back() const;
        T at(size_t index) const;
        T& operator[](size_t index);
        T operator[](size_t index) const;
        void dump_data_to(std::ostream& out) const;
        void dump_data() const;
        void push_back(T new_value);
        void pop_back();
        
        // local definition
        vector<T> operator+=(const Pic10b::vector<T>& v1) {
            for(int i = 0; i < the_size; i++){
                the_data[i] += v1[i];
            }
            return *this;
        }
        
    private:
        void reserve(size_t new_capacity);
        
    };
    
    
    /** *********************** THE BIG 4 *********************** **/
    template<typename T>
    vector<T>::vector()
    : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {
        
        the_data = new T[the_capacity];
        std::cout << "xxxxx: This is the default constructor :xxxxx\n";
    }
    template<typename T>
    vector<T>::vector(const vector<T>& source)
    : the_data(nullptr), the_size(source.the_size),
    the_capacity(source.the_capacity) {
        
        the_data = new T[the_capacity];
        
        for (int i = 0; i < the_size; ++i) {
            the_data[i] = source.the_data[i];
        }
        std::cout << "xxxxx: This is the regular constructor :xxxxx\n";
    }
    template<typename T>
    vector<T>& vector<T>::operator=(const vector<T>& rhs) {
        if (this != &rhs) {
            delete[] the_data;
            the_data = new T[rhs.the_capacity];
            
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;
            
            for (int i = 0; i < the_size; ++i)
                the_data[i] = rhs.the_data[i];
        }
        return *this;
        std::cout << "xxxxx: This is the copy constructor : xxxxx\n";
    }
    template<typename T>
    vector<T>::~vector() {
        delete[] the_data;
        std::cout << "xxxxx: This is the destructor :xxxxx\n";
    }
    /** ********************* Overloaded Operators ********************* **/
    template<typename T>
    Pic10b::vector<T>  operator*(const T& c, const Pic10b::vector<T>& v) {
        Pic10b::vector<T> v1;
        for (size_t i = 0; i < v.size(); ++i)
            v1.push_back(c * v[i]);
        return v1;
    }
    template <>
    Pic10b::vector<std::string> operator*<std::string>(const std::string& c, const Pic10b::vector<std::string>& v) {
        Pic10b::vector<std::string> v1;
        for (size_t i = 0; i < v.size(); ++i)
            v1.push_back(c + " " + v[i]);
        return v1;
    }
    template<typename T>
    Pic10b::vector<T> operator*(const Pic10b::vector<T>& v, const T& c) {
        Pic10b::vector<T> v1;
        for (size_t i = 0; i < v.size(); ++i)
            v1.push_back(v[i] * c);
        return v1;
    }
    template <>
    Pic10b::vector<std::string> operator*<std::string>(const Pic10b::vector<std::string>& v,
                                               const std::string& c) {
        Pic10b::vector<std::string> v1;
        for (size_t i = 0; i < v.size(); ++i)
            v1.push_back(v[i] +" " + c);
        return v1;
    }
    template<typename T>
        T operator*(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        T norm1 = 0;
        for( int i = 0 ; i < vec1.size();i++){
            norm1 += vec1[i]*vec1[i];
        }
        norm1 = sqrt(norm1);
        
        T norm2 = 0;
        for(int i = 0; i < vec2.size(); i++){
            norm2 += vec2[i]*vec2[i];
        }
        norm2 = sqrt(norm2);
        
        return norm1*norm2;
    }

    template<typename T>
    Pic10b::vector<T> operator+(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        Pic10b::vector<T> v;
        size_t v_size;
        const Pic10b::vector<T> *big_vec;
        
        if (vec1.size() < vec2.size()) {
            v_size = vec1.size();
            big_vec = &vec2;
        }
        else {
            v_size = vec2.size();
            big_vec = &vec1;
        }
        size_t i = 0;
        for (;i < v_size; ++i)
            v.push_back(vec1[i] + vec2[i]);
        for (;i < big_vec->size(); ++i)
            v.push_back((*(big_vec))[i]);
        
        return v;
    }
    template<typename T>
    Pic10b::vector<T> operator+(const Pic10b::vector<T>& v, const T& c) {
        Pic10b::vector<T> v1;
        for (size_t i = 0; i < v.size(); ++i)
            v1.push_back(v[i] + c);
        return v1;
    }
    template<typename T>
    T sqrt(const Pic10b::vector<T>& vec) {
        T norm = 0;
        for (size_t i = 0; i < vec.size(); ++i)
            norm+=abs(vec[i]*vec[i]);
        return norm;
    }
    template<typename T>
    bool operator==(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) return false;
        for (size_t i = 0; i < vec1.size(); ++i)
            if (vec1[i] != vec2[i]) return false;
        return true;
    }
    template<typename T>
    bool operator!=(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        return !(vec1 == vec2);
    }
    template<typename T>
    bool operator<(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) return false;
        if (sqrt(vec1)>sqrt(vec2)) return false;
        return true;
    }
    template<typename T>
    bool operator<=(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) return false;
        if (sqrt(vec1) > sqrt(vec2)) return false;
        return true;
    }
    template<typename T>
    bool operator>(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) return false;
            if (sqrt(vec1) <= sqrt(vec2)) return false;
        return true;
    }
    template<typename T>
    bool operator>=(const Pic10b::vector<T>& vec1, const Pic10b::vector<T>& vec2) {
        if (vec1.size() != vec2.size()) return false;
            if (sqrt(vec1) < sqrt(vec2)) return false;
        return true;
    }
    
    /** ********************* OTHER MEMBERS ********************* **/
    template<typename T>
    bool vector<T>::empty() const {
        return the_size == 0;
    }
    template<typename T>
    size_t vector<T>::size() const {
        return the_size;
    }
    template<typename T>
    size_t vector<T>::capacity() const {
        return the_capacity;
    }
    template<typename T>
    T vector<T>::front() const {
        return *the_data;
    }
    template<typename T>
    T vector<T>::back() const {
        return *(the_data + the_size - 1);
    }
    template<typename T>
    T vector<T>::at(size_t index) const {
        if (index < the_size)
            return the_data[index];
        return the_data[0];
    }
    template<typename T>
    T& vector<T>::operator[](size_t index) {
        return the_data[index];
    }
    template<typename T>
    T vector<T>::operator[](size_t index) const {
        return the_data[index];
    }
    template<typename T>
    void vector<T>::dump_data_to(std::ostream& out) const {
        out << "Vector (dump): ";
        for (size_t i = 0; i < the_capacity; ++i)
            out << the_data[i] << ' ';
        out << '\n';
    }
    template<typename T>
    void vector<T>::dump_data() const {
        dump_data_to(std::cout);
    }
    
    template<typename T>
    void vector<T>::push_back(T new_value) {
        if (the_size == the_capacity)
            reserve(the_capacity + 1);
        
        the_data[the_size++] = new_value;
    }
    
    template<typename T>
    void vector<T>::pop_back() {
        if (the_size > 0)
            --the_size;
    }
    
    template<typename T>
    void vector<T>::reserve(size_t new_capacity) {
        if (new_capacity > the_capacity) {
            if (new_capacity <= 2 * the_capacity)
                new_capacity = 2 * the_capacity;
            
            T* old_location = the_data;
            
            the_data = new T[new_capacity];
            the_capacity = new_capacity;
            
            for (size_t i = 0; i < the_size; ++i)
                the_data[i] = old_location[i];
            
            delete old_location;
        }
    }
    
}

/** ********************** OTHER FUNCTIONS ********************** **/
template<typename T>
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<T>& v) {
    //if the datatype is string, the << operator will use [] and {} if the data type is a number.
    std::string s;
    if(typeid(v[1]) == typeid(s)){
        out << "[ ";
        for (size_t i = 0; i < v.size(); ++i){
            if(i!=v.size()-1)
                out << v[i] << ", ";
            else
                out << v[i] << " ";
        }
        out << "]";
    }
    else{
    out << "{ ";
    for (size_t i = 0; i < v.size(); ++i){
        if(i != v.size()-1)
            out << v[i] << ", ";
        else
            out << v[i] << " ";
    }
    out << "}";
        }
    return out;
}

template<typename T>
void print_vector(const Pic10b::vector<T>& v) {
    if (v.empty())
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n';
}
