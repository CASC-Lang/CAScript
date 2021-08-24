import { describe, it } from "mocha";
import { Diagnostic } from "../src/diagnostic";
import { Emitter } from "../src/emit/Emitter";
import { expect } from "chai";

const getReports = (source: string): Diagnostic[] => {
	const emitter = new Emitter(source);

	return emitter.diagnosticHandler.diagnostics;
};

describe("evaluation error test", () => {
	it("invalid number format I", () => {
		const diagnostics = getReports("1..");

		expect(diagnostics.length).to.equal(1);
		expect(diagnostics[0].message).to.equal(
			"ERROR: Invalid number format: '1..'"
		);
	});

	it("cannot negate bool (-)", () => {
		const diagnostics = getReports("-true");

		expect(diagnostics.length).to.equal(1);
		expect(diagnostics[0].message).to.equal(
			"ERROR: Cannot apply operator '-' on type 'bool'"
		);
	});

	it("bool cannot add with number", () => {
		const diagnostics = getReports("true + 1");

		expect(diagnostics.length).to.equal(1);
		expect(diagnostics[0].message).to.equal(
			"ERROR: Cannot apply operator '+' on type 'bool' and type 'number'"
		);
	});
});
