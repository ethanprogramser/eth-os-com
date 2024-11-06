#include "klib/kctype.h"

/* Table grabbed from https://cppreference.com/
 *
 * fig. 1:
 * +----------------------------------------------------------------------+
 * |           ASCII           |       |    |    |    |    |    |    |    |
 * |---------------------------| Chars | cn | pr | sp | bl | gr | pn | an |
 * |   dec   |  hex  |   oct   |       |    |    |    |    |    |    |    |
 * |---------+-------+---------+-------+----+----+----+----+----+----+----|
 * |     0-8 |   0-8 |    0-10 |   cc1 |  X |  - |  - |  - |  - |  - |  - |
 * |       9 |     9 |      11 |   tab |  X |  - |  X |  X |  - |  - |  - |
 * |   10-13 |   A-D |   12-15 |    ws |  X |  - |  X |  - |  - |  - |  - |
 * |   14-31 |  E-1F |   16-37 |   cc2 |  X |  - |  - |  - |  - |  - |  - |
 * |      32 |    20 |      40 |   spc |  - |  X |  X |  X |  - |  - |  - |
 * |   33-47 | 21-2F |   41-57 |   pn1 |  - |  X |  - |  - |  X |  X |  - |
 * |   48-57 | 30-39 |   60-71 |   num |  - |  X |  - |  - |  X |  - |  X |
 * |   58-64 | 3A-40 |  72-100 |   pn2 |  - |  X |  - |  - |  X |  X |  - |
 * |   65-70 | 41-46 | 101-106 |   ulx |  - |  X |  - |  - |  X |  - |  X |
 * |   71-90 | 47-5A | 107-132 |    ul |  - |  X |  - |  - |  X |  - |  X |
 * |   91-96 | 5B-60 | 133-140 |   pn3 |  - |  X |  - |  - |  X |  X |  - |
 * |  97-102 | 61-66 | 141-146 |   llx |  - |  X |  - |  - |  X |  - |  X |
 * | 103-122 | 67-7A | 147-172 |    ll |  - |  X |  - |  - |  X |  X |  X |
 * | 123-126 | 7B-7E | 173-176 |   pn4 |  - |  X |  - |  - |  X |  - |  - |
 * |     127 |    7F |     177 |    bs |  X |  - |  - |  - |  - |  - |  - |
 * +----------------------------------------------------------------------+
 *
 * fig. 2:
 * +------------------------------------------------------------+
 * |           ASCII           |       |    |    |    |    |    |
 * |---------------------------| Chars | al | up | lo | dg | xd |
 * |   dec   |  hex  |   oct   |       |    |    |    |    |    |
 * |---------+-------+---------+-------+----+----+----+----+----|
 * |     0-8 |   0-8 |    0-10 |   cc1 |  - |  - |  - |  - |  - |
 * |       9 |     9 |      11 |   tab |  - |  - |  - |  - |  - |
 * |   10-13 |   A-D |   12-15 |    ws |  - |  - |  - |  - |  - |
 * |   14-31 |  E-1F |   16-37 |   cc2 |  - |  - |  - |  - |  - |
 * |      32 |    20 |      40 |   spc |  - |  - |  - |  - |  - |
 * |   33-47 | 21-2F |   41-57 |   pn1 |  - |  - |  - |  - |  - |
 * |   48-57 | 30-39 |   60-71 |   num |  - |  - |  - |  X |  X |
 * |   58-64 | 3A-40 |  72-100 |   pn2 |  - |  - |  - |  - |  - |
 * |   65-70 | 41-46 | 101-106 |   ulx |  X |  X |  - |  - |  X |
 * |   71-90 | 47-5A | 107-132 |    ul |  X |  X |  - |  - |  - |
 * |   91-96 | 5B-60 | 133-140 |   pn3 |  - |  - |  - |  - |  - |
 * |  97-102 | 61-66 | 141-146 |   llx |  X |  - |  X |  - |  X |
 * | 103-122 | 67-7A | 147-172 |    ll |  X |  - |  X |  - |  - |
 * | 123-126 | 7B-7E | 173-176 |   pn4 |  - |  - |  - |  - |  - |
 * |     127 |    7F |     177 |    bs |  - |  - |  - |  - |  - |
 * +------------------------------------------------------------+
 *
 * Mapping (bits):
 * 1st  -> iscntrl
 * 2nd  -> isprint
 * 3rd  -> isspace
 * 4th  -> isblank
 * 5th  -> isgraph
 * 6th  -> ispunct
 * 7th  -> isalnum
 * 8th  -> isalpha
 * 9th  -> isupper
 * 10th -> islower
 * 11th -> isdigit
 * 12th -> isxdigit
 */

