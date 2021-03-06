// "Copyright [2017] <Copyright SebastianBlanco>"
//------------------------------------------------------------------------------
#ifndef _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONDICC_H_
#define _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONDICC_H_
//------------------------------------------------------------------------------
#include <iostream>
#include <map>
#include <vector>
#include "commonException.h"
//------------------------------------------------------------------------------
/*******************************************************************************
// TEMPLATE GENERICO
*******************************************************************************/
template <class T, class V>
class commonDicc {
 protected :
    std::map<T, V> aMap1;
    std::vector<V> list1;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    V operator[](T key) {
        try {
            return aMap1.at(key);
        } catch (const std::out_of_range& oor) {
            std::cout << "The key: " << key << " was not found\n" << std::endl;
            throw Exception("The key was not found\n");
        }
    }
    //--------------------------------------------------------------------------
    void operator()(T key, V value) {
        try {
            aMap1.at(key) = value;
        } catch (const std::out_of_range& oor) {
            aMap1.emplace(key, value);
        }
        list1.push_back(value);
    }
    //--------------------------------------------------------------------------
    void erase(T key) {
        if (!keyExist(key)) return;
        V value = operator[](key);
        size_t position = 0;
        for (size_t i = 0; i < list1.size(); i++) {
            if (value == list1[i]) {
                position = i;
            }
        }
        list1.erase(list1.begin()+position);
        aMap1.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(T key) const {
        try {
            aMap1.at(key);
            return true;
        } catch (const std::out_of_range& oor) {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return aMap1.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return aMap1.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<V>& getList() {
        return list1;
    }
    //--------------------------------------------------------------------------
    void clear() {
        aMap1.clear();
        list1.clear();
    }
    //--------------------------------------------------------------------------
};
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
/*******************************************************************************
// TEMPLATE GENERICO - COMPLETE SPECIALIZATION OF K - VOID*
*******************************************************************************/
template <class K>
class commonDicc<K, void*> {
 protected :
    std::map<K, void*> aMap2;
    std::vector<void*> list2;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    void* operator[](K key) {
        try {
            return aMap2.at(key);
        } catch (const std::out_of_range& oor) {
            std::cout << "The key: " << key << " was not found\n" << std::endl;
            throw Exception("The key was not found\n");
        }
    }
    //--------------------------------------------------------------------------
    void operator()(K key, void* value) {
        try {
            aMap2.at(key) = value;
        } catch (const std::out_of_range& oor) {
            aMap2.emplace(key, value);
        }
        list2.push_back(value);
    }
    //--------------------------------------------------------------------------
    void erase(K key) {
        if (!keyExist(key)) return;
        void* value = operator[](key);
        size_t position = 0;
        for (size_t i = 0; i < list2.size(); i++) {
            if (value == list2[i]) {
                position = i;
            }
        }
        list2.erase(list2.begin()+position);
        aMap2.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(K key) const {
        try {
            aMap2.at(key);
            return true;
        } catch (const std::out_of_range& oor) {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return aMap2.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return aMap2.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<void*>& getList() {
        return list2;
    }
    //--------------------------------------------------------------------------
    void clear() {
        aMap2.clear();
        list2.clear();
    }
    //--------------------------------------------------------------------------
};
/*******************************************************************************
// PARTIAL SPECIALIZATION OF K - V*
*******************************************************************************/
template <class K, class V>
class commonDicc<K, V*> {
 private :
    commonDicc<K, void*> father2;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    V* operator[](K key) {
        return reinterpret_cast<V*>(father2.operator[](key));
    }
    //--------------------------------------------------------------------------
    void operator()(K key, V* value) {
        father2(key, value);
    }
    //--------------------------------------------------------------------------
    void erase(K key) {
        father2.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(K key) const {
        return father2.keyExist(key);
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return father2.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return father2.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<V*>& getList() {
        return (std::vector<V*>&)father2.getList();
    }
    //--------------------------------------------------------------------------
    void clear() {
        father2.clear();
    }
    //--------------------------------------------------------------------------
};
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
/*******************************************************************************
// COMPLETE SPECIALIZATION OF CONST VOID* - VOID*
*******************************************************************************/
template <>
class commonDicc<const void*, void*> {
 protected :
    std::map<const void*, void*> aMap3;
    std::vector<void*> list3;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    void* operator[](const void* key) {
        try {
            return aMap3.at(key);
        } catch (const std::out_of_range& oor) {
            std::cout << "The key: " << key << " was not found\n" << std::endl;
            throw Exception("The key was not found\n");
        }
    }
    //--------------------------------------------------------------------------
    void operator()(const void* key, void* value) {
        try {
            aMap3.at(key) = value;
        } catch (const std::out_of_range& oor) {
            aMap3.emplace(key, value);
        }
        list3.push_back(value);
    }
    //--------------------------------------------------------------------------
    void erase(const void* key) {
        if (!keyExist(key)) return;
        void* value = operator[](key);
        size_t position = 0;
        for (size_t i = 0; i < list3.size(); i++) {
            if (value == list3[i]) {
                position = i;
            }
        }
        list3.erase(list3.begin()+position);
        aMap3.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(const void* key) const {
        try {
            aMap3.at(key);
            return true;
        } catch (const std::out_of_range& oor) {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return aMap3.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return aMap3.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<void*>& getList() {
        return list3;
    }
    //--------------------------------------------------------------------------
    void clear() {
        aMap3.clear();
        list3.clear();
    }
    //--------------------------------------------------------------------------
};
/*******************************************************************************
// PARTIAL SPECIALIZATION OF CONST K* - V*
*******************************************************************************/
template <class K, class V>
class commonDicc<const K*, V*> {
 private :
    commonDicc<const void*, void*> father3;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    V* operator[](const K* key) {
        return reinterpret_cast<V*>(father3[key]);
    }
    //--------------------------------------------------------------------------
    void operator()(const K* key, V* value) {
        father3(key, value);
    }
    //--------------------------------------------------------------------------
    void erase(const K* key) {
        father3.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(const K* key) const {
        return father3.keyExist(key);
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return father3.empty();
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return father3.size();
    }
    //--------------------------------------------------------------------------
    std::vector<V*>& getList() {
        return (std::vector<V*>&)father3.getList();
    }
    //--------------------------------------------------------------------------
    void clear() {
        father3.clear();
    }
    //--------------------------------------------------------------------------
};
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
/*******************************************************************************
// COMPLETE SPECIALIZATION OF CONST VOID* - CONST VOID*
*******************************************************************************/
template <>
class commonDicc<const void*, const void*> {
 protected :
    std::map<const void*, const void*> aMap4;
    std::vector<const void*> list4;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    const void* operator[](const void* key) {
        try {
            return aMap4.at(key);
        } catch (const std::out_of_range& oor) {
            std::cout << "The key: " << key << " was not found\n" << std::endl;
            throw Exception("The key was not found\n");
        }
    }
    //--------------------------------------------------------------------------
    void operator()(const void* key, const void* value) {
        try {
            aMap4.at(key) = value;
        } catch (const std::out_of_range& oor) {
            aMap4.emplace(key, value);
        }
        list4.push_back(value);
    }
    //--------------------------------------------------------------------------
    void erase(const void* key) {
        if (!keyExist(key)) return;
        const void* value = operator[](key);
        size_t position = 0;
        for (size_t i = 0; i < list4.size(); i++) {
            if (value == list4[i]) {
                position = i;
            }
        }
        list4.erase(list4.begin()+position);
        aMap4.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(const void* key) const {
        try {
            aMap4.at(key);
            return true;
        } catch (const std::out_of_range& oor) {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return aMap4.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return aMap4.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<const void*>& getList() {
        return list4;
    }
    //--------------------------------------------------------------------------
    void clear() {
        aMap4.clear();
        list4.clear();
    }
    //--------------------------------------------------------------------------
};
/*******************************************************************************
// PARTIAL SPECIALIZATION OF CONST K* - CONST V*
*******************************************************************************/
template <class K, class V>
class commonDicc<const K*, const V*> {
 private :
    commonDicc<const void*, const void*> father4;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    const V* operator[](const K* key) {
        return reinterpret_cast<const V*>(father4[key]);
    }
    //--------------------------------------------------------------------------
    void operator()(const K* key, const V* value) {
        father4(key, value);
    }
    //--------------------------------------------------------------------------
    void erase(const K* key) {
        father4.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(const K* key) const {
        return father4.keyExist(key);
    }
    //--------------------------------------------------------------------------
    std::vector<const V*>& getList() {
        return (std::vector<const V*>&)father4.getList();
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return father4.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return father4.empty();
    }
    //--------------------------------------------------------------------------
    void clear() {
        father4.clear();
    }
    //--------------------------------------------------------------------------
};
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
/*******************************************************************************
// COMPLETE SPECIALIZATION OF VOID* - VOID*
*******************************************************************************/
template <>
class commonDicc<void*, void*> {
 protected :
    std::map<void*, void*> aMap5;
    std::vector<void*> list5;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    void* operator[](void* key) {
        try {
            return aMap5.at(key);
        } catch (const std::out_of_range& oor) {
            std::cout << "The key: " << key << " was not found\n" << std::endl;
            throw Exception("The key was not found\n");
        }
    }
    //--------------------------------------------------------------------------
    void operator()(void* key, void* value) {
        try {
            aMap5.at(key) = value;
        } catch (const std::out_of_range& oor) {
            aMap5.emplace(key, value);
        }
        list5.push_back(value);
    }
    //--------------------------------------------------------------------------
    void erase(void* key) {
        if (!keyExist(key)) return;
        void* value = operator[](key);
        size_t position = 0;
        for (size_t i = 0; i < list5.size(); i++) {
            if (value == list5[i]) {
                position = i;
            }
        }
        list5.erase(list5.begin()+position);
        aMap5.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(void* key) const {
        try {
            aMap5.at(key);
            return true;
        } catch (const std::out_of_range& oor) {
            return false;
        }
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return aMap5.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return aMap5.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<void*>& getList() {
        return list5;
    }
    //--------------------------------------------------------------------------
    void clear() {
        aMap5.clear();
        list5.clear();
    }
    //--------------------------------------------------------------------------
};
/*******************************************************************************
// PARTIAL SPECIALIZATION OF K* - V*
*******************************************************************************/
template <class K, class V>
class commonDicc<K*, V*> {
 private :
    commonDicc<void*, void*> father5;
 public :
    //--------------------------------------------------------------------------
    commonDicc() {}
    //--------------------------------------------------------------------------
    ~commonDicc() {}
    //--------------------------------------------------------------------------
    V* operator[](K* key) {
        return reinterpret_cast<V*>(father5[key]);
    }
    //--------------------------------------------------------------------------
    void operator()(K* key, V* value) {
        father5(key, value);
    }
    //--------------------------------------------------------------------------
    void erase(K* key) {
        father5.erase(key);
    }
    //--------------------------------------------------------------------------
    bool keyExist(K* key) const {
        return father5.keyExist(key);
    }
    //--------------------------------------------------------------------------
    size_t size() const {
        return father5.size();
    }
    //--------------------------------------------------------------------------
    bool empty() {
        return father5.empty();
    }
    //--------------------------------------------------------------------------
    std::vector<V*>& getList() {
        return (std::vector<V*>&)father5.getList();
    }
    //--------------------------------------------------------------------------
    void clear() {
        father5.clear();
    }
    //--------------------------------------------------------------------------
};
//------------------------------------------------------------------------------
#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TPGRUPAL_COMMONDICC_H_
