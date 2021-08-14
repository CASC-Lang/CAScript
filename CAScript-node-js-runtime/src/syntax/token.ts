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