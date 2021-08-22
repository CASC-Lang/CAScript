import { Type } from "./binding/Binder";
import { TokenType } from "./syntax/Parser";

export class DiagnosticHandler {
<<<<<<< HEAD:CAScript-node-js-runtime/src/diagnostic.ts
	public readonly diagnostics = new Array<Diagnostic>();

	private report(span: TextSpan, message: string) {
		this.diagnostics.push(new Diagnostic(span, message));
	}

	public reportUnaryTypeMismatch(
		span: TextSpan,
		operator: string,
		providedType: Type
	) {
		this.report(
			span,
			`ERROR: Cannot apply operator '${operator}' on type '${providedType}'`
		);
	}

	public reportBinaryTypeMismatch(
		span: TextSpan,
		operator: string,
		type1: Type,
		type2: Type
	) {}
=======
    public readonly diagnostics = new Array<Diagnostic>();

    private report(span: TextSpan, message: string) {
        this.diagnostics.push(new Diagnostic(span, message));
    }
    
    public reportInvalidNumberFormat(span: TextSpan, numberLiteral: string) {
        this.report(span, `ERROR: Invalid number format: '${numberLiteral}'`);
    }

    public reportUnexpectedToken(span: TextSpan, providedToken: TokenType, expectedToken: TokenType) {
        this.report(span, `ERROR: Unexpected token '${TokenType[providedToken]}', expected token '${TokenType[expectedToken]}'`);
    }

    public reportUnaryTypeMismatch(span: TextSpan, operator: string, providedType: Type) {
        this.report(span, `ERROR: Cannot apply operator '${operator}' on type '${providedType}'`);
    }

    public reportBinaryTypeMismatch(span: TextSpan, operator: string, type1: Type, type2: Type) {
        this.report(span, `ERROR: Cannot apply operator '${operator}' on type '${type1}' and type '${type2}'`);
    }
>>>>>>> 89a21e72461634cebff7b764825e3454f1f14096:src/diagnostic.ts
}

export class Diagnostic {
	public readonly span: TextSpan;
	public readonly message: string;

	constructor(span: TextSpan, message: string) {
		this.span = span;
		this.message = message;
	}

	public toString = (): string => {
		return `${this.span.toString()}: ${this.message}`;
	};
}

export class TextSpan {
	public readonly start: number;
	public readonly len: number;
	public readonly end: number;

	constructor(start: number, len: number) {
		this.start = start;
		this.len = len;
		this.end = start + len;
	}

	public toString = (): string => {
		return `(${this.start}, ${this.end})`;
	};
}
