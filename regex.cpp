// (ha+)+
// s -> h J
// J -> a s | a J | a
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
class RegexHa
{
private:
    using u32 = uint32_t;

    u32 m_CurPos = 0u;
    bool m_ParseSuccess = false;
    std::string m_InputString;
    std::string m_ErrorMsg;

    bool match(char const& lCharToMatch)
    {
        if((m_CurPos < m_InputString.size()) and (lCharToMatch == m_InputString[m_CurPos]))
        {
            ++m_CurPos;
            return true;
        }
        return false;
    }

    bool ruleS()
    {
        if(match('h'))
            return ruleJ();
        return false;
    }

    bool ruleJ()
    {
        if(match('a'))
        {
            if(m_CurPos == m_InputString.size())
                return true;
            else if(ruleS())
                return true;
            else if(ruleJ())
                return true;
            else
                return false;
        }
        return false;
    }

    bool parse()
    {
        m_ParseSuccess = ('h' == m_InputString.front()) and ('a' == m_InputString.back());
        if (not m_ParseSuccess) 
        {
            m_ErrorMsg =
                "unexpected tokens at the start/end of input string parsing "
                "stopped, expected \"h\" at start and \"a\" at the end";
            return false;
        }

        m_ParseSuccess = ruleS() and (m_CurPos == m_InputString.size());
        if (not m_ParseSuccess) 
        {
            if (m_CurPos < m_InputString.size())
                m_ErrorMsg =
                    "parsing failed at position: " + std::to_string(m_CurPos) +
                    " (expected more input)";
            else
                m_ErrorMsg = "parsing failed: unexpected end of input";
        }
        return m_ParseSuccess;
    }
public:

    bool parse(std::string const& lStringToParse)
    {
        m_InputString = lStringToParse;
        return parse();
    }

    bool parse(std::string&& lStringToParse)
    {
        m_InputString = std::move(lStringToParse);
        return parse();
    }

    friend std::ostream& operator<<(std::ostream &lOutStream, RegexHa const& lRegex)
    {
        lOutStream << std::quoted(lRegex.m_InputString) << ' ';
        if(lRegex.m_ParseSuccess)
            lOutStream << "parsed with success";
        else
             lOutStream << lRegex.m_ErrorMsg;
        return lOutStream;
    }
};

int main(void) 
{ 
    std::string lTestCases[] = {"ha", "haha", "hahaha", "hahaaa", "haah", "ah", "h", "haaaaaah"};
    for(const auto &lStringToCheck : lTestCases)
    {
        RegexHa lRegex;
        std::cout << std::boolalpha << lRegex.parse(lStringToCheck) << ' ' << lRegex << '\n';
    }
    return 0; 
}
