#ifndef BENCH_UTIL_HEADER
#define BENCH_UTIL_HEADER

#include <string>

#include <ace/ace_wchar.h> // For ACE_TCHAR
#include <ace/Default_Constants.h> // For ACE_DIRECTORY_SEPARATOR_*

#include "Bench_Common_Export.h"

namespace Bench {

// Argument Parsing
std::string Bench_Common_Export get_option_argument(int& i, int argc, ACE_TCHAR* argv[]);
int Bench_Common_Export get_option_argument_int(int& i, int argc, ACE_TCHAR* argv[]);
unsigned Bench_Common_Export get_option_argument_uint(int& i, int argc, ACE_TCHAR* argv[]);

// Filesytem
std::string join_path(const std::string& arg) {
  return arg;
}
template <typename... Args>
std::string join_path(const std::string& arg, Args... args) {
  return arg + (arg.back() == ACE_DIRECTORY_SEPARATOR_CHAR ? "" : ACE_DIRECTORY_SEPARATOR_STR) + join_path(args...);
}
std::string Bench_Common_Export create_temp_dir(const std::string& prefix);

}

#endif
