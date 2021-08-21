import * as fs from "fs";
import { createInterface } from "readline";
import { bgRedBright, black } from "chalk";
import { Emitter } from "./emit/Emitter";

console.log(process.argv);

let command = process.argv[2];

switch (command) {
    case "eval": {
        let sourceCode = process.argv[3];

        if (!sourceCode) {
            console.error("Require one string to evaluate.");
            process.exit(0);
        }

        let emitter = new Emitter(sourceCode);

        if (emitter.diagnosticHandler.diagnostics.length !== 0) {
            emitter.diagnosticHandler.diagnostics.forEach(d => {
                console.error(bgRedBright(black(d.toString())));
            });
            process.exit(0);
        }

        let result = emitter.emitJs();

        console.log(result);
        console.log(eval(result).toString());
        break;
    }
    case "repl": {
        let readline = createInterface({
            input: process.stdin,
            output: process.stdout
        });
        let input: string;

        let proc = () => readline.question("> ", data => {
            input = data;

            if (input === ":exit") {
                readline.close();
                process.exit(0);
            } else {
                console.log(input);
                proc();
            }
        });

        proc();
        break;
    }
}