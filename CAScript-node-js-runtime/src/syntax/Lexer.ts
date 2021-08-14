export class Lexer {
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
                    tokens.push(new Token(Type.OpenParenthesis, this.next()));
                    break;
                case ")":
                    tokens.push(new Token(Type.CloseParenthesis, this.next()));
                    break;
                case "?":
                    tokens.push(new Token(Type.QuestionMark, this.next()));
                    break;
                case ":":
                    tokens.push(new Token(Type.Colon, this.next()));
                    break;
                case "=":
                    if (this.peek(1) === "=") {
                        tokens.push(new Token(Type.DoubleEqual, this.next(2)));
                    } else {
                        this.pos++
                    }
                    break;
                case "!":
                    if (this.peek(1) === "=") {
                        tokens.push(new Token(Type.BangEqual, this.next(2)));
                    } else {
                        this.pos++
                    }
                    break;
                case ">":
                    if (this.peek(1) === ">") {
                        if (this.peek(2) === ">") {
                            tokens.push(new Token(Type.TripleGreaterThan, this.next(3)));
                        } else {
                            tokens.push(new Token(Type.DoubleGreaterThan, this.next(2)));
                        }
                    } else if (this.peek(1) === "=") {
                        tokens.push(new Token(Type.GreaterEqualThan, this.next(2)));
                        this.pos += 2;
                    } else {
                        tokens.push(new Token(Type.GreaterThan, this.next()));
                    }
                    break;
                case "<":
                    if (this.peek(1) === "<") {
                        tokens.push(new Token(Type.DoubleLessThan, this.next(2)));
                    } else if (this.peek(1) === "=") {
                        if (this.peek(2) === ">") {
                            tokens.push(new Token(Type.LessEqualGreater, this.next(3)));
                        } else {
                            tokens.push(new Token(Type.LessEqualGreater, this.next(2)));
                        }
                    } else {
                        tokens.push(new Token(Type.LessThan, this.next()));
                    }
                    break;
                case "&":
                    if (this.peek(1) === "&") {
                        tokens.push(new Token(Type.DoubleAmpersand, this.next(2)));
                    } else {
                        tokens.push(new Token(Type.Ampersand, this.next()));
                    }
                    break;
                case "^":
                    tokens.push(new Token(Type.Caret, this.next()));
                    break;
                case "|":
                    if (this.peek(1) === "|") {
                        tokens.push(new Token(Type.DoublePipe, this.next(2)));
                    } else {
                        tokens.push(new Token(Type.Pipe, this.next()));
                    }
                    break;
                case "~":
                    tokens.push(new Token(Type.Tilde, this.next()));
                    break;
                case "+":
                    tokens.push(new Token(Type.Plus, this.next()));
                    break;
                case "-":
                    tokens.push(new Token(Type.Minus, this.next()));
                    break;
                case "*":
                    if (this.peek(1) === "*") {
                        tokens.push(new Token(Type.DoubleStar, this.next(2)));
                    } else {
                        tokens.push(new Token(Type.Star, this.next()));
                    }
                    break;
                case "/":
                    if (this.peek(1) === "/") {
                        tokens.push(new Token(Type.DoubleSlash, this.next(2)));
                    } else {
                        tokens.push(new Token(Type.Slash, this.next()));
                    }
                    break;
                case "%":
                    tokens.push(new Token(Type.Percent, this.next()));
                    break;
                case " ":
                case "\t":
                case "\n":
                case "\r":
                    this.next();
                    break;
                default:
                    if (!isNaN(+this.peek())) {
                        let start = this.pos;

                        while (!isNaN(+this.peek())) this.pos++;

                        tokens.push(new Token(Type.NumberLiteral, this.source.substring(start, this.pos)));
                    }
            }
        }

        return tokens;
    }
}

export class Token {
    public readonly type: Type;
    public readonly literal: string;

    constructor(type: Type, literal: string) {
        this.type = type;
        this.literal = literal;
    }
}

export const enum Type {
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
