import { DiagnosticHandler, TextSpan } from "../diagnostic";

class Lexer {
    public readonly diagnosticHandler = new DiagnosticHandler();
    private readonly source: string;
    private pos = 0;

    constructor(source: string) {
        this.source = source;
    }

    private peek(offset: number = 0): string {
        return this.source[this.pos + offset];
    }

    private next(len: number = 1): string {
        if (len === 1) {
            return this.source[this.pos++];
        } else {
            this.pos += len;
            return this.source.substr(this.pos - len, len);
        }
    }

    public lex(): Token[] {
        const tokens = new Array<Token>();

        while (this.pos < this.source.length) {
            switch (this.source[this.pos]) {
                case "(":
                    tokens.push(new Token(TokenType.OpenParenthesis, this.pos, this.next()));
                    break;
                case ")":
                    tokens.push(new Token(TokenType.CloseParenthesis, this.pos, this.next()));
                    break;
                case "?":
                    tokens.push(new Token(TokenType.QuestionMark, this.pos, this.next()));
                    break;
                case ":":
                    tokens.push(new Token(TokenType.Colon, this.pos, this.next()));
                    break;
                case "=":
                    if (this.peek(1) === "=") {
                        tokens.push(new Token(TokenType.DoubleEqual, this.pos, this.next(2)));
                    } else {
                        this.pos++
                    }
                    break;
                case "!":
                    if (this.peek(1) === "=") {
                        tokens.push(new Token(TokenType.BangEqual, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.Bang, this.pos, this.next()));
                    }
                    break;
                case ">":
                    if (this.peek(1) === ">") {
                        if (this.peek(2) === ">") {
                            tokens.push(new Token(TokenType.TripleGreaterThan, this.pos, this.next(3)));
                        } else {
                            tokens.push(new Token(TokenType.DoubleGreaterThan, this.pos, this.next(2)));
                        }
                    } else if (this.peek(1) === "=") {
                        tokens.push(new Token(TokenType.GreaterEqualThan, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.GreaterThan, this.pos, this.next()));
                    }
                    break;
                case "<":
                    if (this.peek(1) === "<") {
                        tokens.push(new Token(TokenType.DoubleLessThan, this.pos, this.next(2)));
                    } else if (this.peek(1) === "=") {
                        if (this.peek(2) === ">") {
                            tokens.push(new Token(TokenType.LessEqualGreater, this.pos, this.next(3)));
                        } else {
                            tokens.push(new Token(TokenType.LessEqualThan, this.pos, this.next(2)));
                        }
                    } else {
                        tokens.push(new Token(TokenType.LessThan, this.pos, this.next()));
                    }
                    break;
                case "&":
                    if (this.peek(1) === "&") {
                        tokens.push(new Token(TokenType.DoubleAmpersand, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.Ampersand, this.pos, this.next()));
                    }
                    break;
                case "^":
                    tokens.push(new Token(TokenType.Caret, this.pos, this.next()));
                    break;
                case "|":
                    if (this.peek(1) === "|") {
                        tokens.push(new Token(TokenType.DoublePipe, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.Pipe, this.pos, this.next()));
                    }
                    break;
                case "~":
                    tokens.push(new Token(TokenType.Tilde, this.pos, this.next()));
                    break;
                case "+":
                    tokens.push(new Token(TokenType.Plus, this.pos, this.next()));
                    break;
                case "-":
                    tokens.push(new Token(TokenType.Minus, this.pos, this.next()));
                    break;
                case "*":
                    if (this.peek(1) === "*") {
                        tokens.push(new Token(TokenType.DoubleStar, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.Star, this.pos, this.next()));
                    }
                    break;
                case "/":
                    if (this.peek(1) === "/") {
                        tokens.push(new Token(TokenType.DoubleSlash, this.pos, this.next(2)));
                    } else {
                        tokens.push(new Token(TokenType.Slash, this.pos, this.next()));
                    }
                    break;
                case "%":
                    tokens.push(new Token(TokenType.Percent, this.pos, this.next()));
                    break;
                case " ":
                case "\t":
                case "\n":
                case "\r":
                    this.next();
                    break;
                default:
                    if (!isNaN(+this.peek())) {
                        const start = this.pos;

                        while (this.peek() && !/\s/.test(this.peek())) this.pos++;

                        const numberLiteral = this.source.substring(start, this.pos);

                        if (isNaN(+numberLiteral)) {
                            this.diagnosticHandler.reportInvalidNumberFormat(new TextSpan(start, start - this.pos), this.source.substring(start, this.pos));
                        }

                        tokens.push(new Token(TokenType.NumberLiteral, this.pos, numberLiteral));
                    } else {
                        const start = this.pos;

                        while (this.peek() && !/\s/.test(this.peek())) this.pos++;

                        const literal = this.source.substring(start, this.pos);

                        switch (literal) {
                            case "true":
                            case "false":
                                tokens.push(new Token(TokenType.BoolLiteral, this.pos, literal));
                                break;
                            default:
                                tokens.push(new Token(TokenType.Identifier, this.pos, literal));
                        }
                    }
            }
        }

        return tokens;
    }
}

