/*
 *  Edmund Mergl <E.Mergl@bawue.de>
 *
 *  $Id$
 *
 */


#include <ctype.h>
#include "postgres.h"


text *lower(text *string);
text *upper(text *string);
text *initcap(text *string);
text *lpad(text *string1, int4 len, text *string2);
text *rpad(text *string1, int4 len, text *string2);
text *ltrim(text *string, text *set);
text *rtrim(text *string, text *set);
text *substr(text *string, int4 m, int4 n);
text *translate(text *string, char from, char to);


/********************************************************************
 *
 * lower
 *
 * Syntax:
 *
 *   text *lower(text *string)
 *
 * Purpose:
 *
 *   Returns string, with all letters forced to lowercase.
 *
 ********************************************************************/

text *
lower(text *string)
{
  text *ret;
  char *ptr, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0) {
    return string;
  }

  ret = (text *)palloc(VARSIZE(string));
  VARSIZE(ret) = VARSIZE(string);

  ptr     = VARDATA(string);
  ptr_ret = VARDATA(ret);

  while (m--) {
    *ptr_ret++ = tolower(*ptr++);
  }

  return ret;
}


/********************************************************************
 *
 * upper
 *
 * Syntax:
 *
 *   text *upper(text *string)
 *
 * Purpose:
 *
 *   Returns string, with all letters forced to uppercase.
 *
 ********************************************************************/

text *
upper(text *string)
{
  text *ret;
  char *ptr, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0) {
    return string;
  }

  ret = (text *)palloc(VARSIZE(string));
  VARSIZE(ret) = VARSIZE(string);

  ptr     = VARDATA(string);
  ptr_ret = VARDATA(ret);

  while (m--) {
    *ptr_ret++ = toupper(*ptr++);
  }

  return ret;
}


/********************************************************************
 *
 * initcap
 *
 * Syntax:
 *
 *   text *initcap(text *string)
 *
 * Purpose:
 *
 *   Returns string, with first letter of each word in uppercase,
 *   all other letters in lowercase. A word is delimited by white
 *   space.
 *
 ********************************************************************/

text *
initcap(text *string)
{
  text *ret;
  char *ptr, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0) {
    return string;
  }

  ret = (text *)palloc(VARSIZE(string));
  VARSIZE(ret) = VARSIZE(string);

  ptr  = VARDATA(string);
  ptr_ret = VARDATA(ret);

  *ptr_ret++ = toupper(*ptr++);
  --m;

  while (m--) {
    if (*(ptr_ret - 1) == ' ' || *(ptr_ret - 1) == '	') {
      *ptr_ret++ = toupper(*ptr++);
    } else {
      *ptr_ret++ = tolower(*ptr++);
    }
  }

  return ret;
}


/********************************************************************
 *
 * lpad
 *
 * Syntax:
 *
 *   text *lpad(text *string1, int4 len, text *string2)
 *
 * Purpose:
 *
 *   Returns string1, left-padded to length len with the sequence of
 *   characters in string2.
 *
 ********************************************************************/

text *
lpad(text *string1, int4 len, text *string2)
{
  text *ret;
  char *ptr1, *ptr2, *ptr_ret;
  int m, n;

  m = len - VARSIZE(string1) + VARHDRSZ;

  if (m <= 0 || (VARSIZE(string2) - VARHDRSZ) <= 0) {
    return string1;
  }

  ret = (text *)palloc(VARHDRSZ + len);
  VARSIZE(ret) = VARHDRSZ + len;

  ptr2    = VARDATA(string2);
  ptr_ret = VARDATA(ret);

  while (m--) {
    *ptr_ret++ = *ptr2;
    ptr2 = ptr2 == VARDATA(string2) + VARSIZE(string2) - VARHDRSZ - 1 ? VARDATA(string2) : ++ptr2;
  }

  n    = VARSIZE(string1) - VARHDRSZ;
  ptr1 = VARDATA(string1);

  while (n--) {
    *ptr_ret++ = *ptr1++;
  }

  return ret;
}


/********************************************************************
 *
 * rpad
 *
 * Syntax:
 *
 *   text *rpad(text *string1, int4 len, text *string2)
 *
 * Purpose:
 *
 *   Returns string1, right-padded to length len with the sequence of
 *   characters in string2.
 *
 ********************************************************************/

