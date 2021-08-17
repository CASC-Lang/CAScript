import * as fs from "fs";
import {Emitter} from "./emit/Emitter";

let file_path = process.argv[2]

let data = fs.readFileSync(file_path, "utf-8");

let emitter = new Emitter(data);
let result = emitter.emitJs();

console.log(result);
console.log(eval(result).toString());