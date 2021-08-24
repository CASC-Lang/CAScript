import { Type } from "./binding/Binder";

export abstract class Symbol {}

export class VariableSymbol extends Symbol {
    public readonly name: string;
    public readonly type: Type;

    constructor(name: string, type: Type) {
        super();

        this.name = name;
        this.type = type;
    }
}