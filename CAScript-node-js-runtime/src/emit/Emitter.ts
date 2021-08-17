import {
    BinaryOperatorType,
    Binder,
    BoundBinaryExpression,
    BoundExpression,
    BoundLiteralExpression,
    BoundTernaryExpression,
    BoundType
} from "../binding/Binder";

export class Emitter {
    public root: BoundExpression;

    constructor(source: string) {
        this.root = new Binder(source).bind();
    }

    public emitJs(): string {
        return JsEmitter.emit(this.root);
    }
}

class JsEmitter {
    public static emit(root: BoundExpression): string {
        let builder = new Array<string>();

        this.emitExpression(root, builder);

        return builder.join(" ");
    }

    private static emitExpression(expression: BoundExpression, builder: string[]) {
        switch (expression.boundType()) {
            case BoundType.Literal:
                this.emitLiteralExpression(expression as BoundLiteralExpression, builder);
                break;
            case BoundType.Binary:
                this.emitBinaryExpression(expression as BoundBinaryExpression, builder);
                break;
            case BoundType.Ternary:
                this.emitTernaryExpression(expression as BoundTernaryExpression, builder);
                break;
        }
    }

    private static emitLiteralExpression(expression: BoundLiteralExpression, builder: string[]) {
        builder.push(expression.value);
    }

    private static emitBinaryExpression(expression: BoundBinaryExpression, builder: string[]) {
        switch (expression.operator.operatorType) {
            case BinaryOperatorType.Addition:
                this.emitExpression(expression.left, builder);
                builder.push("+");
                this.emitExpression(expression.right, builder);
                break;
            case BinaryOperatorType.Minus:
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
                let b1 = new Array<string>("Math.pow(");
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
                let b1 = new Array<string>("Math.floor(");
                this.emitExpression(expression.left, b1);
                b1.push(" % ");
                this.emitExpression(expression.right, b1);
                b1.push(")")
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
            case BinaryOperatorType.UnsignedRightShift:
                this.emitExpression(expression.left, builder);
                builder.push(">>>");
                this.emitExpression(expression.right, builder);
                break;
            case BinaryOperatorType.ThreeWayComparison: {
                let b1 = new Array<string>("(");
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

    private static emitTernaryExpression(expression: BoundTernaryExpression, builder: string[]) {
        this.emitExpression(expression.left, builder);
        builder.push("?");
        this.emitExpression(expression.center, builder);
        builder.push(":");
        this.emitExpression(expression.right, builder);
    }
}
