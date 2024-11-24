//! Problem Statement: Implement a Hash Table with Fixed Slots
//! 
//! Design a hash table with **26 slots** to store and manage keys. 
//! The hash table supports the following operations:
//! 
//! ## Input Format:
//! 1. Each input is a string:
//!    - The first character is either:
//!      - `A`: Add a key to the table.
//!      - `D`: Delete a key from the table.
//!    - The rest of the string is the key (lowercase letters from `a` to `z`).
//!    - Ignore invalid inputs (e.g., keys longer than 10 characters, non-lowercase characters).
//! 
//! ## Hash Table Details:
//! - **Size**: 26 slots, each indexed by a hash value.
//! - **Slot States**:
//!   - **Never Used**: The slot has never been occupied.
//!   - **Tombstoned**: The slot once held a key but is now marked as deleted.
//!   - **Occupied**: The slot currently holds a key.
//! - **Key Constraints**:
//!   - Keys are lowercase English letters.
//!   - Maximum key length: 10 characters.
//! 
//! ## Hashing:
//! - Compute the hash value of a key using its **last character** (e.g., the hash value of `"abc"` is based on `'c'`).
//! - Use **open addressing with linear probing** for collision resolution:
//!   - If the slot for a hash value is occupied or tombstoned, check the next slot, wrapping around if necessary.
//! 
//! ## Operations:
//! 1. **Add (`A key`)**:
//!    - Search for the key:
//!      - If the key already exists in the table, do nothing.
//!    - If the key doesn't exist:
//!      - Compute its hash value and find the first free slot (either "never used" or "tombstoned").
//!      - Insert the key into that slot.
//! 2. **Delete (`D key`)**:
//!    - Search for the key:
//!      - If the key exists, mark its slot as "tombstoned."
//!      - If the key doesn't exist, do nothing.

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using u8  = uint8_t;
using i8  = int8_t;
using u16 = uint16_t;
using i16 = int16_t;
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

template <typename T> using vec = std::vector<T>;

template <typename T> struct is_string {
  static constexpr bool value = false;
};

template <typename Traits, typename Alloc>
struct is_string<std::basic_string<char, Traits, Alloc>> {
  static constexpr bool value = true;
};

template <typename T> constexpr bool is_string_like() {
  using expr = std::__remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>;

  if constexpr (std::is_same_v<expr, char>)
    return true;
  return false;
}

template <typename T> constexpr bool is_string_like_v = is_string_like<T>();
template <typename T> constexpr bool is_string_v = is_string<T>::value;

template <typename T>
concept StringType = is_string_v<T> or is_string_like_v<T> ;

enum class opType
{
    Unknown = 0,
    Add     = 1,
    Delete  = 2
};

template<StringType T>
class parser
{
public:
    struct OpTok
    {
        opType m_Operations = opType::Unknown;
        std::string m_Tokens;

        OpTok(char const& lOpType, std::string&& lToken)
        {
            if(lOpType == 'A')
                m_Operations = opType::Add;
            else if(lOpType == 'D')
                m_Operations = opType::Delete;

            m_Tokens = std::move(lToken);
        }

        friend std::ostream& operator<<(std::ostream &lOutStream, OpTok const& lOutData)
        {
            lOutStream << '[';
            switch(lOutData.m_Operations)
            {
            case opType::Add:
                lOutStream << "Add";
                break;
            case opType::Delete:
                lOutStream << "Delete";
                break;
            default:
                lOutStream << "Unknown";
                break;
            }
            lOutStream << ", " << lOutData.m_Tokens << ']';
            return lOutStream;
        }
    };

private:
    static constexpr auto m_IsValidOpr = [](const char &lRefOpr) -> bool {
        return (('A' == lRefOpr) or ('D' == lRefOpr));
    };
    static constexpr auto m_IsValidTok = [](const std::string &lRefTok) -> bool {
        return ((10 >= lRefTok.size()) and
                std::all_of(lRefTok.begin(), lRefTok.end(),
                    [](char const &lTokChar) { return lTokChar >= 'a' and lTokChar <= 'z'; }));
    };

    vec<OpTok> m_vOpTokens;
public:

