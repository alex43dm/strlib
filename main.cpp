#include <iostream>
#include <regex>

#include "main.h"

#define WORDS "(\\w)+"

str::str(const std::string s) : s(s), occurences(1)
{
    m_hash = _hash(s);
}

/* print
 * print string size and hash
 */
void str::print() const
{
    std::cout << s << " size:" << s.size() << " hash:" << m_hash << std::endl;
}

/* print_chanks
 * print all repeatable sequences
 */
void str::print_chanks() const
{
    if (m.size() == 0) return;

    for (auto i = m.begin(); i != m.end(); ++i)
    {
        std::cout << "chank: " << i->s << " num:" << i->num;
        if ((i + 1) != m.end())
            std::cout << " ";
    }
    std::cout << std::endl;
}

/* print_max_chank
 * print longest repeatable sequence
 */
void str::print_max_chank() const
{
    if (m.size() == 0) return;
    auto max = m.begin();
    for (auto i = m.begin() + 1; i != m.end(); ++i)
    {
        if (max->num < i->num)
            max = i;
    }

    std::cout << "longest repeatable sequence: " << max->s << " num: " << max->num << std::endl;
}


bool str::find_chank(const std::string &s) const
{
    for (auto i = m.begin(); i != m.end(); ++i)
    {
        if (i->s == s) return true;
    }
    return false;
}

/* find_match
 * find in string s longest repeatable sequence
 */
bool str::find_match()
{
    bool ret = false;
    if (s.size() == 1) return ret;

    //find chars repeats
    for (auto i = s.begin(); i != s.end(); ++i)
    {
        auto j = i + 1;
        for (; j != s.end() && *i == *j; ++j);

        if (i + 1 != j)
        {
            m.push_back(chank(std::string(1, *i), j - i));
            ret = true;
            if (j == s.end()) break;
            i = j - 1;
        }
    }

    if (s.size() == 2) return ret;

    //find substring repeats
    for (size_t i = 2; i <= s.size() / 2; ++i)
    {
        for (auto j = s.begin(); j != s.end(); j += i)
        {
            if (j + i > s.end()) break;
            size_t h1 = _hash(std::string(j, j + i));
            size_t num = 0;
            for (auto x = j + i; x != s.end(); x += i)
            {
                if (x + i > s.end()) break;
                size_t h2 = _hash(std::string(x, x + i));
                if (h1 == h2)
                {
                    num++;
                }
                else
                {
                    break;
                }
            }

            if (num)
            {
                std::string sample = std::string(j, j + i);
                if (!find_chank(sample))
                    m.push_back(chank(sample, num + 1));
            }
        }
    }

    return ret;
};

/* process function
 * input: string for parse
 */
void process(const std::string &s)
{
    std::regex re(WORDS);
    std::vector<str> res;
    int longest = 0;

    using sit = std::sregex_iterator;
    for (sit it = sit(s.begin(), s.end(), re); it != sit(); ++it)
    {
        str st = str(it->str(0));
        res.push_back(st);

        if (res.size() && res[longest].size() < st.size())
        {
            longest = res.size() - 1;
        }

        //3. the word with longest repeatable sequence
        st.find_match();

        st.print();
        st.print_max_chank();
    }

    //1. count of words
    std::cout << "number of any words: "  << res.size() << std::endl;

    //2. the longest word
    std::cout << "longest word: "  << res[longest].get() << " size: " << res[longest].size() <<
              std::endl;

    //4. reverse words
    std::cout << "reverse words: ";
    for (auto w = res.rbegin(); w != res.rend(); ++w)
    {
        std::cout <<  w->get();
        if ((w + 1) != res.rend())
            std::cout << " ";
    }
    std::cout << std::endl;

    //1.1 Optional : output - array of structures with word/number of occurrences
    for (auto w = res.begin(); w != res.end(); ++w)
    {
        for (auto v = res.begin(); v != res.end(); ++v)
        {
            if (w == v || v->get_occurences() == 0 || w->get_occurences() == 0) continue;
            if (w->get_hash() == v->get_hash() && v->get_occurences() == 1)
            {
                w->add_occurences();
                v->zero_occurences();
            }
        }
    }
    std::cout << "occurences words: ";
    for (auto w = res.begin(); w != res.end(); ++w)
    {
        if (w->get_occurences() == 0) continue;
        std::cout <<  w->get() << ":" << w->get_occurences();
        if ((w + 1) != res.end())
            std::cout << " ";
    }
    std::cout << std::endl;
}
