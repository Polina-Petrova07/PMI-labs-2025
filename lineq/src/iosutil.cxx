#include "iosutil.hxx"
#include <iostream>
using namespace std;
void eat_pad(istream& i) {
    try {
        while (i.good()) {
            int c = i.peek();
            if (!i.good() || isgraph(c) != 0 || c == '\n') break;
            i.get();
        }
    } catch (istream::failure const&) {}
}
void setstate_noexcept(istream& i, istream::iostate sta) noexcept {
    try { i.setstate(sta); } catch (istream::failure const&) {}
}

throw_only_bad::throw_only_bad(basic_ios<char>& ios) : ios(ios), prev_exc(ios.exceptions())
   { ios.exceptions(prev_exc & basic_ios<char>::badbit); }
throw_only_bad::~throw_only_bad() { ios.exceptions(prev_exc); }
