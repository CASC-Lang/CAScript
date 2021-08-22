import * as fs from "fs";
import { createInterface } from "readline";
import { bgGreenBright, bgRedBright, black } from "chalk";
import { Emitter } from "./emit/Emitter";

const command = process.argv[2];

switch (command) {
	case "eval": {
		const sourceCode = process.argv[3];

		if (!sourceCode) {
			console.error("Require one string to evaluate.");
			process.exit(0);
		}

		const emitter = new Emitter(sourceCode);

		if (emitter.diagnosticHandler.diagnostics.length !== 0) {
			emitter.diagnosticHandler.diagnostics.forEach((d) => {
				console.error(bgRedBright(black(d.toString())));
			});
			process.exit(0);
		}

		const result = emitter.emitJs();

		console.log(bgGreenBright(black(eval(result).toString())));
		break;
	}
	case "repl": {
		const readline = createInterface({
			input: process.stdin,
			output: process.stdout,
			terminal: false
		});
		let input: string;

		const proc = () =>
			readline.question("> ", (data) => {
				input = data;

				if (input === ":exit") {
					readline.close();
					process.exit(0);
				} else {
					const emitter = new Emitter(input);

					if (emitter.diagnosticHandler.diagnostics.length !== 0) {
						emitter.diagnosticHandler.diagnostics.forEach((d) => {
							console.error(bgRedBright(black(d.toString())));
						});
					} else {
						const result = emitter.emitJs();

<<<<<<< HEAD:CAScript-node-js-runtime/src/lib.ts
						console.log(eval(result).toString());
=======
						console.log(bgGreenBright(black(eval(result).toString())));
>>>>>>> 89a21e72461634cebff7b764825e3454f1f14096:src/lib.ts
					}
					proc();
				}
			});

		proc();
		break;
	}
}
