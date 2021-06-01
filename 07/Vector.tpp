template <typename T>
T* Allocator<T>::allocate(size_t cnt){
    T* ans = new T[cnt];
    return ans;
};

template <typename T>
void Allocator<T>::deallocate(T* ptr){
    if (ptr != nullptr)
        delete[] ptr;
};



template <typename T>
T VectorIterator<T>::operator*() const{
    return *current_;
}

template <typename T>
void VectorIterator<T>::operator++(){
    if (isReserved){
        current_--;
    }
    else{
        current_++;
    }
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator+(const size_t cnt){
    VectorIterator<T> cur = current_;
    for (size_t i(0); i<cnt; i++)
    if (isReserved){
        cur--;
    }
    else{
        cur++;
    }
    return cur;
};

template <typename T>
bool VectorIterator<T>::operator==(const VectorIterator& other) const{
    return (*current_ == *(other.current_));
}

template <typename T>
bool VectorIterator<T>::operator!=(const VectorIterator& other) const{
    return !(*this == other);
}



template<typename T, typename Alloc>
void Vector<T, Alloc>::transportdata(){
    T* newdata = alc.allocate(Capacity);
    for (size_t i(0); i<Size; i++)
        newdata[i] = data[i];
    if (data != nullptr)
        alc.deallocate(data);
    data = newdata;
}

template<typename T, typename Alloc>
T& Vector<T, Alloc>::operator[](const size_t i){
    if ((i >= Capacity) || (i < 0))
        throw std::out_of_range("");
    return data[i];
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::push_back(const T& x){
    if (Size == Capacity){
        Capacity = (Size + 1)*2;
        transportdata();
    }
    data[Size] = x;
    Size += 1;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::push_back(T&& x){
    if (Size == Capacity){
        Capacity = (Size + 1)*2;
        transportdata();
    }
    data[Size] = std::move(x);
    Size += 1;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::pop_back(){
    if (Size == 0)
        throw std::out_of_range("");
    Size -= 1;
    if (Size <= Capacity / 4){
        Capacity /= 2;
        transportdata();
    }
}

template<typename T, typename Alloc>
template<typename... ArgsT>
void Vector<T, Alloc>::emplace_back(ArgsT&&... args){
    if (Size == Capacity){
        Capacity *= 2;
        transportdata();
    }
    data[Size] = T(args...);
    Size += 1;
}

template<typename T, typename Alloc>
bool Vector<T, Alloc>::empty(){
    return (Size == 0);
}

template<typename T, typename Alloc>
size_t Vector<T, Alloc>::size(){
    return Size;
}

template<typename T, typename Alloc>
size_t Vector<T, Alloc>::capacity(){
    return Capacity;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::clear(){
    Size = 0;
    Capacity = 0;
    alc.deallocate(data);
    data = nullptr;
}

template<typename T, typename Alloc>
VectorIterator<T> Vector<T, Alloc>::begin() noexcept{
    return VectorIterator<T>(data, Size, false, true);
}

template<typename T, typename Alloc>
VectorIterator<T> Vector<T, Alloc>::rbegin() noexcept{
    return VectorIterator<T>(data, Size, true, true);
}

template<typename T, typename Alloc>
VectorIterator<T> Vector<T, Alloc>::end() noexcept{
    return VectorIterator<T>(data, Size, false, false);
}

template<typename T, typename Alloc>
VectorIterator<T> Vector<T, Alloc>::rend() noexcept{
    return VectorIterator<T>(data, Size, true, false);
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::resize(const size_t cnt){
    if ((cnt >= Capacity) || (cnt <= Capacity / 4)){
        Capacity = 2 * cnt;
        if (cnt < Size)
            Size = cnt;
        transportdata();
        }
    Size = cnt;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::reserve(const size_t cnt){
    Capacity = cnt;
    if (Size > Capacity)
        Size = Capacity;
    transportdata();
}
