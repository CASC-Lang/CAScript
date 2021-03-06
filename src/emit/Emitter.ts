import {
	BinaryOperatorType,
	Binder,
	BoundBinaryExpression,
	BoundExpression,
	BoundLiteralExpression,
	BoundParenthesizedExpression,
	BoundTernaryExpression,
	BoundType,
	BoundUnaryExpression,
	UnaryOperatorType,
} from "../binding/Binder";
import { DiagnosticHandler } from "../diagnostic";
import { BoundStatement, BoundExpressionStatement } from "../binding/Binder";

export class Emitter {
	public readonly diagnosticHandler: DiagnosticHandler;
	public readonly root: BoundStatement;

	constructor(source: string) {
		const binder = new Binder(source);

		this.root = binder.bind();
		this.diagnosticHandler = binder.diagnosticHandler;
	}

	public emitJs(): string {
		if (this.diagnosticHandler.diagnostics.length !== 0) return "";
		else return new JsEmitter().emit(this.root);
	}
}

class JsEmitter {
	public emit(root: BoundStatement): string {
		const builder = new Array<string>();

		this.emitStatement(root, builder);

		return builder.join(" ");
	}

	private emitStatement(statement: BoundStatement, builder: string[]) {
		switch (statement.boundType()) {
			case BoundType.VariableDeclaration:
			case BoundType.ExpressionStatement:
				this.emitExpression(
					(statement as BoundExpressionStatement).expression,
					builder
				);
				builder.push("\n");
				break;
		}
	}

	private emitExpression(expression: BoundExpression, builder: string[]) {
		switch (expression.boundType()) {
			case BoundType.Literal:
				this.emitLiteralExpression(
					expression as BoundLiteralExpression,
					builder
				);
				break;
			case BoundType.Parenthesized: {
				const b1 = new Array<string>();
				this.emitExpression(
					(expression as BoundParenthesizedExpression).expression,
					b1
				);
				builder.push(`(${b1.join(" ")})`);
				break;
			}
			case BoundType.Unary:
				this.emitUnaryExpression(
					expression as BoundUnaryExpression,
					builder
				);
				break;
			case BoundType.Binary:
				this.emitBinaryExpression(
					expression as BoundBinaryExpression,
					builder
				);
				break;
			case BoundType.Ternary:
				this.emitTernaryExpression(
					expression as BoundTernaryExpression,
					builder
				);
				break;
		}
	}

	private emitLiteralExpression(
		expression: BoundLiteralExpression,
		builder: string[]
	) {
		builder.push(expression.value);
	}

	private emitUnaryExpression(
		expression: BoundUnaryExpression,
		builder: string[]
	) {
		switch (expression.operator.operatorType) {
			case UnaryOperatorType.Complement:
				builder.push("~");
				this.emitExpression(expression.expression, builder);
				break;
			case UnaryOperatorType.LogicalNot:
				builder.push("!");
				this.emitExpression(expression.expression, builder);
				break;
			case UnaryOperatorType.Identity:
				builder.push("+");
				this.emitExpression(expression.expression, builder);
				break;
			case UnaryOperatorType.Negation:
				builder.push("-");
				this.emitExpression(expression.expression, builder);
				break;
		}
	}

	private emitBinaryExpression(
		expression: BoundBinaryExpression,
		builder: string[]
	) {
		switch (expression.operator.operatorType) {
			case BinaryOperatorType.Addition:
				this.emitExpression(expression.left, builder);
				builder.push("+");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Subtraction:
				this.emitExpression(expression.left, builder);
				builder.push("-");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Multiplication:
				this.emitExpression(expression.left, builder);
				builder.push("*");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Exponent: {
				const b1 = new Array<string>("Math.pow(");
				this.emitExpression(expression.left, b1);
				b1.push(", ");
				this.emitExpression(expression.right, b1);
				b1.push(")");
				builder.push(b1.join(""));
				break;
			}
			case BinaryOperatorType.Division:
				this.emitExpression(expression.left, builder);
				builder.push("/");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.FloorDivision: {
				const b1 = new Array<string>("Math.floor(");
				this.emitExpression(expression.left, b1);
				b1.push(" / ");
				this.emitExpression(expression.right, b1);
				b1.push(")");
				builder.push(b1.join(""));
				break;
			}
			case BinaryOperatorType.Modulus:
				this.emitExpression(expression.left, builder);
				builder.push("%");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Equal:
				this.emitExpression(expression.left, builder);
				builder.push("===");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.NotEqual:
				this.emitExpression(expression.left, builder);
				builder.push("!==");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.LeftShift:
				this.emitExpression(expression.left, builder);
				builder.push("<<");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.UnsignedRightShift:
				this.emitExpression(expression.left, builder);
				builder.push(">>>");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.RightShift:
				this.emitExpression(expression.left, builder);
				builder.push(">>");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.BitwiseAnd:
				this.emitExpression(expression.left, builder);
				builder.push("&");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.BitwiseExclusiveOr:
				this.emitExpression(expression.left, builder);
				builder.push("^");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.BitwiseInclusiveOr:
				this.emitExpression(expression.left, builder);
				builder.push("|");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.LogicalAnd:
				this.emitExpression(expression.left, builder);
				builder.push("&&");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.LogicalOr:
				this.emitExpression(expression.left, builder);
				builder.push("||");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Greater:
				this.emitExpression(expression.left, builder);
				builder.push(">");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.GreaterEqual:
				this.emitExpression(expression.left, builder);
				builder.push(">=");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.Less:
				this.emitExpression(expression.left, builder);
				builder.push("<");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.LessEqual:
				this.emitExpression(expression.left, builder);
				builder.push("<=");
				this.emitExpression(expression.right, builder);
				break;
			case BinaryOperatorType.ThreeWayComparison: {
				const b1 = new Array<string>("(");
				this.emitExpression(expression.left, b1);
				b1.push(" === ");
				this.emitExpression(expression.right, b1);
				b1.push(" ? 0 : ");
				this.emitExpression(expression.left, b1);
				b1.push(" > ");
				this.emitExpression(expression.right, b1);
				b1.push(" ? 1 : -1)");
				builder.push(b1.join(""));
			}
		}
	}

	private emitTernaryExpression(
		expression: BoundTernaryExpression,
		builder: string[]
	) {
		this.emitExpression(expression.left, builder);
		builder.push("?");
		this.emitExpression(expression.center, builder);
		builder.push(":");
		this.emitExpression(expression.right, builder);
	}
}
