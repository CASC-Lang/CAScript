import * as fs from "fs";
import { Lexer } from "./syntax/Lexer";

let file_path = process.argv[2]

let data = fs.readFileSync(file_path, "utf-8");

let lexer = new Lexer(data);
let lexResult = lexer.lex();

console.log(lexResult);