// PROBLEM DEFINITION
// ------------------
// Reverse each word in the input string.
// The order of the words will be unchanged.
// A word is made up of letters and/or numbers.
// Other characters (spaces, punctuation) will not be reversed.
// NOTES
// ------
// Write production quality code
// We prefer clarity over performance (though if you can achieve both - great!)
// You can use the language that best highlights your programming ability
// the template below is in C++
// A working solution is preferred (assert in main() should succeed)
// Bonus points for good tests

#include <string>
#include <cassert>
#include <string_view>
#include <utility>
#include <iostream>
#include <cstring>

/**
 * @brief Reverses a substring of the given string in-place.
 *
 * Performs the reversal directly on the original string without
 * creating a copy or allocating additional storage.
 *
 * Example:
 *   Input  : "abcdef", start = 1, size = 4
 *   Output : "aedcbf"
 *
 * @param str   Original string whose contents are modified in-place.
 * @param start Starting index of the substring.
 * @param size  Length of the substring.
 */

inline void reverse_string(std::string &str, size_t start, size_t size)
{
    size_t left_itr = start, right_itr = start + size - 1;

    while (left_itr < right_itr)
    {
        std::swap(str[left_itr], str[right_itr]);

        left_itr++;
        right_itr--;
    }
}

/**
 * @brief reverses the words while maintaining sentence order
 *
 * A word is defined as a contiguous sequence of alphanumeric
 * characters (A-Z, a-z, 0-9). Any non-alphanumeric character
 * acts as a separator and remains in its original position.
 *
 * Examples:
 *   "Hello World" -> "olleH dlroW"
 *   "abc 123"     -> "cba 321"
 *   "Test_String" -> "tseT_gnirtS"
 *
 * @param str Input string to process.
 *
 * @return String with each word reversed while preserving
 *         word order and separators.
 */

std::string reverse_words(std::string &str)
{

    size_t start_pos = -1; // starting position of word (0-based indexing)
    size_t i = 0;          // iterator for the string
    size_t sz = 0;         // size of the word

    const size_t total_sz = str.size();

    while (i < total_sz)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
        {
            if (start_pos == -1) // default value, needs to be changed
            {
                start_pos = i;
            }

            sz++;
        }

        else
        {
            // Word ends. Reverse the word
            if (start_pos != -1)
                reverse_string(str, start_pos, sz);

            // Reset the tracking params
            start_pos = -1;
            sz = 0;
        }

        i++; // move to the next char
    }

    // Handle the last traversed word
    if (start_pos != -1)
        reverse_string(str, start_pos, sz);

    return str;
}

int main()
{
    std::string test_str = "String; 2be reversed..."; // Check for mix of Upper case, lower case, numbers and other characters
    assert(strcmp(reverse_words(test_str).c_str(), "gnirtS; eb2 desrever...") == 0);

    std::string test_str_1 = "String;    2  b  e  reversed"; // Check if algo is able to handle multiple spaces/other characters in between
    assert(strcmp(reverse_words(test_str_1).c_str(), "gnirtS;    2  b  e  desrever") == 0);

    std::string test_str_2 = "  Test_String  "; // Check if space is not the only seperator present (Since it is not mentioned in requirement)
    assert(strcmp(reverse_words(test_str_2).c_str(), "  tseT_gnirtS  ") == 0);

    std::string test_str_3 = "::::...."; // Check if there is no alphanumeric char present
    assert(strcmp(reverse_words(test_str_3).c_str(), "::::....") == 0);

    std::string test_str_4 = "Test\n\t\nString"; // Check if \n and \t are handled correctly
    assert(strcmp(reverse_words(test_str_4).c_str(), "tseT\n\t\ngnirtS") == 0);

    return 0;
}
