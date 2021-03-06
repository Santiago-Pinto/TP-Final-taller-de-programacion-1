// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONHEAP_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONHEAP_H_
//------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*******************************************************************************
// TEMPLATE GENERICO
*******************************************************************************/
template <class T>
class commonHeap {
 protected :
    std::vector<T> heapVector;
    bool (*compareFunction)(T a, T b);
 public :
    //--------------------------------------------------------------------------
    explicit commonHeap(bool (*cmp)(T a, T b)): compareFunction(cmp) {}
    //--------------------------------------------------------------------------
    virtual ~commonHeap() {}
    //--------------------------------------------------------------------------
    void add(T data) {
        heapVector.push_back(data);
        std::push_heap(heapVector.begin(), heapVector.end(), compareFunction);
    }
    //--------------------------------------------------------------------------
    void pop() {
        std::pop_heap(heapVector.begin(), heapVector.end(), compareFunction);
        heapVector.pop_back();
    }
    //--------------------------------------------------------------------------
    T top() {
        std::make_heap(heapVector.begin(), heapVector.end(), compareFunction);
        return heapVector.front();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return heapVector.empty();
    }
    //--------------------------------------------------------------------------
    size_t size() {
        return heapVector.size();
    }
    //--------------------------------------------------------------------------
    void clear() {
        heapVector.clear();
    }
    //--------------------------------------------------------------------------
    std::vector<T> getQueue() {
        return heapVector;
    }
    //--------------------------------------------------------------------------
};
/*******************************************************************************
// COMPLETE SPECIALIZATION OF T*
*******************************************************************************/
template <class T>
class commonHeap<T*> {
 private :
    std::vector<T*> heapVector;
    bool (*compareFunction)(T* a, T* b);
 public :
    //--------------------------------------------------------------------------
    explicit commonHeap(bool (*cmp)(T* a, T* b)):compareFunction(cmp) {}
    //--------------------------------------------------------------------------
    ~commonHeap() {}
    //--------------------------------------------------------------------------
    void add(T* data) {
        heapVector.push_back(data);
        std::push_heap(heapVector.begin(), heapVector.end(), compareFunction);
    }
    //--------------------------------------------------------------------------
    void pop() {
        std::pop_heap(heapVector.begin(), heapVector.end(), compareFunction);
        heapVector.pop_back();
    }
    //--------------------------------------------------------------------------
    T* top() {
        std::make_heap(heapVector.begin(), heapVector.end(), compareFunction);
        return heapVector.front();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return heapVector.empty();
    }
    //--------------------------------------------------------------------------
    size_t size() {
        return heapVector.size();
    }
    //--------------------------------------------------------------------------
    void clear() {
        heapVector.clear();
    }
    //--------------------------------------------------------------------------
    std::vector<T*> getQueue() {
        return heapVector;
    }
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONHEAP_H_
