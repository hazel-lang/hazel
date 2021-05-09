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

#include <Hazel/Compiler/Tokens/Tokens.h>

// Token constructor
Token* token_init() {
    Token* token = calloc(1, sizeof(Token));
    token->type__ = TOK_ILLEGAL; 
    token->offset__ = 0; 
    token->tok_bytes__ = 0; 
    token->tok_length__ = 0; 
    token->value__ = "";
    token_location_init(token);

    return token;
}

// Initialize/Reset a token's location
void token_location_init(Token* token) {
    token->location__.lineno__ = 0; 
    token->location__.colno__ = 0; 
    token->location__.fname__ = "";
}

// Make a token from a TokenType
// Note: This is not recommended because the rest of the Token fields are populated with default 
// values only
Token* token_from_tok_type(const TokenType __tok_type) {
    Token* token = token_init();
    token->type__ = __tok_type;
    return token;
}

Token* token_make_illegal_tok() {
    return token_init();
}

// Construct an EOF token
Token* token_make_eof_tok() {
    Token* token = token_init();
    token->type__ = TOK_EOF;
    return token;
}

// Clone a Token
Token* token_clone(Token* other) {
    Token* token = token_init();
    token->type__ = other->type__; 
    token->offset__ = other->offset__; 
    token->tok_bytes__ = other->tok_bytes__; 
    token->tok_length__ = other->tok_length__; 
    token->value__ = other->value__;
    token->location__ = other->location__;
    return token;
}

// Get token type 
TokenType token_get_tok_type(Token token) { return token.type__; }
// Returns the location of the token
Location token_location(Token token) { return token.location__; }
// Get the token value 
const char* value(Token token) { return token.value__; }
// Reset a Token instance
void token_reset_token(Token* token) {
    token->type__ = TOK_ILLEGAL; 
    token->offset__ = 0; 
    token->tok_bytes__ = 0; 
    token->tok_length__ = 0; 
    token->value__ = "";
    token_location_init(token);
}