text *
rpad(text *string1, int4 len, text *string2)
{
  text *ret;
  char *ptr1, *ptr2, *ptr_ret;
  int m, n;

  m = len - VARSIZE(string1) + VARHDRSZ;

  if (m <= 0 || (VARSIZE(string2) - VARHDRSZ) <= 0) {
    return string1;
  }

  ret = (text *)palloc(VARHDRSZ + len);
  VARSIZE(ret) = VARHDRSZ + len;

  n       = VARSIZE(string1) - VARHDRSZ;
  ptr1    = VARDATA(string1);
  ptr_ret = VARDATA(ret);

  while (n--) {
    *ptr_ret++ = *ptr1++;
  }

  ptr2  = VARDATA(string2);

  while (m--) {
    *ptr_ret++ = *ptr2;
    ptr2 = ptr2 == VARDATA(string2) + VARSIZE(string2) - VARHDRSZ - 1 ? VARDATA(string2) : ++ptr2;
  }

  return ret;
}


/********************************************************************
 *
 * ltrim
 *
 * Syntax:
 *
 *   text *ltrim(text *string, text *set)
 *
 * Purpose:
 *
 *   Returns string with initial characters removed up to the first
 *   character not in set.
 *
 ********************************************************************/

text *
ltrim(text *string, text *set)
{
  text *ret;
  char *ptr, *ptr2, *end2, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0 || VARSIZE(set) - VARHDRSZ <= 0) {
    return string;
  }

  ptr  = VARDATA(string);
  ptr2 = VARDATA(set);
  end2 = VARDATA(set) + VARSIZE(set) - VARHDRSZ - 1;
  
  while (m--) {
    while (ptr2 <= end2) {
      if (*ptr == *ptr2) {
        break;
      }
      ++ptr2;
    }
    if (*ptr != *ptr2) {
      break;
    }
    ptr++;
    ptr2 = VARDATA(set);
  }

  ++m;

  ret = (text *)palloc(VARHDRSZ + m);
  VARSIZE(ret) = VARHDRSZ + m;

  ptr_ret = VARDATA(ret);

  while (m--) {
    *ptr_ret++ = *ptr++;
  }

  return ret;
}


/********************************************************************
 *
 * rtrim
 *
 * Syntax:
 *
 *   text *rtrim(text *string, text *set)
 *
 * Purpose:
 *
 *   Returns string with final characters removed after the last
 *   character not in set.
 *
 ********************************************************************/

text *
rtrim(text *string, text *set)
{
  text *ret;
  char *ptr, *ptr2, *end2, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0 || VARSIZE(set) - VARHDRSZ <= 0) {
    return string;
  }

  ptr   = VARDATA(string) + VARSIZE(string) - VARHDRSZ - 1;
  ptr2  = VARDATA(set);
  end2  = VARDATA(set)    + VARSIZE(set)    - VARHDRSZ - 1;
  
  while (m--) {
    while (ptr2 <= end2) {
      if (*ptr == *ptr2) {
        break;
      }
      ++ptr2;
    }
    if (*ptr != *ptr2) {
      break;
    }
    --ptr;
    ptr2 = VARDATA(set);
  }

  ++m;

  ret = (text *)palloc(VARHDRSZ + m);
  VARSIZE(ret) = VARHDRSZ + m;

  ptr_ret = VARDATA(ret) + m - 1;

  while (m--) {
    *ptr_ret-- = *ptr--;
  }

  return ret;
}


/********************************************************************
 *
 * substr
 *
 * Syntax:
 *
 *   text *substr(text *string, int4 m, int4 n)
 *
 * Purpose:
 *
 *   Returns a portion of string, beginning at character m, n
 *   characters long. The first position of string is 1.
 *
 ********************************************************************/

text *
substr(text *string, int4 m, int4 n)
{
  text *ret;
  char *ptr, *ptr_ret;
  int len;

  len = VARSIZE(string) - VARHDRSZ - m;

  if (m <= 0 || n <= 0 || len <= 0) {
    return string;
  }

  len = len + 1 < n ? len + 1 : n;

  ret = (text *)palloc(VARHDRSZ + len);
  VARSIZE(ret) = VARHDRSZ + len;

  ptr     = VARDATA(string) + m - 1;
  ptr_ret = VARDATA(ret);

  while (len--) {
    *ptr_ret++ = *ptr++;
  }

  return ret;
}


/********************************************************************
 *
 * translate
 *
 * Syntax:
 *
 *   text *translate(text *string, char from, char to)
 *
 * Purpose:
 *
 *   Returns string after replacing all occurences of from with
 *   the corresponding character in to. TRANSLATE will not remove
 *    characters.
 *
 ********************************************************************/

text *
translate(text *string, char from, char to)
{
  text *ret;
  char *ptr, *ptr_ret;
  int m;

  m = VARSIZE(string) - VARHDRSZ;

  if (m <= 0) {
    return string;
  }

  ret = (text *)palloc(VARSIZE(string));
  VARSIZE(ret) = VARSIZE(string);

  ptr     = VARDATA(string);
  ptr_ret = VARDATA(ret);

  while (m--) {
    *ptr_ret++ = *ptr == from ? to : *ptr;
    ptr++;
  }

  return ret;
}


/* EOF */
