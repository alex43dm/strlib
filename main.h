#ifndef __STR_CLASS_
#define __STR_CLASS_

#include <string>
#include <vector>

struct chank
{
    std::string s;
    size_t num;
    chank(const std::string &s, const size_t &p) : s(s), num(p) {};
};

class str
{
        std::string s;
        std::vector<chank> m;
        int occurences;
        size_t m_hash;
        std::hash<std::string> _hash;
    public:
        str(const std::string s);
        inline void print() const;
        inline const std::string &get() const { return s; };
        inline size_t size() const { return s.size(); };
        inline int get_occurences() const { return occurences; };
        inline void add_occurences() { occurences++; };
        inline void zero_occurences() { occurences = 1; };
        bool find_match();
        inline size_t get_hash() const { return m_hash; };
        void print_chanks() const;
        bool find_chank(const std::string &s) const;
        void print_max_chank() const;
};

//the function for words parse
void process(const std::string &);

#endif //__STR_CLASS_
