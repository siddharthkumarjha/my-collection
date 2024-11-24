#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using u32 = uint32_t;
using i32 = int32_t;
u32 g_CopyCounter = 0;
u32 g_AllocationCounter = 0;
u32 g_MoveCounter = 0;

class String
{
private:
    char *m_Data;
    u32 m_DataSize;

public:
    String() : m_Data(nullptr), m_DataSize(0u) {}
    String(const char* const& lBuffer)
    {
        ++g_AllocationCounter;

        if(nullptr != lBuffer)
        {
            m_DataSize = strlen(lBuffer) + 1;
            m_Data = new char[m_DataSize];
            std::memcpy(m_Data, lBuffer, m_DataSize - 1);
            m_Data[m_DataSize - 1] = '\0';
        }
        else
        {
            m_Data = nullptr;
            m_DataSize = 0u;
        }
    }
    ~String()
    {
        delete[] m_Data;
        m_Data = nullptr;
    }

    String(String const& lOtherData)
    {
        ++g_CopyCounter;

        if(lOtherData.m_DataSize > 0u)
        {
            ++g_AllocationCounter;

            this->m_Data = new char[lOtherData.m_DataSize];
            this->m_DataSize = lOtherData.m_DataSize;
            std::memcpy(this->m_Data, lOtherData.m_Data, this->m_DataSize);
        }
        else
        {
            this->m_Data = nullptr;
            this->m_DataSize = 0u;
        }
    }

    String(String&& lOtherData)
    {
        ++g_MoveCounter;

        this->m_DataSize = lOtherData.m_DataSize;
        this->m_Data = lOtherData.m_Data;

        lOtherData.m_Data = nullptr;
        lOtherData.m_DataSize = 0u;
    }

    String& operator=(String const& lOtherData)
    {
        ++g_CopyCounter;

        if(&lOtherData != this)
        {
            delete[] this->m_Data;

            if(lOtherData.m_DataSize > 0u)
            {
                ++g_AllocationCounter;

                this->m_Data = new char[lOtherData.m_DataSize];
                this->m_DataSize = lOtherData.m_DataSize;

                std::memcpy(this->m_Data, lOtherData.m_Data, this->m_DataSize);
            }
            else
            {
                this->m_Data = nullptr;
                this->m_DataSize = 0u;
            }
        }
        return *this;
    }

    String& operator=(String&& lOtherData)
    {
        ++g_MoveCounter;

        if(&lOtherData != this)
        {
            delete[] this->m_Data;

            this->m_DataSize = lOtherData.m_DataSize;
            this->m_Data = lOtherData.m_Data;

            lOtherData.m_DataSize = 0u;
            lOtherData.m_Data = nullptr;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &lOutStream,
                                    String const &lOutData)
    {
        if(nullptr != lOutData.m_Data)
            lOutStream << lOutData.m_Data;
        return lOutStream;
    }
};

void print(std::vector<String> const& l_vStrings)
{
    for(const auto &lRefStrings : l_vStrings)
        std::cout << lRefStrings << '\n';
}

int main(void)
{
    std::vector<String> l_vStrings;
    l_vStrings.reserve(5);
    for(i32 i = 0; i < 5; i++)
        l_vStrings.emplace_back("Hi This is sid!");

    print(l_vStrings);

    std::cout << "g_AllocationCounter:: " << g_AllocationCounter
              << " g_CopyCounter:: " << g_CopyCounter
              << " g_MoveCounter:: " << g_MoveCounter << '\n';
    return 0;
}
