// Str_Vec.h
#pragma once
#ifndef GUARD_Str
#define GUARD_Str

#include <algorithm>
#include <iterator>
#include <cstring>

#include "Vec.h"
#include "Ptr.h"

class Str {
    // �Է� ������
    friend std::istream& operator>>(std::istream&, Str&);
    friend std::istream& getline(std::istream&, Str&);

private:
    Ptr< Vec<char> > data;

public:
    typedef Vec<char>::size_type size_type;
    typedef char* iterator; // Q12
    typedef const char* const_iterator; // Q12

    // ��� �ִ� Str ��ü�� ����� �⺻ ������
    Str() : data(new Vec<char>){ } //�ʱⰪ �߰�
 
    // c�� ���纻 n���� �ִ� Str ��ü�� ����
    Str(size_type n, char c) : data(new Vec<char>(n, c)) { }

    // null�� ������ char Ÿ���� �迭���� Str ��ü�� ����
    Str(const char* cp) : data(new Vec<char>) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(*data));
    }

    // �ݺ��� b�� e�� ����Ű�� �������� Str ��ü�� ����
    template<class In> Str(In b, In e) : data(new Vec<char>) {
        std::copy(b, e, std::back_inserter(*data));
    }

    // �ε��� ������
    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }
    const char& operator[](size_type i) const { return (*data)[i]; }

    // ����(ũ��) �Լ�
    size_type size() const { return data->size(); }

    // ���� ������
    Str& operator+=(const Str& s) {
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(),
            std::back_inserter(*data));
        return *this;
    }

     // Q12 begin(), end(), insert()
    iterator begin() { return data->begin(); }
    iterator end() { return data->end(); }

    const_iterator begin() const { return data->begin(); }
    const_iterator end() const { return data->end(); }

    /*iterator insert(iterator d, iterator b, iterator e) {
        return data.insert(d, b, e);
    }*/
};

std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);

#endif 
