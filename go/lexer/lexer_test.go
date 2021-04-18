package lexer 

import (
    "testing"
    "go/token"
)

func TestNextToken(t *testing.T) {
    input := `=+(){},;`

    tests := []struct {
        expectedType token.TokenTupe 
        expectedLiteral string
    } {
        {token.ASSIGN, "="},
        {token.PLUS, "+" }, 
        {token.LPAREN, "("},
        {token.RPAREN, ")"}, 
        {token.LBRACE, "{"}, 
        {token.RBRACE, "}"},
        {token.COMMA, "," }, 
        {token.SEMICOLON, ";"},
        {token.EOF, ""},
    }
    
    l := New(input)
    for i, tt := range tests {
        tok := l.NextToken()

        if tok.Type != t.expectedType {
            t.Fatalf("tests[%d] - tokentype wrong. Expected=%q, got=%q"),
            i, tt.expectedType, tok.Type)
        }

		if tok.Literal != t.expectedLiteral {
            t.Fatalf("tests[%d] - Literal wrong. Expected=%q, got=%q"),
            i, tt.Literal, tok.Literal)
        }
  }
}
