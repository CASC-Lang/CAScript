import { describe } from "mocha";
import { expect } from "chai";
import { Emitter } from "../src/emit/Emitter";

const evaluate = (sourceCode: string): any => {
	const emitter = new Emitter(sourceCode);

	return eval(emitter.emitJs());
};

describe("number parsing test", () => {
	const tests = new Map([
		["1", 1],
		["1.", 1],
		["1.2", 1.2],
		["1.234", 1.234],
	]);

	tests.forEach((v, k) => {
		it(`${k} = ${v}`, () => {
			expect(evaluate(k)).to.equal(v);
		});
	});
});

describe("literal parsing test", () => {
	const tests = new Map([
		["true", true],
		["false", false],
	]);

	tests.forEach((v, k) => {
		it(`"${k}"'s value is ${v}`, () => {
			expect(evaluate(k)).to.equal(v);
		});
	});
});

describe("numeric arithmetic test", () => {
	const tests = new Map([
		["~100", -101],
		["-100.", -100],
		["+100.", 100],
		["100 + 100", 200],
		["100 - 100", 0],
		["100 * 100", 10e3],
		["100 ** 2", 10e3],
		["100 / 100", 1],
		["100 // 7.9", 12],
        ["100 % 7", 2],
        ["100 << 1", 200],
        ["-100 >>> 1", 2147483598],
        ["100 >> 1", 50],
        ["100 & 1", 0],
        ["100 ^ 1", 101],
        ["100 | 1", 101],
        ["100 <=> 101", -1],
        ["100 <=> 100", 0],
        ["101 <=> 100", 1],
	]);

	tests.forEach((v, k) => {
		it(`${k} = ${v}`, () => {
			expect(evaluate(k)).to.equal(v);
		});
	});
});

describe("logical test", () => {
    const tests = new Map([
        ["!true", false],
        ["!false", true],
        ["1 == 1", true],
        ["1 != 1", false],
        ["1 > 1", false],
        ["1 >= 1", true],
        ["1 < 1", false],
        ["1 <= 1", true],
        ["1 > 2 ? true : false", false],
    ]);

    tests.forEach((v, k) => {
		it(`${k} is ${v}`, () => {
			expect(evaluate(k)).to.equal(v);
		});
	});
});
