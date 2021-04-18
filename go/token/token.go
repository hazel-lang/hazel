package token

type TokenType string

type Token struct {
    Type TokenType 
    Literal string
}

// Constants
const (
    ILLEGAL = "ILLEGAL"
    EOF = "EOF"

    // Identifiers + Literals
    IDENT = "IDENT"
    INT = "INT"

    // Operators
    ASSIGN = "="
    PLUS = "+" 

    // Delimiters
    COMMA = ","
    SEMICOLON = ";"

    LPAREN = "("
    RPAREN = ")"
    LBRACE = "{"
    RBRACE = "}"
    
    // Keywords
    FUNCTION = "FUNCTION"
    LET = "LET"
)
