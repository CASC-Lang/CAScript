import { bgGreenBright, bgRedBright, black } from "chalk";
import { createInterface } from "readline";
import { Emitter } from "./emit/Emitter";
import { Parser, SyntaxNode, SyntaxType, Token } from "./syntax/Parser";
import { Evaluator } from "./runtime/runtime";
import { Binder } from "./binding/Binder";

const command = process.argv[2];

switch (command) {
	case "run": {
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
			terminal: false,
		}), evaluator = new Evaluator();
		let input: string,
			showSyntaxTree: boolean = false;

		const repl = () =>
			readline.question("> ", (data) => {
				input = data;

				if (input === ":exit" || input === ":e") {
					readline.close();
					process.exit(0);
				} else if (input === ":showTree" || input === ":st") {
					showSyntaxTree = !showSyntaxTree;
				} else {
					const tree = new Parser(input);
					const result = evaluator.evaluate(input);

					if (result.diagnosticHolder.diagnostics.length !== 0) {
						result.diagnosticHolder.diagnostics.forEach((d) => {
							console.error(bgRedBright(black(d.toString())));

							const prefix = input.substring(0, d.span.start),
								error = input.substring(
									d.span.start,
									d.span.end
								),
								suffix = input.substring(d.span.end);

							process.stderr.write("\t");
							process.stderr.write(prefix);

							process.stderr.write(bgRedBright(black(error)));

							process.stderr.write(suffix);

							console.log();

							process.stderr.write("\t");
							process.stderr.write(" ".repeat(d.span.start));
							process.stderr.write("^".repeat(d.span.len));

							console.log();
						});
					} else {
						console.log(
							bgGreenBright(black(result.resultValue))
						);

						if (showSyntaxTree) {
							printTree(tree.parse());
						}
					}
				}

				repl();
			});

		repl();
		break;
	}
}

function printTree(
	node: SyntaxNode,
	indent: string = "",
	isLast: boolean = true
) {
	process.stdout.write(indent);
	process.stdout.write(isLast ? "└──" : "├──");
	process.stdout.write(SyntaxType[node.type()]);

	if (node instanceof Token) {
		process.stdout.write(" ");
		process.stdout.write(node.literal);
	}

	console.log();

	indent += isLast ? "   " : "│  ";

	node.children().forEach((child, i) => {
		printTree(child, indent, node.children().length - 1 === i);
	});
}
