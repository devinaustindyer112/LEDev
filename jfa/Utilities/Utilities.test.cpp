#include "Utilities.hpp"
#include "../catch_amalgamated.hpp"

TEST_CASE("size", "[size]")
{
    REQUIRE(size("test") == 4);
    REQUIRE(size("") == 0);
}

TEST_CASE("equals", "[equals]")
{
    REQUIRE(strCompare("test", "test") == 1);
    REQUIRE(strCompare("test", "false") == 0);
}