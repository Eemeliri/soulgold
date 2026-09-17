#include "global.h"
#include "datetime.h"
#include "test/test.h"

TEST("ConvertTimeToDateTime handles a negative day")
{
    struct Time time = {.days = -1, .hours = 23, .minutes = 59, .seconds = 58};
    struct DateTime result;

    ConvertTimeToDateTime(&result, &time);

    EXPECT_EQ(result.year, 1999);
    EXPECT_EQ(result.month, MONTH_DEC);
    EXPECT_EQ(result.day, 31);
    EXPECT_EQ(result.dayOfWeek, WEEKDAY_FRI);
    EXPECT_EQ(result.hour, 23);
    EXPECT_EQ(result.minute, 59);
    EXPECT_EQ(result.second, 58);
}

TEST("ConvertTimeToDateTime normalizes negative clock fields")
{
    struct Time time = {.days = 0, .hours = 0, .minutes = 0, .seconds = -1};
    struct DateTime result;

    ConvertTimeToDateTime(&result, &time);

    EXPECT_EQ(result.year, 1999);
    EXPECT_EQ(result.month, MONTH_DEC);
    EXPECT_EQ(result.day, 31);
    EXPECT_EQ(result.dayOfWeek, WEEKDAY_FRI);
    EXPECT_EQ(result.hour, 23);
    EXPECT_EQ(result.minute, 59);
    EXPECT_EQ(result.second, 59);
}

TEST("ConvertTimeToDateTime handles the minimum saved day count")
{
    struct Time time = {.days = -32768};
    struct DateTime result;

    ConvertTimeToDateTime(&result, &time);

    EXPECT_EQ(result.year, 1910);
    EXPECT_EQ(result.month, MONTH_APR);
    EXPECT_EQ(result.day, 15);
    EXPECT_EQ(result.dayOfWeek, WEEKDAY_FRI);
}

TEST("ConvertTimeToDateTime preserves positive leap-day behavior")
{
    struct Time time = {.days = 60, .hours = 12, .minutes = 34, .seconds = 56};
    struct DateTime result;

    ConvertTimeToDateTime(&result, &time);

    EXPECT_EQ(result.year, 2000);
    EXPECT_EQ(result.month, MONTH_MAR);
    EXPECT_EQ(result.day, 1);
    EXPECT_EQ(result.dayOfWeek, WEEKDAY_WED);
    EXPECT_EQ(result.hour, 12);
    EXPECT_EQ(result.minute, 34);
    EXPECT_EQ(result.second, 56);
}