#define SYMBOL_CNTRL (1 << 0)
#define SYMBOL_PRINT (1 << 1)
#define SYMBOL_SPACE (1 << 2)
#define SYMBOL_BLANK (1 << 3)
#define SYMBOL_GRAPH (1 << 4)
#define SYMBOL_PUNCT (1 << 5)
#define SYMBOL_ALNUM (1 << 6)
#define SYMBOL_ALPHA (1 << 7)
#define SYMBOL_UPPER (1 << 8)
#define SYMBOL_LOWER (1 << 9)
#define SYMBOL_DIGIT (1 << 10)
#define SYMBOL_XDIGIT (1 << 11)

const unsigned short SYMBOL_TABLE[256] = {
  // control codes 1
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,

  // tab
  SYMBOL_CNTRL | SYMBOL_SPACE | SYMBOL_BLANK,

  // whitespaces
  SYMBOL_CNTRL | SYMBOL_SPACE, SYMBOL_CNTRL | SYMBOL_SPACE,
  SYMBOL_CNTRL | SYMBOL_SPACE, SYMBOL_CNTRL | SYMBOL_SPACE,

  // control codes 2
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,
  SYMBOL_CNTRL, SYMBOL_CNTRL, SYMBOL_CNTRL,

  // scape
  SYMBOL_PRINT | SYMBOL_SPACE | SYMBOL_BLANK,

  // punct 1
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,

  // numbers
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_DIGIT | SYMBOL_XDIGIT,

  // punct 2
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,

  // uppercase letters (hex flagged)
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER
      | SYMBOL_XDIGIT,

  // uppercase letters
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_UPPER,

  // punct 3
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,

  // lowercase letters (hex flagged)
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER
      | SYMBOL_XDIGIT,

  // lowercase letters
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_ALNUM | SYMBOL_ALPHA | SYMBOL_LOWER,

  // punct 4
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,
  SYMBOL_PRINT | SYMBOL_GRAPH | SYMBOL_PUNCT,

  // backspace
  SYMBOL_CNTRL,

  // empty (for safe)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int
__kisalnum (char c)
{
  return SYMBOL_TABLE[c] & (1 << 6);
}

int
__kisalpha (char c)
{
  return SYMBOL_TABLE[c] & (1 << 7);
}

int
__kisblank (char c)
{
  return SYMBOL_TABLE[c] & (1 << 3);
}

int
__kiscntrl (char c)
{
  return SYMBOL_TABLE[c] & 1;
}

int
__kisdigit (char c)
{
  return SYMBOL_TABLE[c] & (1 << 10);
}

int
__kisgraph (char c)
{
  return SYMBOL_TABLE[c] & (1 << 4);
}

int
__kislower (char c)
{
  return SYMBOL_TABLE[c] & (1 << 9);
}

int
__kisprint (char c)
{
  return SYMBOL_TABLE[c] & (1 << 1);
}

int
__kispunct (char c)
{
  return SYMBOL_TABLE[c] & (1 << 5);
}

int
__kisspace (char c)
{
  return SYMBOL_TABLE[c] & (1 << 2);
}

int
__kisupper (char c)
{
  return SYMBOL_TABLE[c] & (1 << 8);
}

int
__kisxdigit (char c)
{
  return SYMBOL_TABLE[c] & (1 << 11);
}

char
__ktoupper (char c)
{
  return __kisalpha (c) > 0 ? c & ~0x20 : c;
}

char
__ktolower (char c)
{
  return __kisalpha (c) > 0 ? c | 0x20 : c;
}

char
__ktoggle (char c)
{
  return __kisalpha (c) > 0 ? c ^ 0x20 : c;
}