// Convert a Token to its respective String representation
const char* token_toString(Token* token) {
    switch(token->type__) {
        // Special (internal usage only)
        case TOK_EOF: return "TOK_EOF";
        case TOK_NULL: return "TOK_NULL";
        case TOK_ILLEGAL: return "ILLEGAL";
        case COMMENT: return "COMMENT";

        // Literals
        case IDENTIFIER: return "IDENTIFIER";
        case INTEGER: return "INTEGER";
        case BIN_INT: return "BIN_INT";
        case HEX_INT: return "HEX_INT";        
        case INT8_LIT: return "INT8_LIT";       
        case INT16_LIT: return "INT16_LIT";      
        case INT32_LIT: return "INT32_LIT";      
        case INT64_LIT: return "INT64_LIT";      
        case UINT_LIT: return "UINT_LIT";       
        case UINT8_LIT: return "UINT8_LIT";      
        case UINT16_LIT: return "UINT16_LIT";     
        case UINT32_LIT: return "UINT32_LIT";     
        case UINT64_LIT: return "UINT64_LIT";     
        case FLOAT: return "FLOAT";          
        case FLOAT32_LIT: return "FLOAT32_LIT";    
        case FLOAT64_LIT: return "FLOAT64_LIT";    
        case FLOAT128_LIT: return "FLOAT128_LIT";  
        case IMAG: return "IMAG";         
        case RUNE: return "RUNE";         
        case STRING: return "STRING";       
        case RAW_STRING: return "RAW_STRING";   
        case TRIPLE_STRING: return "TRIPLE_STRING"; 
        case TOK_TRUE: return "TRUE";
        case TOK_FALSE: return "FALSE";

        // Operators 
        case PLUS: return "+";
        case MINUS: return "-";
        case MULT: return "*";
        case SLASH: return "/";
        case MOD: return "%";
        case MOD_MOD: return "%%";
        case PLUS_PLUS: return "++";
        case MINUS_MINUS: return "--";
        case AT_SIGN: return "@";
        case HASH_SIGN: return "#";
        case QUESTION: return "?";

        // Comparison Operators
        case GREATER_THAN: return ">";
        case LESS_THAN: return "<";
        case GREATER_THAN_OR_EQUAL_TO: return ">=";
        case LESS_THAN_OR_EQUAL_TO: return "<=";
        case EQUALS_EQUALS: return "==";
        case EXCLAMATION_EQUALS: return "!=";

        // Assignment Operators
        case EQUALS: return "=";
        case PLUS_EQUALS: return "+=";
        case MINUS_EQUALS: return "-=";
        case MULT_EQUALS: return "*=";
        case SLASH_EQUALS: return "/=";
        case MOD_EQUALS: return "%=";
        case AND_EQUALS: return "&=";
        case OR_EQUALS: return "|=";
        case XOR_EQUALS: return "^=";
        case LBITSHIFT_EQUALS: return "<<=";
        case RBITSHIFT_EQUALS: return ">>=";
        case TILDA: return "~";

        // Arrows
        case EQUALS_ARROW: return "=>";
        case RARROW: return "->";
        case LARROW: return "<-";

        // Delimiters
        case LSQUAREBRACK: return "[";
        case RSQUAREBRACK: return "]";
        case LBRACE: return "{";
        case RBRACE: return "}";
        case LPAREN: return "(";
        case RPAREN: return ")";

        // Bitwise
        case LBITSHIFT: return "<<";
        case RBITSHIFT: return ">>";
        case AND: return "&";
        case OR: return "|";
        case EXCLAMATION: return "!";
        case XOR: return "^";
        case AND_NOT: return "&^";
        case AND_AND: return "&&";
        case OR_OR: return "||";

        // Separators
        case COLON: return ":";  
        case SEMICOLON: return ";";  
        case COMMA: return ":";  
        case DOT: return ".";  
        case DDOT: return ".."; 
        case ELLIPSIS: return "...";
        case BACKSLASH: return "\\"; 

        // Keywords
        case ANY: return "any";      
        case AS: return "as";      
        case BEGIN: return "begin";   
        case BREAK: return "break";   
        case CASE: return "case";    
        case CAST: return "cast";    
        case CATCH: return "catch";   
        case CLASS: return "class";   
        case CONST: return "const";   
        case CONTINUE: return "continue";
        case DO: return "do";      
        case DECL: return "decl"; 
        case DEFAULT: return "default"; 
        case ENUM: return "enum";    
        case ELSE: return "else";    
        case ELSEIF: return "elseif";  
        case EXCEPT: return "except";  
        case EXPORT: return "export";  
        case EXTERN: return "inline";  
        case FINALLY: return "finally"; 
        case FOR: return "for";     
        case FROM: return "from";     
        case FUNC: return "func";    
        case IF: return "if";      
        case IMPORT: return "import";  
        case IN: return "in";      
        case INCLUDE: return "include"; 
        case INLINE: return "inline";  
        case ISA: return "isa";     
        case MACRO: return "macro";   
        case MAP: return "map";     
        case MATCH: return "match"; 
        case MIXIN: return "mixin"; 
        case MODULE: return "module";  
        case MUTABLE: return "mutable"; 
        case NO_INLINE: return "noinline"; 
        case NOT: return "not";  
        case NOT_IN: return "notin";  
        case RAISE: return "raise";   
        case RANGE: return "range";   
        case RETURN: return "return";  
        case STRUCT: return "struct";  
        case TRY: return "try";     
        case TUPLE: return "tuple";     
        case TYPE: return "type";     
        case TYPEOF: return "typeof";  
        case WHEN: return "when";    
        case WHERE: return "where";   
        case WHILE: return "while";   
        case UNION: return "union";  
        // We should _never_ reach here
        default: return "ILLEGAL";
    }
}

inline bool token_isJumpStatement(Token* token) {
	// Break (BREAK)
	// Continue (CONTINUE)
	// Return (RETURN)
	return (token->type__ == BREAK || token->type__ == CONTINUE || token->type__ == RETURN); 
} 

inline bool token_isLoopStatement(Token* token) {
	// While (WHILE)
	// For (FOR)
	return (token->type__ == WHILE || token->type__ == FOR); 
} 

inline bool token_isFlowStatement(Token* token) {
	// If 
	// Match 
	return (token->type__ == IF || token->type__ == MATCH); 
} 

inline bool token_isMatchStatement(Token* token) {
	// Declarations used in match-case 
	return (token->type__ == MATCH || token->type__ == CASE || token->type__ == DEFAULT); 
} 

