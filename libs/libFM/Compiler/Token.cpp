/*
 * Copyright (c) 2009 Samit Basu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "Token.hpp"
#include <errno.h>
#include <limits.h>

using namespace FM;

Token::Token(TokenValueType tok, unsigned pos, FMString text) :
  m_tok(tok), m_pos(pos), m_text(text) { }

Token::Token() {
  m_tok = TOK_INVALID;
}

bool Token::isBinaryOperator() const {
  return ((m_tok == '+') || (m_tok == '-') ||
	  (m_tok == '*') || (m_tok == '/') ||
	  (m_tok == '\\') || (m_tok == '^') ||
	  (m_tok == '>') || (m_tok == '<') || 
	  (m_tok == ':') || (m_tok == TOK_LE) ||
	  (m_tok == TOK_GE) || (m_tok == TOK_EQ) ||
	  (m_tok == TOK_NE) || (m_tok == TOK_SOR) ||
	  (m_tok == TOK_SAND) || (m_tok == TOK_DOTTIMES) ||
	  (m_tok == TOK_DOTRDIV) || (m_tok == TOK_DOTLDIV) ||
	  (m_tok == TOK_DOTPOWER) || (m_tok == '|') ||
	  (m_tok == '&'));
}

bool Token::isUnaryOperator() const {
  return ((m_tok == '+') || (m_tok == '-') || (m_tok == '~')
	  || (m_tok == TOK_UNARY_MINUS) || 
	  (m_tok == TOK_UNARY_PLUS) ||
	  (m_tok == TOK_INCR) ||
	  (m_tok == TOK_DECR) ||
	  (m_tok == '?'));
}


bool Token::isRightAssociative() const {
  return (m_tok == '^');
}

//FMTextStream& operator<<(FMTextStream& o, const Token& b) {
//  o << TokenToString(b) << " (" << (b.position() >> 16)
//    << "," << (b.position() & 0xffff) << ")\r\n";
//  return o;
//}

std::ostream& operator<<(std::ostream& o, const Token& b) {
  o << FM::TokenToString(b) << " (" << (b.position() >> 16)
    << "," << (LineNumber(b.position())) << ")\n";
  return o;
}


FMString FM::TokenToString(const Token& b) {
  switch(b.value()) {
  case TOK_IDENT: return "'"+b.text()+"'";
  case TOK_SCOPED_IDENT: return ":"+b.text()+":";
  case TOK_SPACE: return "space";
  case TOK_STRING: return "\""+b.text()+"\"";
  case TOK_KEYWORD: return "keyword";
  case TOK_BREAK: return "break";
  case TOK_CASE: return "case";
  case TOK_CATCH: return "catch";
  case TOK_CONTINUE: return "continue";
  case TOK_ELSE: return "else";
  case TOK_ELSEIF: return "elseif";
  case TOK_END: return "end";
  case TOK_FOR: return "for";
  case TOK_FUNCTION: return "function";
  case TOK_GLOBAL: return "global";
  case TOK_IF: return "if";
  case TOK_KEYBOARD: return "keyboard";
  case TOK_OTHERWISE: return "otherwise";
  case TOK_PERSISTENT: return "persistent";
  case TOK_QUIT: return "quit";
  case TOK_RETALL: return "retall";
  case TOK_RETURN: return "return";
  case TOK_SWITCH: return "switch";
  case TOK_TRY: return "try";
  case TOK_WHILE: return "while";
    // Generated (synthetic) token;
  case TOK_MULTI: return "multi";
  case TOK_SPECIAL: return "special";
  case TOK_VARIABLE: return "variable";
  case TOK_DYN: return "dyn";
  case TOK_BLOCK: return "block";
  case TOK_EOF: return "eof";
  case TOK_MATDEF: return "matdef";
  case TOK_CELLDEF: return "celldef";
  case TOK_PARENS: return "()";
  case TOK_BRACES: return "{}";
  case TOK_BRACKETS: return "[]";
  case TOK_ROWDEF: return "row";
  case TOK_UNARY_MINUS: return "u-";
  case TOK_UNARY_PLUS: return "u+";
  case TOK_EXPR: return "expr";
  case TOK_DOTTIMES: return ".*";
  case TOK_DOTRDIV: return "./";
  case TOK_DOTLDIV: return ".\\";
  case TOK_DOTPOWER: return ".^";
  case TOK_DOTTRANSPOSE: return ".'";
  case TOK_LE: return "<=";
  case TOK_GE: return ">=";
  case TOK_EQ: return "==";
  case TOK_NE: return "~=";
  case TOK_SOR: return "||";
  case TOK_SAND: return "&&";
  case TOK_QSTATEMENT: return "qstmnt";
  case TOK_STATEMENT: return "stmnt";
  case TOK_REALF: return "(real single)" + b.text();
  case TOK_IMAGF: return "(imag single)" + b.text();
  case TOK_REAL: return "(real)" + b.text();
  case TOK_IMAG: return "(imag)" + b.text();
  case TOK_FUNCTION_DEFS: return "functions:";
  case TOK_SCRIPT: return "script:";
  case TOK_ANONYMOUS_FUNC: return "anon func";
  case TOK_NEST_FUNC: return "nest func";
  case TOK_TYPE_DECL: return "type decl";
  case TOK_REINDEX: return "reindex";
  case TOK_INCR: return "++";
  case TOK_DECR: return "--";
  case TOK_INCR_PREFIX: return "++(pre)";
  case TOK_DECR_PREFIX: return "--(pre)";
  case TOK_INCR_POSTFIX: return "++(post)";
  case TOK_DECR_POSTFIX: return "--(post)";
  case TOK_PLUS_EQ: return "+=";
  case TOK_MINUS_EQ: return "-=";
  case TOK_AND_EQ: return "&=";
  case TOK_OR_EQ: return "|=";
  case TOK_TIMES_EQ: return "*=";
  case TOK_DOTTIMES_EQ: return ".*=";
  case TOK_CLASSDEF: return "classdef";
  case TOK_PROPERTIES: return "properties";
  case TOK_METHODS: return "methods";
  case TOK_THROW: return "throw";
  case TOK_ATTRIBUTES: return "attributes";
  case TOK_GET_METHOD: return "get_method";
  case TOK_EVENTS: return "events";
  }
  return FMString(1,FMChar(b.value()));
}

