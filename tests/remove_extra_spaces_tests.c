#include <criterion/criterion.h>
#include "../include/server/server.h"

Test(remove_extra_spaces_tests, simple_spaces) {
    cr_assert_str_eq(remove_extra_spaces("a b"), "a b");
    cr_assert_str_eq(remove_extra_spaces("a   b"), "a b");
    cr_assert_str_eq(remove_extra_spaces("a   b   "), "a b");
    cr_assert_str_eq(remove_extra_spaces("    a   b"), "a b");
    cr_assert_str_eq(remove_extra_spaces("  a     b   "), "a b");
}