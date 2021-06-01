#pragma once
#include <iostream>

template <typename T>
class Allocator{

public:
    T* allocate(size_t cnt);

    void deallocate(T* ptr);
};



template <typename T>
class VectorIterator{

    T* current_;
    bool isReserved;

public:

    VectorIterator(T*& begin, const size_t Size, const bool isreservedIter, const bool isbeginiter)
        : isReserved(isreservedIter){
            T* begin_ = begin;
            T* end_ = begin_;
            end_ = end_ + Size;
            if (isreservedIter){
                std::swap(begin_, end_);
                begin_--;
                end_--;
            }
            if (isbeginiter)
                current_ = begin_;
            else
                current_ = end_;
        };

    ~VectorIterator(){
        current_ = nullptr;
    };

    VectorIterator(const VectorIterator& other ){
        current_ = other.current_;
        isReserved = other.isReserved;
    };

    VectorIterator(VectorIterator&& other ){
        current_ = other.current_;
        isReserved = other.isReserved;
        other.current_ = nullptr;
    };

    VectorIterator& operator=(const VectorIterator& other ){
        current_ = other.current_;
        isReserved = other.isReserved;
        return *this;
    };

    VectorIterator& operator=(VectorIterator&& other ){
        if (*this == other)
            return *this;
        current_ = other.current_;
        isReserved = other.isReserved;
        other.current_ = nullptr;
        return *this;
    };

    T operator*() const;

    void operator++();

    VectorIterator&  operator+(const size_t cnt);

    bool operator==(const VectorIterator& other) const;

    bool operator!=(const VectorIterator& other) const;
};



template<typename T, typename Alloc = Allocator<T>>
class Vector{

    T* data;
    size_t Size;
    size_t Capacity;
    Alloc alc;

    void transportdata();

public:

    Vector(const size_t cnt = 0){
        Size = cnt;
        Capacity = cnt;
        data = alc.allocate(cnt);
    };

    ~Vector(){
        alc.deallocate(data);
    };

    Vector(const Vector& other ){
        data = std::copy(other.data);
        Size = other.Size;
        Capacity = other.Capacity;
    };

    Vector(Vector&& other ){
        data = other.data;
        other.data = nullptr;
        Size = other.Size;
        Capacity = other.Capacity;
    };

    Vector& operator=(const Vector& other ){
        data = std::copy(other.data);
        Size = other.Size;
        Capacity = other.Capacity;
        return *this;
    };

    Vector& operator=(Vector&& other ){
        if (*this == other)
            return *this;
        data = std::copy(other.data);
        Size = other.Size;
        Capacity = other.Capacity;
        alc = other.alc;
        other.data = nullptr;
        return *this;
    };

    T& operator[](const size_t i);

    void push_back(const T& x);

    void push_back(T&& x);

    void pop_back();

    template<typename... ArgsT>
    void emplace_back(ArgsT&&... args);

    bool empty();

    size_t size();

    size_t capacity();

    void clear();

    VectorIterator<T> begin() noexcept;

    VectorIterator<T> rbegin() noexcept;

    VectorIterator<T> end() noexcept;

    VectorIterator<T> rend() noexcept;

    void resize(const size_t cnt);

    void reserve(const size_t cnt);
};

#include "Vector.tpp"
