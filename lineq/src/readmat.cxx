#include "readmat.hxx"
#include "iosutil.hxx"
#include "mat_mem.hxx"
#include <stdexcept>
using namespace std;

struct row_start { bool matend = false; };
static istream& operator>>(istream& i, row_start& s) {
    eat_pad(i);
    if (!i.good()) return i;

    char c = i.peek();
    if (i.fail() && !i.eof()) return i;

    if (i.eof() || is_nl(c)) {
        s.matend = true; // Declare end of matrix
        return i;
    }

    if (!is_num_start(c)) i.setstate(istream::failbit); // Not a row start at all
    return i;
}

struct row_end { bool end = false; };

static istream& operator>>(istream& i, row_end& s) {
    s.end = false;
    eat_pad(i);
    char c = i.peek();
    if (!i.eof() && (!i || !is_nl(c))) return i;
    if (i.good()) i.get();
    s.end = true;
    return i;
}

struct split_or_frac {
    frac f;
    bool split = false;
};
static istream& operator>>(istream& i, split_or_frac& sof) {
    sof.f     = {};
    sof.split = false;
    eat_pad(i);
    if (!i.good()) return i;
    if (i.peek() == '|') {
        i.get();
        sof.split = true;
        return i;
    }
    i >> sof.f;
    return i;
}

void read_mat( // NOLINT (cognitive complexity)
    istream& i,
    mat_mem<frac, mat_maj::row>& o,
    size_t& split
) {
    o = {};
    size_t cur_row = 0, cur_col = 0;
    split = 0;
    bool row_had_split = false;
    if (!i.good()) return;
    row_start start;
    row_end   end  ;

    i >> start;
    if (!i.good() || start.matend) return;

    while (i.good()) {
        i >> end;
        if (end.end) {
            if (cur_col == 0) break; // End of matrix
            // New row
            if (!row_had_split) throw runtime_error("missing matrix split");
            row_had_split = false;
            cur_row++;
            cur_col = 0;
            continue;
        }
        if (!i.good()) return;

        split_or_frac sf;
        i >> sf;
        if (i.fail()) return;
        int c = i.peek();
        if (i.good() && isgraph(c) != 0 && !is_num_start(c) && c != '|')
            throw runtime_error("unexpected character");

        if (sf.split) {
            if (row_had_split) throw runtime_error("multiple matrix splits in a row");
            row_had_split = true;
            if (cur_row == 0) split = cur_col;
            else if (cur_col != split) throw runtime_error("inconsistent matrix split");
            continue;
        }

        if (cur_col == 0) o.grow_row();
        if (cur_col == o.m().n_cols()) o.grow_col();
        o.m()[cur_row][cur_col] = sf.f;
        cur_col++;
    }

    if (cur_row == 0 && !row_had_split) throw runtime_error("missing matrix split");
}
