import {
	BinaryOperatorType,
	Binder,
	BoundAssignmentExpression,
	BoundBinaryExpression,
	BoundExpression,
	BoundIdentifierExpression,
	BoundLiteralExpression,
	BoundParenthesizedExpression,
	BoundStatement,
	BoundTernaryExpression,
	BoundUnaryExpression,
	BoundVariableDeclarationStatement,
	UnaryOperatorType,
} from "../binding/Binder";
import { DiagnosticHandler } from "../diagnostic";
import { BoundExpressionStatement } from "../binding/Binder";
import { VariableSymbol } from "../symbols";

export class Evaluator {
	private readonly variables: Map<VariableSymbol, any> = new Map();

	public evaluate(sourceCode: string): EvaluationResult {
		const binder = new Binder(sourceCode, this.variables);

		return new EvaluationResult(
			this.evaluateStatement(binder.bind()),
			binder.diagnosticHandler
		);
	}

	private evaluateStatement(statement: BoundStatement): any {
		if (statement instanceof BoundVariableDeclarationStatement) {
			const evaluatedValue = this.evaluateExpression(
				statement.expression
			);
			this.variables.set(
				new VariableSymbol(
					statement.identifier,
					statement.expression.type()
				),
				evaluatedValue
			);
			return evaluatedValue;
		}

		if (statement instanceof BoundExpressionStatement) {
			return this.evaluateExpression(statement.expression);
		}

		return undefined;
	}

	private evaluateExpression(expression: BoundExpression): any {
		if (expression instanceof BoundLiteralExpression)
			return expression.value;

		if (expression instanceof BoundIdentifierExpression)
			return this.variables.find(
				(key) => key.name === expression.identifier
			).value;

		if (expression instanceof BoundAssignmentExpression) {
			const evaluatedValue = this.evaluateExpression(
				expression.expression
			);
			this.variables.set(
				new VariableSymbol(expression.identifier, expression.type()),
				evaluatedValue
			);
			return evaluatedValue;
		}

		if (expression instanceof BoundParenthesizedExpression) {
			return this.evaluateExpression(expression.expression);
		}

		if (expression instanceof BoundUnaryExpression) {
			const evaluatedValue = this.evaluateExpression(
				expression.expression
			);

			switch (expression.operator.operatorType) {
				case UnaryOperatorType.Complement:
					return ~evaluatedValue;
				case UnaryOperatorType.LogicalNot:
					return !evaluatedValue;
				case UnaryOperatorType.Identity:
					return evaluatedValue;
				case UnaryOperatorType.Negation:
					return -evaluatedValue;
			}
		}

		if (expression instanceof BoundBinaryExpression) {
			const leftValue = this.evaluateExpression(expression.left),
				rightValue = this.evaluateExpression(expression.right);

			switch (expression.operator.operatorType) {
				case BinaryOperatorType.Addition:
					return leftValue + rightValue;
				case BinaryOperatorType.Subtraction:
					return leftValue - rightValue;
				case BinaryOperatorType.Multiplication:
					return leftValue * rightValue;
				case BinaryOperatorType.Exponent:
					return leftValue ** rightValue;
				case BinaryOperatorType.Division:
					return leftValue / rightValue;
				case BinaryOperatorType.FloorDivision:
					return Math.floor(leftValue / rightValue);
				case BinaryOperatorType.Modulus:
					return leftValue % rightValue;
				case BinaryOperatorType.Equal:
					return leftValue === rightValue;
				case BinaryOperatorType.NotEqual:
					return leftValue !== rightValue;
				case BinaryOperatorType.LeftShift:
					return leftValue << rightValue;
				case BinaryOperatorType.UnsignedRightShift:
					return leftValue >>> rightValue;
				case BinaryOperatorType.RightShift:
					return leftValue >> rightValue;
				case BinaryOperatorType.BitwiseAnd:
					return leftValue & rightValue;
				case BinaryOperatorType.BitwiseExclusiveOr:
					return leftValue ^ rightValue;
				case BinaryOperatorType.BitwiseInclusiveOr:
					return leftValue | rightValue;
				case BinaryOperatorType.LogicalAnd:
					return leftValue && rightValue;
				case BinaryOperatorType.LogicalOr:
					return leftValue || rightValue;
				case BinaryOperatorType.Greater:
					return leftValue > rightValue;
				case BinaryOperatorType.GreaterEqual:
					return leftValue >= rightValue;
				case BinaryOperatorType.Less:
					return leftValue < rightValue;
				case BinaryOperatorType.LessEqual:
					return leftValue <= rightValue;
				case BinaryOperatorType.ThreeWayComparison:
					return leftValue === rightValue
						? 0
						: leftValue > rightValue
						? 1
						: -1;
			}
		}

		if (expression instanceof BoundTernaryExpression) {
			const leftValue = this.evaluateExpression(expression.left),
				centerValue = this.evaluateExpression(expression.center),
				rightValue = this.evaluateExpression(expression.right);

			return leftValue ? centerValue : rightValue;
		}

		return undefined;
	}
}

export class EvaluationResult {
	public readonly resultValue: any;
	public readonly diagnosticHolder: DiagnosticHandler;

	constructor(resultValue: any, diagnosticHolder: DiagnosticHandler) {
		this.resultValue = resultValue;
		this.diagnosticHolder = diagnosticHolder;
	}
}
