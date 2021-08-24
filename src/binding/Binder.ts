import { setMaxListeners } from "process";
import { DiagnosticHandler } from "../diagnostic";
import { VariableSymbol } from "../symbols";
import {
	AssignmentExpression,
	StatementSyntax,
	ExpressionStatement,
	VariableDeclarationStatement,
} from "../syntax/Parser";
import {
	BinaryExpression,
	ExpressionSyntax,
	IdentifierExpression,
	LiteralExpression,
	ParenthesizedExpression,
	Parser,
	SyntaxType,
	TernaryExpression,
	TokenType,
	UnaryExpression,
} from "../syntax/Parser";
import "../utils/map";

export class Binder {
	private readonly variables: Map<VariableSymbol, any>;
	public readonly diagnosticHandler: DiagnosticHandler;
	private readonly root: StatementSyntax;

	constructor(source: string, variables: Map<VariableSymbol, any> = new Map()) {
		const parser = new Parser(source);

		this.variables = variables;
		this.root = parser.parse();
		this.diagnosticHandler = parser.diagnosticHandler;
	}

	public bind(): BoundStatement {
		return this.bindStatement(this.root);
	}

	private bindStatement(statement: StatementSyntax): BoundStatement {
		switch (statement.type()) {
			case SyntaxType.VariableDeclaration:
				return this.bindVariableDeclarationStatement(
					statement as VariableDeclarationStatement
				);
			case SyntaxType.StatementExpression:
				return new BoundExpressionStatement(
					this.bindExpression(
						(statement as ExpressionStatement).expression
					)
				);
			default:
				throw new Error(
					`Unknown statement ${SyntaxType[statement.type()]}`
				);
		}
	}

	private bindVariableDeclarationStatement(
		statement: VariableDeclarationStatement
	): BoundStatement {
		if (
			this.variables.find((key) => {
				return key.name === statement.identifier.literal;
			})
		) {
			// err
		}

		return new BoundVariableDeclarationStatement(
			statement.identifier.literal,
			this.bindExpression(statement.expression)
		);
	}

	private bindExpression(expression: ExpressionSyntax): BoundExpression {
		switch (expression.type()) {
			case SyntaxType.Literal:
				return this.bindLiteralExpression(
					expression as LiteralExpression
				);
			case SyntaxType.Identifier:
				return this.bindIdentifierExpression(
					expression as IdentifierExpression
				);
			case SyntaxType.Assignment:
				return this.bindAssignmentExpression(
					expression as AssignmentExpression
				);
			case SyntaxType.Parenthesized:
				return new BoundParenthesizedExpression(
					this.bindExpression(
						(expression as ParenthesizedExpression).expression
					)
				);
			case SyntaxType.Unary:
				return this.bindUnaryExpression(expression as UnaryExpression);
			case SyntaxType.Binary:
				return this.bindBinaryExpression(
					expression as BinaryExpression
				);
			case SyntaxType.Ternary:
				return this.bindTernaryExpression(
					expression as TernaryExpression
				);
			default:
				throw new Error(
					`Unknown expression ${SyntaxType[expression.type()]}`
				);
		}
	}

	private bindLiteralExpression(
		expression: LiteralExpression
	): BoundExpression {
		return new BoundLiteralExpression(expression.value);
	}

	private bindIdentifierExpression(
		expression: IdentifierExpression
	): BoundExpression {
		return new BoundIdentifierExpression(
			expression.token.literal,
			this.variables.find(
				(key) => key.name === expression.token.literal
			 ).key.type || Type.Undefined
		);
	}

	private bindAssignmentExpression(
		expression: AssignmentExpression
	): BoundExpression {
		throw new Error();
	}

	private bindUnaryExpression(expression: UnaryExpression): BoundExpression {
		const operand = this.bindExpression(expression.expression);
		const operator = BoundUnaryOperator.bind(
			expression.operator.tokenType,
			operand.type()
		);

		if (operator) {
			return new BoundUnaryExpression(operator, operand);
		} else {
			this.diagnosticHandler.reportUnaryTypeMismatch(
				expression.operator.span,
				expression.operator.literal,
				operand.type()
			);
			return new BoundErrorExpression();
		}
	}

