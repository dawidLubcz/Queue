#ifndef CMYQUEUE
#define CMYQUEUE

#define MIN_SIZE 4

typedef long unsigned int uint64_t;
typedef bool bool_t;

class CQueueInfo;

template<class T>
class CMyQueue
{
private:
    T* m_paItems;
    uint64_t m_uiArraySize;
    static uint64_t m_uiSize;
    uint64_t m_uiHead;
    uint64_t m_uiTail;

    bool_t copyArray(T *a_paSource, T *a_paDest, uint64_t a_startIndex, uint64_t a_uiSize);
    void tryReleaseMem();

public:
    CMyQueue();
    ~CMyQueue();

    bool_t push(T a_oItem);
    bool_t pop(T &a_oItem);
    bool_t peek(T &a_oItem);
    uint64_t size();
    void getQueueInfo(CQueueInfo &a_oInfo);
    bool_t getItems(T *a_atItemsArray, uint64_t a_uiSize = m_uiSize);
    bool_t clear();
};

class CQueueInfo
{
public:
    uint64_t m_uiSize;
    uint64_t m_uiArraySize;
    uint64_t m_uiHead;
    uint64_t m_uiTail;
    uint64_t m_uiMemSize;

    // TO DO: Add typename
};

#include "CMyQueue.cpp"

#endif // CMYQUEUE

