#include <fstream>
#include <gtest/gtest.h>
#include "work.h"

std::string input_name;

TEST(Work_in_computers_club, Test_1_ALL_RUN) {
    std::ifstream real("google_test/test_real");
    std::ifstream check("google_test/check.txt");
    work_in_club(input_name.c_str());

    std::string work_r, work;
    while (std::getline(real, work_r) && std::getline(check, work)) {
    ASSERT_EQ(work_r, work);
    }
}

TEST(Work_in_computers_club, Test_2_ALL_RUN) {
    std::ifstream real("google_test/test_real2.txt");
    std::ifstream check("google_test/check.txt");
    work_in_club("google_test/test2.txt");

    std::string work_r, work;
    while (std::getline(real, work_r) && std::getline(check, work)) {
        ASSERT_EQ(work_r, work);
    }
}

TEST(Work_in_computers_club, Test_3_WRONG_INPUT_DATA_ID_1) {
    ASSERT_DEATH({work_in_club("google_test/test3.txt");}, "06:00 1 cliEnt&");
}

TEST(Work_in_computers_club, Test_4_WRONG_INPUT_DATA_ID_2) {
    ASSERT_DEATH({work_in_club("google_test/test4.txt");}, "06:00 2 client");
}

TEST(Work_in_computers_club, Test_5_WRONG_INPUT_DATA_ID_3) {
    ASSERT_DEATH({work_in_club("google_test/test5.txt");}, "06:3 3 client3");
}

TEST(Work_in_computers_club, Test_6_WRONG_INPUT_DATA_ID_4) {
    ASSERT_DEATH({work_in_club("google_test/test6.txt");}, "06:00 4 client 2");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    input_name = argv[1];
    return RUN_ALL_TESTS();
}