	private bindBinaryExpression(
		expression: BinaryExpression
	): BoundExpression {
		const left = this.bindExpression(expression.left);
		const right = this.bindExpression(expression.right);
		const operator = BoundBinaryOperator.bind(
			expression.operator.tokenType,
			left.type(),
			right.type()
		);

		if (operator) {
			return new BoundBinaryExpression(left, operator, right);
		} else {
			this.diagnosticHandler.reportBinaryTypeMismatch(
				expression.operator.span,
				expression.operator.literal,
				left.type(),
				right.type()
			);
			return new BoundErrorExpression();
		}
	}

	private bindTernaryExpression(
		expression: TernaryExpression
	): BoundExpression {
		const left = this.bindExpression(expression.left);
		const center = this.bindExpression(expression.center);
		const right = this.bindExpression(expression.right);

		if (left.type() != Type.Bool) {
			throw new Error("Cannot convert ");
		}

		return new BoundTernaryExpression(left, center, right);
	}
}

export abstract class BoundNode {
	public abstract boundType(): BoundType;
}

export const enum BoundType {
	ERROR,
	Literal,
	Identifier,
	Assignment,
	Parenthesized,
	Unary,
	Binary,
	Ternary,
	VariableDeclaration,
	ExpressionStatement,
}

export const enum Type {
	Undefined = "undefined",
	Bool = "bool",
	Number = "number",
}

export abstract class BoundExpression extends BoundNode {
	public abstract type(): Type;
}

export class BoundErrorExpression extends BoundExpression {
	public boundType(): BoundType {
		return BoundType.ERROR;
	}

	public type(): Type {
		return Type.Undefined;
	}
}

export class BoundLiteralExpression extends BoundExpression {
	public readonly value: any;

	constructor(value: any) {
		super();

		this.value = value;
	}

	type(): Type {
		switch (typeof this.value) {
			case "boolean":
				return Type.Bool;
			case "number":
				return Type.Number;
			default:
				throw new Error(`Unknown type of value: ${this.value}`);
		}
	}

	boundType(): BoundType {
		return BoundType.Literal;
	}
}

export class BoundIdentifierExpression extends BoundExpression {
	public readonly identifier: string;
	public readonly variableType: Type;

	constructor(identifier: string, variableType: Type) {
		super();

		this.identifier = identifier;
		this.variableType = variableType;
	}

	boundType(): BoundType {
		return BoundType.Identifier;
	}

	type(): Type {
		return this.variableType;
	}
}

export class BoundAssignmentExpression extends BoundExpression {
	public readonly identifier: string;
	public readonly operator: BoundAssignmentOperator;
	public readonly expression: BoundExpression;

	constructor(
		identifier: string,
		operator: BoundAssignmentOperator,
		expression: BoundExpression
	) {
		super();

		this.identifier = identifier;
		this.operator = operator;
		this.expression = expression;
	}

	type(): Type {
		return this.operator.resultType;
	}

	boundType(): BoundType {
		return BoundType.Assignment;
	}
}

export const enum AssignmentOperatorType {
	PureAssign,
}

export class BoundAssignmentOperator {
	private static readonly types = [
		new BoundAssignmentOperator(
			TokenType.Equal,
			AssignmentOperatorType.PureAssign,
			Type.Undefined,
			Type.Undefined,
			Type.Undefined
		),
	];

	public readonly tokenType: TokenType;
	public readonly assignmentType: AssignmentOperatorType;
	public readonly variableType: Type;
	public readonly expressionType: Type;
	public readonly resultType: Type;

	constructor(
		tokenType: TokenType,
		assignmentType: AssignmentOperatorType,
		variableType: Type,
		expressionType: Type,
		resultType: Type
	) {
		this.tokenType = tokenType;
		this.assignmentType = assignmentType;
		this.variableType = variableType;
		this.expressionType = expressionType;
		this.resultType = resultType;
	}