    parser(T const &lBuffer) { tokenizer(lBuffer); }
    void tokenizer(T const& lBuffer)
    {
        std::stringstream lStringStream = [&]() -> std::stringstream
            {
                if constexpr(is_string_v<T>)
                    return std::stringstream(lBuffer);
                else 
                    return std::stringstream(std::string(lBuffer));
            }();

        while(lStringStream.good())
        {
            std::string lTmpTok;
            lStringStream >> lTmpTok;

            if(lTmpTok.size() <= 1)
                continue;

            const char lOpType = lTmpTok[0];
            lTmpTok = lTmpTok.substr(1);

            if(m_IsValidOpr(lOpType) and m_IsValidTok(lTmpTok))
            {
                m_vOpTokens.emplace_back(lOpType, std::move(lTmpTok));
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& lOutStream, parser const& lOutData)
    {
        for(auto const& lRefOpToks : lOutData.m_vOpTokens)
            lOutStream << lRefOpToks << ' ';

        return lOutStream;
    }

    inline i32  size()  const { return m_vOpTokens.size();  }
    inline auto begin() const { return m_vOpTokens.begin(); }
    inline auto end()   const { return m_vOpTokens.end();   }
};

template<StringType T = const char *>
class HashTable
{
private:
    enum class TableState
    {
        NeverUsed  = 0,
        TombStoned = 1,
        Occupied   = 2
    };

    struct HashCell
    {
        TableState m_CellState = TableState::NeverUsed;
        std::string m_CellData;
    };

    static constexpr u32 HASH_TABLE_SIZE = 26u;
    HashCell m_DataTable[HASH_TABLE_SIZE];
    parser<T> m_ParsedData;

public:
    HashTable(T const& lDataToParse) : m_ParsedData(lDataToParse) {}
    HashTable() : m_ParsedData("") {}

    i32 Find(std::string const& lTableKey) const
    {
        i32 lTableIdx = lTableKey.back() - 'a';
        i32 lMaxItrs = HASH_TABLE_SIZE;
        while(lMaxItrs > 0)
        {
            if (m_DataTable[lTableIdx].m_CellState != TableState::Occupied or
                m_DataTable[lTableIdx].m_CellData == lTableKey)
                return lTableIdx;
            else
                lTableIdx = (lTableIdx + 1) % HASH_TABLE_SIZE;

            --lMaxItrs;
        }

        return -1;
    }

    bool Add(std::string const& lTableKey)
    {
        i32 lTableIdx = Find(lTableKey);
        if(lTableIdx >= 0)
        {
            m_DataTable[lTableIdx] = {TableState::Occupied, lTableKey};
            return true;
        }
        return false;
    }

    bool Delete(std::string const& lTableKey)
    {
        i32 lTableIdx = Find(lTableKey);
        if(lTableIdx >= 0)
        {
            if(TableState::Occupied == m_DataTable[lTableIdx].m_CellState)
                m_DataTable[lTableIdx].m_CellState = TableState::TombStoned;

            return true;
        }
        return false;
    }

    HashTable<T>& TokenizeData(T const& lDataToParse)
    {
        m_ParsedData.tokenizer(lDataToParse);
        return *this;
    }
    HashTable& ExecuteTokenizedData()
    {
        for(auto const& lRefParsedData : m_ParsedData)
        {
            switch (lRefParsedData.m_Operations) 
            {
            case opType::Add:
                std::cout << "Add: " << lRefParsedData.m_Tokens << ' ' << std::boolalpha << Add(lRefParsedData.m_Tokens) << '\n';
                break;
            case opType::Delete:
                std::cout << "Delete: " << lRefParsedData.m_Tokens << ' ' << std::boolalpha << Delete(lRefParsedData.m_Tokens) << '\n';
                break;
            default:
                std::cout << "Error: Unknown type provided...\n";
                break;
            }
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &lOutStream, HashTable const& lOutData)
    {
        lOutStream << "========== HashTable internal parser state ==========\n";
        lOutStream << lOutData.m_ParsedData << '\n';

        i32 lIndex = 0;
        lOutStream << "============== HashTable internal state ==============\n";
        for(auto const& lRefExecutedState : lOutData.m_DataTable)
        {
            lOutStream << '[' << std::setw(2) << lIndex << "]:: [" << std::setw(11);
            switch(lRefExecutedState.m_CellState)
            {
            case TableState::NeverUsed:
                lOutStream << "NeverUsed";
                break;
            case TableState::TombStoned:
                lOutStream << "Tombstoned";
                break;
            case TableState::Occupied:
                lOutStream << "Occupied";
                break;
            }
            lOutStream << ", " << std::setw(10) << lRefExecutedState.m_CellData << "]\n";
            ++lIndex;
        }
        return lOutStream;
    }
};

template<StringType T = const char *>
class HashTableBuilder 
{
private:
    std::string m_InitialData;
    bool m_ExecuteTokens = false;

public:
    // Method to set initial data
    HashTableBuilder& withInitialData(T const& lInitData) 
    {
        if constexpr(is_string_v<T>)
            m_InitialData = lInitData;
        else
            m_InitialData = std::string(lInitData);
        return *this;
    }
    HashTableBuilder& ExecuteTokenizedData(bool const& lOptVal)
    {
        m_ExecuteTokens = lOptVal;
        return *this;
    }

    // Build method to create the HashTable object
    HashTable<std::string> build() const 
    {
        if(m_ExecuteTokens)
            return HashTable<std::string>(m_InitialData).ExecuteTokenizedData();
        else
            return HashTable<std::string>(m_InitialData);
    }
};

int main(void)
{
    const char *lPtrTestString = "Aapple Agrape Dapple Astrawberry Aorange";
    HashTable lTableObj = HashTableBuilder()
                              .withInitialData(lPtrTestString)
                              .ExecuteTokenizedData(true)
                              .build();
    std::cout << lTableObj;

    return 0;
}
