#ifndef RS_STRONG_POINTER_H
#define RS_STRONG_POINTER_H
#include "logger.h"
template<typename T> class wp;

// ---------------------------------------------------------------------------

#define COMPARE(_op_)                                           \
inline bool operator _op_ (const sp<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
inline bool operator _op_ (const T* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const sp<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const U* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
inline bool operator _op_ (const wp<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const wp<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}

// ---------------------------------------------------------------------------

template <typename T>
class sp
{
public:
    inline sp() : m_ptr(0) { }

    sp(T* other): m_ptr(other)
    {
        Logging("sp::sp(T*)");
        if (other) other->incStrong(this);
    }

    sp(const sp<T>& other): m_ptr(other.m_ptr)
    {
        Logging("sp::sp(const sp<T>&)");
        if (m_ptr) m_ptr->incStrong(this);
    }

    ~sp()
    {
        Logging("sp::~sp()");
        if (m_ptr) m_ptr->decStrong(this);
    }

    // Assignment

    sp& operator = (T* other);
    sp& operator = (const sp<T>& other);

    void clear();

    // Accessors

    inline  T&      operator* () const  
    { 
        Logging("sp::operator*()");
        return *m_ptr; 
    }
    inline  T*      operator-> () const 
    {
        Logging("sp::operator->()"); 
        return m_ptr;  
    }
    inline  T*      get() const         
    { 
        Logging("sp::get()");
        return m_ptr; 
    }

    // Operators

    COMPARE(==)
    COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)

private:
    template<typename Y> friend class sp;
    template<typename Y> friend class wp;
    void set_pointer(T* ptr);
    T* m_ptr;
};

#undef COMPARE

// ---------------------------------------------------------------------------
// No user serviceable parts below here.
template<typename T> sp<T>& sp<T>::operator = (const sp<T>& other) 
{
    Logging("sp::operator = (const sp<T>& other)");
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    if (m_ptr) m_ptr->decStrong(this);
    m_ptr = otherPtr;
    return *this;
}

template<typename T> sp<T>& sp<T>::operator = (T* other)
{
    Logging("sp::operator = (T* other)");
    if (other) other->incStrong(this);
    if (m_ptr) m_ptr->decStrong(this);
    m_ptr = other;
    return *this;
}

template<typename T> void sp<T>::clear()
{
    Logging("sp::clear()");
    if (m_ptr) {
        m_ptr->decStrong(this);
        m_ptr = 0;
    }
}

template<typename T> void sp<T>::set_pointer(T* ptr) 
{
    Logging("sp::set_pointer(T* ptr)");
    m_ptr = ptr;
}


#endif