	public static bind(
		tokenType: TokenType,
		variableType: Type,
		expressionType: Type
	): BoundAssignmentOperator {
		if (tokenType === TokenType.Equal) {
			return this.types[0];
		} else {
			for (const op of this.types)
				if (
					op.tokenType == tokenType &&
					op.variableType == variableType &&
					op.expressionType == expressionType
				)
					return op;

			return undefined;
		}
	}
}

export class BoundParenthesizedExpression extends BoundExpression {
	public readonly expression: BoundExpression;

	constructor(expression: BoundExpression) {
		super();

		this.expression = expression;
	}

	boundType(): BoundType {
		return BoundType.Parenthesized;
	}

	type(): Type {
		return this.expression.type();
	}
}

export const enum UnaryOperatorType {
	Complement,
	LogicalNot,
	Identity,
	Negation,
}

export class BoundUnaryOperator {
	private static readonly types = [
		new BoundUnaryOperator(
			TokenType.Tilde,
			UnaryOperatorType.Complement,
			Type.Number
		),
		new BoundUnaryOperator(
			TokenType.Bang,
			UnaryOperatorType.LogicalNot,
			Type.Bool
		),
		new BoundUnaryOperator(
			TokenType.Plus,
			UnaryOperatorType.Identity,
			Type.Number
		),
		new BoundUnaryOperator(
			TokenType.Minus,
			UnaryOperatorType.Negation,
			Type.Number
		),
	];

	public readonly tokenType: TokenType;
	public readonly operatorType: UnaryOperatorType;
	public readonly operandType: Type;
	public readonly resultType: Type;

	constructor(
		tokenType: TokenType,
		operatorType: UnaryOperatorType,
		operandType: Type,
		resultType?: Type
	) {
		this.tokenType = tokenType;
		this.operatorType = operatorType;
		this.operandType = operandType;
		this.resultType = resultType || operandType;
	}

	public static bind(
		tokenType: TokenType,
		operandType: Type
	): BoundUnaryOperator | undefined {
		for (const op of this.types)
			if (op.tokenType == tokenType && op.operandType == operandType)
				return op;

		return undefined;
	}
}

export class BoundUnaryExpression extends BoundExpression {
	public readonly operator: BoundUnaryOperator;
	public readonly expression: BoundExpression;

	constructor(operator: BoundUnaryOperator, expression: BoundExpression) {
		super();

		this.operator = operator;
		this.expression = expression;
	}

	boundType(): BoundType {
		return BoundType.Unary;
	}

	type(): Type {
		return this.operator.resultType;
	}
}

export const enum BinaryOperatorType {
	Addition,
	Subtraction,
	Multiplication,
	Exponent,
	Division,
	FloorDivision,
	Modulus,
	Equal,
	NotEqual,
	LeftShift,
	UnsignedRightShift,
	RightShift,
	BitwiseAnd,
	BitwiseExclusiveOr,
	BitwiseInclusiveOr,
	LogicalAnd,
	LogicalOr,
	Greater,
	GreaterEqual,
	Less,
	LessEqual,
	ThreeWayComparison,
}

