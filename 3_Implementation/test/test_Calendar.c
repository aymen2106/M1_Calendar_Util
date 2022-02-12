#include "unity.h"
#include <Calendar.h>

#include <Calendar_op.h>
#define PROJECT_NAME    "Calendar"

void test_displayDay(void);
void test_displayMonthCalendar(void);
void test_AddNotes(void);
void test_Exit(void);

void setUp(){}

void tearDown(){}

int main()
{

  UNITY_BEGIN();

/* Run Test functions */
  RUN_TEST(test_displayDAY);
  RUN_TEST(test_displayMonthCalendar);
  RUN_TEST(test_AddNotes);
  RUN_TEST(test_Exit);

  /* Close the Unity Test Framework */
  return UNITY_END();
}

/* Write all the test functions */ 
void test_displayDAY(void) {
  TEST_ASSERT_EQUAL(SATURDAY, date(12 02 2022));
  

}

void test_subtract(void) {
  TEST_ASSERT_EQUAL(FEBRUARY-2022, date(02 2022));
  
  
}

