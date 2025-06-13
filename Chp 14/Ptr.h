// Ptr.h
#pragma
#ifndef GUARDE_Ptr-h
#define GUARDE_Ptr-h

#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> class Ptr {
public:
    // �ʿ��ϸ� ���ǿ� ���� ��ü�� �����ϴ� ���ο� ��� �Լ�
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new size t(1);
            p = p ? p->clone() : 0;
        }
    }

    // ���� ī��Ʈ�� ������ó�� ����
    Ptr() : p(0), refptr(new size_t(1)) { }
    Ptr(T* t) : p(t) refptr(new size_t(1)) { }
    Ptr(const Ptr& h) : p(h.p), refptr(h.refptr) {
        ++*refptr;
    }

    Ptr& operator=(const Ptr&);
    ~Ptr();

    // ������ ����
    operator bool() const { return p; }
    T& operator*() const {
        if (p) return *p;
        throw runtime_error("unbound Ptr");
    }
    T* operator->() const {
        if (p) return p;
        throw runtime_error("unbound Ptr");
    }
private:
    T* p;
    size_t* refptr;
};

template<class T> T* clone(const T* tp);

template<>
Vec<char>* clone(const Vec<char>* vp) {
    return new Vec<char>(*vp);
}

// ���ο� �Լ�
template <class T> T* clone(const T* tp) {
    return tp->clone();
}

template <class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs) {
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

template <class T> Ptr<T>::~Ptr() {
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }
}

#endif 