export abstract class SyntaxNode {
    public abstract type(): SyntaxType;

    public abstract children(): SyntaxNode[];
}

export class Token extends SyntaxNode {
    public readonly tokenType: TokenType;
    public readonly span: TextSpan;
    public readonly literal: string;

    constructor(tokenType: TokenType, pos: number, literal: string) {
        super();

        this.tokenType = tokenType;
        this.span = new TextSpan(pos, literal.length);
        this.literal = literal;
    }

    type(): SyntaxType {
        return SyntaxType.Token;
    }

    children(): Token[] {
        return [];
    }
}

export enum TokenType {
    Identifier,
    BoolLiteral,
    NumberLiteral,
    OpenParenthesis,
    CloseParenthesis,
    QuestionMark,
    Colon,
    DoubleEqual,
    BangEqual,
    DoubleGreaterThan,
    TripleGreaterThan,
    GreaterThan,
    GreaterEqualThan,
    DoubleLessThan,
    LessThan,
    LessEqualThan,
    LessEqualGreater,
    DoubleAmpersand,
    Ampersand,
    Caret,
    DoublePipe,
    Pipe,
    Bang,
    Tilde,
    Plus,
    Minus,
    Star,
    DoubleStar,
    Slash,
    DoubleSlash,
    Percent,
}

export namespace TokenType {
    export function unaryPrecedence(type: TokenType): number {
        switch (type) {
            case TokenType.Tilde:
            case TokenType.Bang:
            case TokenType.Plus:
            case TokenType.Minus:
                return 13;
            default:
                return 0;
        }
    }

    export function binaryPrecedence(type: TokenType): number {
        switch (type) {
            case TokenType.QuestionMark:
                return 1;
            case TokenType.DoublePipe:
                return 2;
            case TokenType.DoubleAmpersand:
                return 3;
            case TokenType.Pipe:
                return 4;
            case TokenType.Caret:
                return 5;
            case TokenType.Ampersand:
                return 6;
            case TokenType.DoubleEqual:
            case TokenType.BangEqual:
                return 7;
            case TokenType.GreaterThan:
            case TokenType.GreaterEqualThan:
            case TokenType.LessThan:
            case TokenType.LessEqualThan:
                return 8;
            case TokenType.LessEqualGreater:
                return 9;
            case TokenType.DoubleGreaterThan:
            case TokenType.TripleGreaterThan:
            case TokenType.DoubleLessThan:
                return 10;
            case TokenType.Plus:
            case TokenType.Minus:
                return 11;
            case TokenType.Star:
            case TokenType.Slash:
            case TokenType.DoubleSlash:
            case TokenType.Percent:
                return 12;
            case TokenType.DoubleStar:
                return 13;
            default:
                return 0;
        }
    }
}

export class Parser {
    public readonly diagnosticHandler: DiagnosticHandler;
    private readonly tokens: Token[];
    private pos = 0;

    constructor(source: string) {
        const lexer = new Lexer(source);

        this.tokens = lexer.lex();
        this.diagnosticHandler = lexer.diagnosticHandler;
    }

    private peek(offset = 0): Token {
        return this.pos + offset < this.tokens.length ? this.tokens[this.pos + offset] : this.tokens[this.tokens.length - 1];
    }

    private next(): Token {
        const current = this.peek();
        this.pos++;
        return current;
    }

    private assert(type: TokenType): Token {
        if (this.peek().tokenType == type)
            return this.next();

        this.diagnosticHandler.reportUnexpectedToken(this.peek().span, this.peek().tokenType, type);

        this.pos++;
        return new Token(TokenType.Bang, this.pos - 1, "");
    }

    public parse(): SyntaxNode {
        return this.parseExpression();
    }

