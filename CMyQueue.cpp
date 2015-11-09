#include "CMyQueue.h"

static const uint64_t g_uiInitalSize = 0;

template<typename T>
uint64_t CMyQueue<T>::m_uiSize = 0;

//-----------------------------------------------
// constructor
template<typename T>
CMyQueue<T>::CMyQueue():m_paItems(0), m_uiArraySize(g_uiInitalSize)
{

}

//-----------------------------------------------
// destructor
template<typename T>
CMyQueue<T>::~CMyQueue()
{

}

//-----------------------------------------------
// push
template<typename T>
bool_t CMyQueue<T>::push(T a_oItem)
{
    bool_t fResult = false;
    //array is need to grow
    if(m_uiSize == m_uiArraySize)
    {
        // new size
        int newLength = (m_uiArraySize == 0) ? MIN_SIZE : m_uiArraySize * 2;

        T* pNewArray = new T[newLength];

        if(m_uiSize > 0 && m_paItems != 0)
        {
            int targetIndex = 0;

            if(m_uiTail < m_uiHead)
            {
                for(uint64_t index = m_uiHead; index < m_uiArraySize; index++)
                {
                    pNewArray[targetIndex] = m_paItems[index];
                    targetIndex ++;
                }

                for(uint64_t index = 0; index <= m_uiTail; index++)
                {
                    pNewArray[targetIndex] = m_paItems[index];
                    targetIndex++;
                }
            }
            else
            {
                for(uint64_t index = m_uiHead; index <= m_uiTail; index++)
                {
                    pNewArray[targetIndex] = m_paItems[index];
                    targetIndex++;
                }
            }

            m_uiHead = 0;
            m_uiTail = targetIndex - 1;
        }
        else
        {
            m_uiHead = 0;
            m_uiTail = -1;
        }

        // delete old array and set member pointer to bigger array
        delete[] m_paItems;
        m_paItems = pNewArray;
        m_uiArraySize = newLength;

        fResult = true;
    }
    else
    {
        fResult = true;
    }

    if(m_uiTail == m_uiArraySize - 1)
    {
        m_uiTail = 0;
    }
    else
    {
        m_uiTail++;
    }

    m_paItems[m_uiTail] = a_oItem;
    m_uiSize++;

    return fResult;
}

//-----------------------------------------------
// pop
template<typename T>
bool_t CMyQueue<T>::pop(T &a_oItem)
{
    bool_t fResult = false;

    if(0 < m_uiSize)
    {
        T _item = m_paItems[m_uiHead];

        if(m_uiHead == m_uiArraySize-1)
        {
            m_uiHead = 0;
        }
        else
        {
            m_uiHead++;
        }

        m_uiSize--;
        a_oItem = _item;

        tryReleaseMem();

        fResult = true;
    }
    else
    {
        a_oItem = T(0);
    }

    return fResult;
}

//-----------------------------------------------
// peek
template<typename T>
bool_t CMyQueue<T>::peek(T &a_oItem)
{
    bool_t fResult = false;

    if(0 < m_uiSize)
    {
        a_oItem = m_paItems[m_uiHead];
        fResult = true;
    }

    return fResult;
}

//-----------------------------------------------
// size
template<typename T>
uint64_t CMyQueue<T>::size()
{
    return m_uiSize;
}

//-----------------------------------------------
// getQueueInfo
template<typename T>
void CMyQueue<T>::getQueueInfo(CQueueInfo &a_oInfo)
{
    CQueueInfo oInfo;
    oInfo.m_uiArraySize = m_uiArraySize;
    oInfo.m_uiHead      = m_uiHead;
    oInfo.m_uiSize      = m_uiSize;
    oInfo.m_uiTail      = m_uiTail;
    oInfo.m_uiMemSize   = m_uiArraySize * sizeof(T);

    a_oInfo = oInfo;
}

//-----------------------------------------------
// getItems
template<typename T>
bool_t CMyQueue<T>::getItems(T *a_atItemsArray, uint64_t a_ui64Size)
{
    bool_t fResult = false;

    fResult = copyArray(m_paItems, a_atItemsArray, a_ui64Size);

    return fResult;
}

//-----------------------------------------------
// clear
template<typename T>
bool_t CMyQueue<T>::clear()
{
    bool_t fResult = false;

    if(0 < m_uiSize)
    {
        T *oldArray = m_paItems; // pointer to old array
        T *newArray = new T[g_uiInitalSize];  // pointer to new array

        m_uiArraySize = 0;
        m_uiSize = 0;
        m_uiTail = -1;
        m_uiHead = 0;

        m_paItems = newArray;
        delete[] oldArray;
    }

    return fResult;
}

/// private

//-----------------------------------------------
// copyArray
template<typename T>
bool_t CMyQueue<T>::copyArray(T *a_paSource, T *a_paDest, uint64_t a_uiSize)
{
    bool_t fResult = false;

    if(0 != a_paSource && 0 != a_paDest)
    {
        for(uint64_t idx = 0; idx < a_uiSize; idx++)
        {
            if(idx < m_uiSize)
            {
                a_paDest[idx] = a_paSource[idx];
            }
            else
            {
                a_paDest[idx] = T(0);
            }
        }

        fResult = true;
    }

    return fResult;
}

//-----------------------------------------------
// tryReleaseMem
template<typename T>
void CMyQueue<T>::tryReleaseMem()
{
    if(m_uiSize > 0 && MIN_SIZE < m_uiArraySize)
    {
        if(m_uiArraySize / m_uiSize == 2)
        {
            T *oldArray = m_paItems; //pointer to old array
            T *newArray = new T[m_uiSize]; // pointer to new array

            copyArray(oldArray, newArray, m_uiSize); // copy

            m_paItems = newArray;
            m_uiArraySize = m_uiSize;

            delete[] oldArray;
        }
    }
}

