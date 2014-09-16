
#include <string>

#include <cpprest/asyncrt_utils.h>
#include <pplx/pplxtasks.h>

namespace yoda_utilities
{

// Converts a string of text to Yoda speech.
pplx::task<utility::string_t> convert_to_yoda(const utility::string_t &text);

// Checks a string of text for grammar errors, returning a report.
pplx::task<utility::string_t> check_grammar(const utility::string_t &text);

}
