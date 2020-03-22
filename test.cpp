#include <fstream>
#if defined(WITH_THREADS)
#include <thread>
#endif
#include <gtest/gtest.h>

#include "main.h"

#define FILE_PATH "tests.txt"

using namespace std;

vector<string> stest;

class StrLib : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            ifstream samples;
            samples.open(FILE_PATH);
            if (!samples)
            {
                cerr << "Unable to open file: " << FILE_PATH << endl;
                stest.push_back("test dds ewqqee");
            }
            else
            {
                string line;
                while (getline(samples, line))
                    stest.push_back(line);
                samples.close();
            }
        }
};

TEST_F(StrLib, process)
{
#if defined(WITH_THREADS)
    vector<thread> proc;
#endif
    for (auto &t : stest)
    {
        std::cout << t << std::endl;
#if defined(WITH_THREADS)
        proc.push_back(thread(process, t));
#else
        process(t);
#endif
    }
#if defined(WITH_THREADS)
    for (auto &p : proc)
        p.join();
#endif
}

TEST_F(StrLib, constructor)
{
    for (auto &t : stest)
    {
        str *s = new str(t);
        EXPECT_NE(nullptr, s);
        delete s;
    }
}

TEST_F(StrLib, size)
{
    for (auto &t : stest)
    {
        str *s = new str(t);
        EXPECT_EQ(t.size(), s->size());
        delete s;
    }
}

TEST_F(StrLib, find_match_true)
{
    str s("testt");
    EXPECT_TRUE(s.find_match());
    EXPECT_TRUE(s.find_chank("t"));
}

TEST_F(StrLib, find_match_false)
{
    str s("test");
    EXPECT_FALSE(s.find_match());
    EXPECT_FALSE(s.find_chank("f"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
