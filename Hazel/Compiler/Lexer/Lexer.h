/*
_ _    _           ______   _______        
| |  | |    /\    /___  /   |  ____|| |    
| |__| |   /  \      / /    | |__   | |       Hazel - The Fast, Expressive & Elegant Programming Language
|  __  |  / /\ \    / /     |  __|  | |       Languages: C, C++, and Assembly
| |  | | / ____ \  / /___   | |____ | |____   https://github.com/HazelLang/Hazel/
|_|_ |_|/_/    \_\/_______\ |______|_\______|

Licensed under the MIT License <http://opensource.org/licenses/MIT>
SPDX-License-Identifier: MIT
Copyright (c) 2021 Jason Dsouza <http://github.com/jasmcaus>
*/
#ifndef _HAZEL_LEXER
#define _HAZEL_LEXER 

#include <string>
#include <Hazel/Compiler/Lexer/Lexer.h>
#include <Hazel/Core/HCore.h> 
#include <Hazel/Compiler/Tokens/Tokens.h>

/*
    Hazel's Lexer is built in such a way that no (or negligible) memory allocations are necessary during usage. 

    In order to be able to not allocate any memory during tokenization, STRINGs and NUMBERs are just sanity checked but _not_
    converted - it is the responsibility of the Parser to perform the right conversion.

    In case of a scan error, ILLEGAL is returned and the error details can be extracted from the token itself.

    Reference: 
        1. ASCII Table: http://www.theasciicode.com.ar 
*/
class Lexer {
public:
    // Default constructor 
    Lexer() {
        this->buffer = ""; 
        this->buffer_capacity = -1;
        this->offset = 0; 
        this->col_no = 0; 
        this->line_no = 0; 
        this->fname = ""; 
    }

    // Constructor 
    Lexer(std::string buffer, std::string fname) {
        this->buffer = buffer; 
        this->buffer_capacity = buffer.length();
        this->offset = 0; 
        this->col_no = 0; 
        this->line_no = 0; 
        this->fname = fname; 
    }

    // Lexer next() increments the buffer offset and essentially _advances_ to the next element in the buffer
    inline char next() {
        ++this->col_no;
        return (char)this->buffer[this->offset++];
    }

    // Lexer peek() allows you to "look ahead" `n` characters in the Lexical buffer
    // It _does not_ increment the buffer offset 
    inline char peek(int n) {
        if(this->offset + (n-1) < this->buffer_capacity) {
            return (char)this->buffer[this->offset + n];
        } else {
            return 0;
        }
    }

    // Lexer peek_curr() returns the current element in the Lexical Buffer
    inline char peek_curr() {
        return (char)this->buffer[this->offset];
    }

    // Check if the current Lexer state is at EOF
    inline bool is_EOF() {
        return this->offset >= this->buffer_capacity;
    }

    // Reset the line
    inline void reset_line() {
        this->line_no = 0;
    }

    // Reset the column number 
    inline void reset_column() {
        this->col_no = 0; 
    }

    // Reset a Lexer Token
    inline void reset_token() {
        this->token = Token();
        // TODO(jasmcaus): Verify this is accurate
        this->token.value = this->buffer[this->offset]; 
        this->token.line_no = this->line_no;
        this->token.col_no = this->col_no;
    }

    // Finalize a Token
    inline void finalize_token(TokenType __tok) {
        this->token.type = __tok; 
        this->token.fname = this->fname;
    }

    // Increment Token Bytes
    inline void increment_tok_bytes() {
        ++this->token.tok_bytes;
    }

    // Decrement Token Bytes
    inline void decrement_tok_bytes() {
        --this->token.tok_bytes;
    }

    // Increment Token Length
    inline void increment_tok_length() {
        ++this->token.tok_length;
    }

    // Decrement Token Length
    inline void decrement_tok_length() {
        --this->token.tok_length;
    }

    // Increment the line number
    inline void increment_line() {
        ++this->line_no; 
        this->reset_column();
    }

    // Decrement the line_no
    inline void decrement_line() {
        --this->line_no; 
        this->reset_column();
    }

    // Increment the column number
    inline void increment_column() {
        ++this->col_no; 
    }

    // Decrement the col_no
    inline void decrement_column() {
        --this->col_no; 
    }

    // Increment the Lexical Buffer offset
    inline void increment_offset() {
        ++this->offset; 
        this->increment_column();
    }

    // Decrement the Lexical Buffer offset
    inline void decrement_offset() {
        --this->offset; 
        this->decrement_column();
    }


protected:
    std::string buffer;           // the Lexical buffer
    UInt32 position;        // current buffer position (in characters)
    UInt32 buffer_capacity; // current buffer capacity (in Bytes)
    UInt32 offset;          // current buffer offset (in Bytes) 
                            // offset of the beginning of the line (no. of chars b/w the beginning of the Lexical Buffer
                            // and the beginning of the line)
                            // Sometimes called the buffer position

    Token token;            // current token
    // UInt32 char_idx;        // the index of the token
    UInt32 line_no;         // the line number in the source where the token occured
    UInt32 col_no;          // the column number
    std::string fname;            // the file name
}; // class Lexer



Token* lexer_get_next_token(Lexer* lexer); 
Token* lexer_advance_with_token(Lexer* lexer, int type); 

Lexer* lexer_init(const char* buffer, char* fname);
void lexer_advance(Lexer* lexer); 
void lexer_expect_char(Lexer* lexer, char c);
void lexer_skip_whitespace(Lexer* lexer); 
void lexer_skip_inline_comment(Lexer* lexer);
void lexer_skip_block_comment(Lexer* lexer);

Token* lexer_lex_string(Lexer* lexer); 
Token* lexer_lex_operator(Lexer* lexer);
Token* lexer_lex_separator(Lexer* lexer);
Token* lexer_lex_delimiter(Lexer* lexer);
Token* lexer_lex_macro(Lexer* lexer);
Token* lexer_lex_keywords(Lexer* lexer);
Token* lexer_lex_char(Lexer* lexer); 
Token* lexer_lex_digit(Lexer* lexer); 
Token* lexer_lex_token_id(Lexer* lexer); 

char* lexer_lex_charstr(Lexer* lexer);

static inline bool isBuiltinOperator(char c);
static inline bool isIdentifier(char c);
static inline bool isNewLine(Lexer* lexer, char c);
static inline bool isSlashComment(char c1, char c2);
static inline bool isHashComment(char c);
static inline bool isComment(char c1, char c2);
static inline bool isSemicolon(char c);
static inline bool isString(char c);
static inline bool isMacro(char c);


#endif // _HAZEL_LEXER