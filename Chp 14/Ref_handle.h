#pragma
#ifndef GUARDE_Ref_handle_h
#define GUARDE_Ref_handle_h

#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> class Ref_handle {
public:
    // ���� ī��Ʈ�� ������ó�� ����
    Ref_handle() : p(0), refptr(new size_t(1)) { }
    Ref_handle(T* t) : p(t) refptr(new size_t(1)) { }
    Ref_handle(const Ref_handle& h) : p(h.p), refptr(h.refptr) {
        ++*refptr;
    }

    Ref_handle& operator=(const Ref_handle&);
    ~Ref_handle();

    // ������ ����
    operator bool() const { return p; }
    T& operator*() const {
        if (p) return *p;
        throw runtime_error("unbound Ref_handle");
    }
    T* operator->() const {
        if (p) return p;
        throw runtime_error("unbound Ref_handle");
    }
private:
    T* p;
    size_t* refptr;
};

template <class T>
Ref_handle<T>& Ref_handle<T>::operator=(const Ref_handle& rhs) {
    ++*rhs.refptr;

    // ��Ȳ�� ���� �º��� �Ҵ� �����ϰ� ������ �Ҹ�
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }

    // �캯 ������ ����
    refptr = rhs.refptr;
    p = rhs.p;

    return *this;
}

template <class T> Ref_handle<T>::~Ref_handle() {
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }
}

#endif 
