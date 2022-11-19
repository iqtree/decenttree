#include <stdint.h>

template<class T, int n> class FakeVector {
public:
    T data[n]; //so that operator < can see it
    FakeVector() {
        for (int i=0; i<n; ++i) {
            data[i]=0;
        }
    }
    FakeVector(const FakeVector& r) = default;
    explicit FakeVector(T v) {
        for (int i=0; i<n; ++i) {
            data[i]=v;
        }
    }
    FakeVector& operator= (const FakeVector& rhs) = default;

    int size() { return n; }
    FakeVector& load(const T* p) {
        for (int i=0; i<n; ++i) {
            data[i]=p[i];
        }
        return *this;
    }
    FakeVector& store(T* p) {
        for (int i=0; i<n; ++i) {
            p[i]=data[i];
        }
        return *this;
    }

    FakeVector operator-(const FakeVector& rhs) {
        FakeVector result;
        for (int i=0; i<n; ++i) {
            result.data[i] = data[i] - rhs.data[i];
        }
        return result;
    }
};

typedef FakeVector<double,  4> MyFloatVector;
typedef FakeVector<uint64_t, 4> MyBoolVector;

template <class T, int s> 
    FakeVector<uint64_t,s> operator< 
    ( const FakeVector<T,s>& left, const FakeVector<T,s>& right ) {
    FakeVector<uint64_t,s> result;
    for (int i=0; i<s; ++i) {
        result.data[i] = ( left.data[i] < right.data[i] ) ? -1 : 0;
    }
    return result;
}

template <class T, int s, class B> 
    FakeVector<T,s> select ( const FakeVector<B,s>& isLeft,
                             const FakeVector<T,s>& left,
                             const FakeVector<T,s>& right ) {
    FakeVector<T,s> result;
    for (int i=0; i<s; ++i) {
        result.data[i] = (isLeft.data[i]!=0) 
                       ? left.data[i] : right.data[i];
    }
    return result;
}