    public parseExpression(parentPrecedence = 0): ExpressionSyntax {
        let left: ExpressionSyntax;
        let precedence = TokenType.unaryPrecedence(this.peek().tokenType);
        left = precedence != 0 || precedence > parentPrecedence ? new UnaryExpression(this.next(), this.parseExpression(precedence))
            : this.parsePrimaryExpression();

        for (; ;) {
            precedence = TokenType.binaryPrecedence(this.peek().tokenType);

            if (precedence == 0 || precedence <= parentPrecedence) break;

            left = precedence == 1 ? new TernaryExpression(left, this.next(), this.parseExpression(precedence), this.next(), this.parseExpression(precedence))
                : new BinaryExpression(left, this.next(), this.parseExpression(precedence));
        }

        return left;
    }

    public parsePrimaryExpression(): ExpressionSyntax {
        switch (this.peek().tokenType) {
            case TokenType.OpenParenthesis:
                return new ParenthesizedExpression(this.assert(TokenType.OpenParenthesis), this.parseExpression(), this.assert(TokenType.CloseParenthesis));
            case TokenType.NumberLiteral: {
                const token = this.assert(TokenType.NumberLiteral);
                return new LiteralExpression(token, +token.literal);
            }
            case TokenType.BoolLiteral: {
                const token = this.assert(TokenType.BoolLiteral);
                return new LiteralExpression(token, JSON.parse(token.literal));
            }
            default:
                return new IdentifierExpression(this.assert(TokenType.Identifier));
        }
    }
}

export const enum SyntaxType {
    Token,
    Identifier,
    Literal,
    Parenthesized,
    Unary,
    Binary,
    Ternary
}

export abstract class ExpressionSyntax extends SyntaxNode {
}

export class IdentifierExpression extends ExpressionSyntax {
    public readonly token: Token;

    constructor(token: Token) {
        super();

        this.token = token;
    }

    type(): SyntaxType {
        return SyntaxType.Identifier;
    }

    children(): SyntaxNode[] {
        return [this.token];
    }
}

export class LiteralExpression extends ExpressionSyntax {
    public readonly token: Token;
    public readonly value: any;

    constructor(token: Token, value: any = undefined) {
        super();

        this.token = token;
        this.value = value !== undefined ? value : token.literal;
    }

    type(): SyntaxType {
        return SyntaxType.Literal;
    }

    children(): SyntaxNode[] {
        return [this.token];
    }
}

export class ParenthesizedExpression extends ExpressionSyntax {
    public readonly openParenthesisToken: Token;
    public readonly expression: ExpressionSyntax;
    public readonly closeParenthesisToken: Token;

    constructor(openParenthesisToken: Token, expression: ExpressionSyntax, closeParenthesisToken: Token) {
        super();

        this.openParenthesisToken = openParenthesisToken;
        this.expression = expression;
        this.closeParenthesisToken = closeParenthesisToken;
    }

    type(): SyntaxType {
        return SyntaxType.Parenthesized;
    }

    children(): SyntaxNode[] {
        return [this.openParenthesisToken, this.expression, this.closeParenthesisToken];
    }
}

export class UnaryExpression extends ExpressionSyntax {
    public readonly operator: Token;
    public readonly expression: ExpressionSyntax;

    constructor(operator: Token, expression: ExpressionSyntax) {
        super();

        this.operator = operator;
        this.expression = expression;
    }

    type(): SyntaxType {
        return SyntaxType.Unary;
    }

    children(): SyntaxNode[] {
        return [this.operator, this.expression];
    }
}

export class BinaryExpression extends ExpressionSyntax {
    public readonly left: ExpressionSyntax;
    public readonly operator: Token;
    public readonly right: ExpressionSyntax;

    constructor(left: ExpressionSyntax, operator: Token, right: ExpressionSyntax) {
        super();

        this.left = left;
        this.operator = operator;
        this.right = right;
    }

    type(): SyntaxType {
        return SyntaxType.Binary;
    }

    children(): SyntaxNode[] {
        return [this.left, this.operator, this.right];
    }
}

export class TernaryExpression extends ExpressionSyntax {
    public readonly left: ExpressionSyntax;
    public readonly leftOperator: Token;
    public readonly center: ExpressionSyntax;
    public readonly rightOperator: Token;
    public readonly right: ExpressionSyntax;


    constructor(left: ExpressionSyntax, leftOperator: Token, center: ExpressionSyntax, rightOperator: Token, right: ExpressionSyntax) {
        super();

        this.left = left;
        this.leftOperator = leftOperator;
        this.center = center;
        this.rightOperator = rightOperator;
        this.right = right;
    }

    type(): SyntaxType {
        return SyntaxType.Ternary;
    }

    children(): SyntaxNode[] {
        return [this.left, this.leftOperator, this.center, this.rightOperator, this.right];
    }
}