inline bool token_isExpressionStatement(Token* token) {
	// Postfix Operations: isPrimaryExpressionStatement or module (for files)
	// Unary Ops: PLUS, MINUS, EXCLAMATION, NOT
	// RAISE 
	return (token_isPrimaryExpressionStatement(token) || token->type__ == MODULE || token->type__ == PLUS || 
            token->type__ == MINUS || token->type__ == EXCLAMATION || token->type__ == NOT || token->type__ == RAISE); 
} 

inline bool token_isPrimaryExpressionStatement(Token* token) {
	// Literals (numbers, Strings)
	// inline booletoken_ans (TRUE, FALSE)
	// IDENTIFIER
	// 'null' 
	// FUNC
	// ILLEGAL
	// '(' expression ')'
	return (token->type__ == INTEGER || token->type__ == BIN_INT || token->type__ == HEX_INT || token->type__ == IMAG || 
			token->type__ == FLOAT || token->type__ == RUNE || token->type__ == STRING || token->type__ == IDENTIFIER || 
			token->type__ == TOK_NULL || token->type__ == FUNC || token->type__ == TOK_ILLEGAL || token->type__ == LPAREN || 
			token->type__ == RPAREN); 
} 

inline bool token_isDeclStatement(Token* token) {
	// Variable Declaration (with types + "Any") 
	// Function Declaration (FUNC)
	// Class/Struct Declaration (CLASS and STRUCT)
	// Enum Declaration (ENUM)
	// Module Declaration (MODULE)
	// Empty Declaration (SEMICOLON)
	return (token->type__ == ANY || token->type__ == FUNC || token->type__ == CLASS || token->type__ == STRUCT || 
			token->type__ == ENUM || token->type__ == MODULE || token->type__ == SEMICOLON); 
} 


inline bool token_isSpecial(Token* token) {
	return (token->type__ == TOK_ID || token->type__ == TOK_EOF || token->type__ == TOK_ILLEGAL || token->type__ == COMMENT); 
}

inline bool token_isLiteral(Token* token) {
	return token->type__ > TOK___LITERALS_BEGIN && token->type__ < TOK___LITERALS_END; 
}

inline bool token_isKeyword(Token* token) {
	return token->type__ > TOK___KEYWORDS_BEGIN && token->type__ < TOK___KEYWORDS_END; 
}

inline bool token_isOperator(Token* token) {
	return token->type__ > TOK___OPERATORS_BEGIN && token->type__ < TOK___OPERATORS_END; 
}

inline bool token_isComparisonOperator(Token* token) {
	return token->type__ > TOK___COMP_OPERATORS_BEGIN && token->type__ < TOK___COMP_OPERATORS_END; 
}

inline bool token_isAssignmentOperator(Token* token) {
	return token->type__ > TOK___ASSIGNMENT_OPERATORS_BEGIN && token->type__ < TOK___ASSIGNMENT_OPERATORS_END; 
}

inline bool token_isDelimiter(Token* token) {
	return token->type__ > TOK___DELIMITERS_OPERATORS_BEGIN && token->type__ < TOK___DELIMITERS_OPERATORS_END;
}

inline bool token_isArrow(Token* token) {
	return token->type__ > TOK___ARROW_OPERATORS_BEGIN && token->type__ < TOK___ARROW_OPERATORS_END;
}

inline bool token_isBitwise(Token* token) {
	return token->type__ > TOK___BITWISE_OPERATORS_BEGIN && token->type__ < TOK___BITWISE_OPERATORS_END;
}

inline bool token_isSeparator(Token* token) {
	return token->type__ > TOK___SEPARATORS_BEGIN && token->type__ < TOK___SEPARATORS_END;
}

inline bool token_isIdentifier(Token* token) {
	return token->type__ == IDENTIFIER; 
}

inline bool token_isEOF(Token* token) {
	return token->type__ == TOK_EOF; 
}

inline bool token_isNULL(Token* token) {
	return token->type__ == TOK_NULL; 
}

inline bool token_isIllegal(Token* token) {
	return token->type__ == TOK_ILLEGAL; 
}

inline bool token_isMacro(Token* token) {
	return token->type__ == MACRO; 
}

inline bool token_isImport(Token* token) {
	return token->type__ == IMPORT; 
}

inline bool token_isInclude(Token* token) {
	return token->type__ == INCLUDE; 
}

inline bool token_isSemiColon(Token* token) {
	return token->type__ == SEMICOLON; 
}
