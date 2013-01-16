/* This file is part of the 'stringi' library.
 * 
 * Copyright 2013 Marek Gagolewski, Bartek Tartanus, Marcin Bujarski
 * 
 * 'stringi' is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 'stringi' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'stringi'. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "stringi.h"


/** get char types for each code point UTF-8 string
 * @param s UTF-8 encoded string
 * @param n number of bytes
 * @param codes [OUT] the char types/codes; array of length >= n
 * @param ncodes [OUT] number of code points found
 */
void stri__uchar_charType(const char* s, int n, int* codes, int& ncodes)
{
   UChar32 c;
   ncodes=0;
   for (int i=0; i<n; ) {
      U8_NEXT(s, i, n, c);
      codes[ncodes++] =  u_charType(c);
   }
}


/** Get character types
 * @param s character vector
 * @return list of integer vectors
 * @TODO other encodings..................
 */
SEXP stri_chartype(SEXP s)
{
   s = stri_prepare_arg_string(s);
   R_len_t ns = LENGTH(s);
   if (ns <= 0) return R_NilValue;
   
   R_len_t bufsize = stri__numbytes_max(s);
   int* buf = 0;
   if (bufsize > 0) buf = new int[bufsize];
   
   SEXP ret;
   PROTECT(ret = allocVector(VECSXP, ns));
   for (R_len_t i=0; i<ns; ++i) {
      SEXP ns = STRING_ELT(s, i);
      if (ns == NA_STRING)
         SET_VECTOR_ELT(ret, i, ScalarInteger(NA_INTEGER)); // hmmmm..... integer(0)?
      else {
         R_len_t cns = LENGTH(ns);
         int ncodes;
         stri__uchar_charType(CHAR(ns), cns, buf, ncodes);
         SEXP codes;
         PROTECT(codes = allocVector(INTSXP, ncodes));
         int* int_codes = INTEGER(codes);
         for (int j=0; j<ncodes; ++j)
            int_codes[j] = buf[j];
         UNPROTECT(1);
         SET_VECTOR_ELT(ret, i, codes);
      }
   }
   if (buf) delete [] buf;
   UNPROTECT(1);
   return ret;
}


/** Get character categories
 * Based on ICU4C/uchar.h
 * U_UNASSIGNED (id=0) is omitted
 * @return list of 3 vectors (integer, character, character)
 */