export class BoundBinaryOperator {
	private static readonly types = [
		new BoundBinaryOperator(
			TokenType.Plus,
			BinaryOperatorType.Addition,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Minus,
			BinaryOperatorType.Subtraction,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Star,
			BinaryOperatorType.Multiplication,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.DoubleStar,
			BinaryOperatorType.Exponent,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Slash,
			BinaryOperatorType.Division,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.DoubleSlash,
			BinaryOperatorType.FloorDivision,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Percent,
			BinaryOperatorType.Modulus,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.DoubleEqual,
			BinaryOperatorType.Equal,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.DoubleEqual,
			BinaryOperatorType.Equal,
			Type.Bool,
			Type.Bool,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.BangEqual,
			BinaryOperatorType.NotEqual,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.BangEqual,
			BinaryOperatorType.NotEqual,
			Type.Bool,
			Type.Bool,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.DoubleGreaterThan,
			BinaryOperatorType.RightShift,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.TripleGreaterThan,
			BinaryOperatorType.UnsignedRightShift,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.DoubleLessThan,
			BinaryOperatorType.LeftShift,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Ampersand,
			BinaryOperatorType.BitwiseAnd,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Caret,
			BinaryOperatorType.BitwiseExclusiveOr,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.Pipe,
			BinaryOperatorType.BitwiseInclusiveOr,
			Type.Number,
			Type.Number,
			Type.Number
		),
		new BoundBinaryOperator(
			TokenType.DoubleAmpersand,
			BinaryOperatorType.LogicalAnd,
			Type.Bool,
			Type.Bool,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.DoublePipe,
			BinaryOperatorType.LogicalOr,
			Type.Bool,
			Type.Bool,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.GreaterThan,
			BinaryOperatorType.Greater,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.GreaterEqualThan,
			BinaryOperatorType.GreaterEqual,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.LessThan,
			BinaryOperatorType.Less,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.LessEqualThan,
			BinaryOperatorType.LessEqual,
			Type.Number,
			Type.Number,
			Type.Bool
		),
		new BoundBinaryOperator(
			TokenType.LessEqualGreater,
			BinaryOperatorType.ThreeWayComparison,
			Type.Number,
			Type.Number,
			Type.Number
		),
	];

	public readonly tokenType: TokenType;
	public readonly operatorType: BinaryOperatorType;
	public readonly left: Type;
	public readonly right: Type;
	public readonly resultType: Type;

	constructor(
		tokenType: TokenType,
		operatorType: BinaryOperatorType,
		left: Type,
		right: Type,
		resultType: Type
	) {
		this.tokenType = tokenType;
		this.operatorType = operatorType;
		this.left = left;
		this.right = right;
		this.resultType = resultType;
	}

	public static bind(
		tokenType: TokenType,
		left: Type,
		right: Type
	): BoundBinaryOperator | undefined {
		for (const op of this.types)
			if (
				op.tokenType == tokenType &&
				op.left == left &&
				op.right == right
			)
				return op;

		return undefined;
	}
}

export class BoundBinaryExpression extends BoundExpression {
	public readonly left: BoundExpression;
	public readonly operator: BoundBinaryOperator;
	public readonly right: BoundExpression;

	constructor(
		left: BoundExpression,
		operator: BoundBinaryOperator,
		right: BoundExpression
	) {
		super();

		this.left = left;
		this.operator = operator;
		this.right = right;
	}

	boundType(): BoundType {
		return BoundType.Binary;
	}

	type(): Type {
		return this.operator.resultType;
	}
}

/**
 *  Currently there's only one ternary expression variant, so we collapsed it into one single class.
 */
export class BoundTernaryExpression extends BoundExpression {
	public readonly left: BoundExpression;
	public readonly center: BoundExpression;
	public readonly right: BoundExpression;

	constructor(
		left: BoundExpression,
		center: BoundExpression,
		right: BoundExpression
	) {
		super();

		this.left = left;
		this.center = center;
		this.right = right;
	}

	boundType(): BoundType {
		return BoundType.Ternary;
	}

	type(): Type {
		return this.center.type();
	}
}

export abstract class BoundStatement extends BoundNode {}

export class BoundVariableDeclarationStatement extends BoundNode {
	public readonly identifier: string;
	public readonly expression: BoundExpression;

	constructor(identifier: string, expression: BoundExpression) {
		super();

		this.identifier = identifier;
		this.expression = expression;
	}

	boundType(): BoundType {
		return BoundType.VariableDeclaration;
	}
}

export class BoundExpressionStatement extends BoundNode {
	public readonly expression: BoundExpression;

	constructor(expression: BoundExpression) {
		super();

		this.expression = expression;
	}

	boundType(): BoundType {
		return BoundType.ExpressionStatement;
	}
}
