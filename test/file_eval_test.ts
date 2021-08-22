import { readFileSync } from "fs";
import { describe } from "mocha";
import { expect, should } from "chai";
import { evaluate } from "./eval_test";

describe("eval.cascx evaluation test", () => {
    const fileContent = readFileSync("../example/threeWayOpTest.cascx", "utf-8");

    it(`${fileContent} is true`, () => {
        expect(evaluate(fileContent)).to.equal(true);
    })
})