SEXP stri_charcategories()
{

   
   
   
   
   
 
   const R_len_t numcolumns = 3;
   const R_len_t numcategories = U_CHAR_CATEGORY_COUNT-1;
   SEXP vals;
   SEXP names;
   PROTECT(names = allocVector(STRSXP, numcolumns));
   SET_STRING_ELT(names, 0, mkChar("Identifier"));
   SET_STRING_ELT(names, 1, mkChar("CategoryFull"));
   SET_STRING_ELT(names, 2, mkChar("Category"));
   
   SEXP id;
   SEXP cat;
   SEXP cat2;
   PROTECT(id   = allocVector(INTSXP, numcategories));
   PROTECT(cat  = allocVector(STRSXP, numcategories));
   PROTECT(cat2 = allocVector(STRSXP, numcategories));
   
#define STRI_CHARCATEGORIES_CREATE(x, y, z) \
   INTEGER(id)[x-1] = x; \
   SET_STRING_ELT(cat,  x-1, mkChar(y)); \
   SET_STRING_ELT(cat2, x-1, mkChar(z)); \

  
//STRI_CHARCATEGORIES_CREATE( U_UNASSIGNED,             "U_UNASSIGNED",               "Cn" )
STRI_CHARCATEGORIES_CREATE( U_UPPERCASE_LETTER,       "U_UPPERCASE_LETTER",         "Lu" )
STRI_CHARCATEGORIES_CREATE( U_LOWERCASE_LETTER,       "U_LOWERCASE_LETTER",         "Ll" )
STRI_CHARCATEGORIES_CREATE( U_TITLECASE_LETTER,       "U_TITLECASE_LETTER",         "Lt" )
STRI_CHARCATEGORIES_CREATE( U_MODIFIER_LETTER,        "U_MODIFIER_LETTER",          "Lm" )
STRI_CHARCATEGORIES_CREATE( U_OTHER_LETTER,           "U_OTHER_LETTER",             "Lo" )
STRI_CHARCATEGORIES_CREATE( U_NON_SPACING_MARK,       "U_NON_SPACING_MARK",         "Mn" )        
STRI_CHARCATEGORIES_CREATE( U_ENCLOSING_MARK,         "U_ENCLOSING_MARK",           "Me" )
STRI_CHARCATEGORIES_CREATE( U_COMBINING_SPACING_MARK, "U_COMBINING_SPACING_MARK",   "Mc" )
STRI_CHARCATEGORIES_CREATE( U_DECIMAL_DIGIT_NUMBER,   "U_DECIMAL_DIGIT_NUMBER",     "Nd" )
STRI_CHARCATEGORIES_CREATE( U_LETTER_NUMBER,          "U_LETTER_NUMBER",            "Nl" )
STRI_CHARCATEGORIES_CREATE( U_OTHER_NUMBER,           "U_OTHER_NUMBER",             "No" )
STRI_CHARCATEGORIES_CREATE( U_SPACE_SEPARATOR,        "U_SPACE_SEPARATOR",          "Zs" )
STRI_CHARCATEGORIES_CREATE( U_LINE_SEPARATOR,         "U_LINE_SEPARATOR",           "Zl" )
STRI_CHARCATEGORIES_CREATE( U_PARAGRAPH_SEPARATOR,    "U_PARAGRAPH_SEPARATOR",      "Zp" )
STRI_CHARCATEGORIES_CREATE( U_CONTROL_CHAR,           "U_CONTROL_CHAR",             "Cc" )
STRI_CHARCATEGORIES_CREATE( U_FORMAT_CHAR,            "U_FORMAT_CHAR",              "Cf" )
STRI_CHARCATEGORIES_CREATE( U_PRIVATE_USE_CHAR,       "U_PRIVATE_USE_CHAR",         "Co" )
STRI_CHARCATEGORIES_CREATE( U_SURROGATE,              "U_SURROGATE",                "Cs" )
STRI_CHARCATEGORIES_CREATE( U_DASH_PUNCTUATION,       "U_DASH_PUNCTUATION",         "Pd" )
STRI_CHARCATEGORIES_CREATE( U_START_PUNCTUATION,      "U_START_PUNCTUATION",        "Ps" )
STRI_CHARCATEGORIES_CREATE( U_END_PUNCTUATION,        "U_END_PUNCTUATION",          "Pe" )
STRI_CHARCATEGORIES_CREATE( U_CONNECTOR_PUNCTUATION,  "U_CONNECTOR_PUNCTUATION",    "Pc" )
STRI_CHARCATEGORIES_CREATE( U_OTHER_PUNCTUATION,      "U_OTHER_PUNCTUATION",        "Po" )
STRI_CHARCATEGORIES_CREATE( U_MATH_SYMBOL,            "U_MATH_SYMBOL",              "Sm" )
STRI_CHARCATEGORIES_CREATE( U_CURRENCY_SYMBOL,        "U_CURRENCY_SYMBOL",          "Sc" )
STRI_CHARCATEGORIES_CREATE( U_MODIFIER_SYMBOL,        "U_MODIFIER_SYMBOL",          "Sk" )
STRI_CHARCATEGORIES_CREATE( U_OTHER_SYMBOL,           "U_OTHER_SYMBOL",             "So" )
STRI_CHARCATEGORIES_CREATE( U_INITIAL_PUNCTUATION,    "U_INITIAL_PUNCTUATION",      "Pi" )
STRI_CHARCATEGORIES_CREATE( U_FINAL_PUNCTUATION,      "U_FINAL_PUNCTUATION",        "Pf" )

   PROTECT(vals = allocVector(VECSXP, numcolumns));
   SET_VECTOR_ELT(vals, 0, id);
   SET_VECTOR_ELT(vals, 1, cat);
   SET_VECTOR_ELT(vals, 2, cat2);
   
   setAttrib(vals, R_NamesSymbol, names);
   UNPROTECT(5);
   return vals;
}
