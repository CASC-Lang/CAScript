import * as fs from "fs";
import {CAScript} from "./syntax/Parser";
import Parser = CAScript.Parser;

let file_path = process.argv[2]

let data = fs.readFileSync(file_path, "utf-8");

let parser = new Parser(data);
let result = parser.parse();

console.log(result);