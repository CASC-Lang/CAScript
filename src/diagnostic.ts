import { Type } from "./binding/Binder";

export class DiagnosticHandler {
    public readonly diagnostics = new Array<Diagnostic>();

    private report(span: TextSpan, message: string) {
        this.diagnostics.push(new Diagnostic(span, message));
    }

    public reportUnaryTypeMismatch(span: TextSpan, operator: string, providedType: Type) {
        this.report(span, `ERROR: Cannot apply operator '${operator}' on type '${providedType}'`);
    }

    public reportBinaryTypeMismatch(span: TextSpan, operator: string, type1: Type, type2: Type) {
        
    }
}

export class Diagnostic {
    public readonly span: TextSpan;
    public readonly message: string;

    constructor(span: TextSpan, message: string) {
        this.span = span;
        this.message = message;
    }

    public toString = (): string => {
        return `${this.span.toString()}: ${this.message}`
    }
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
        return `(${this.start}, ${this.end})`
    }
}