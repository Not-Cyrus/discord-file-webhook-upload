import { readFileSync } from 'fs';
import * as readline from 'readline';

let rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

let webHook = '';
let fileName = '';

rl.question('input webhook: ', (answer) => {
    webHook = answer;
    rl.question('input filename: ', (answer) => {
        fileName = answer;
    });
    rl.close();
});

const file = readFileSync(fileName, 'utf8');

let newFile = new File(file, fileName);

fetch(webHook, {
    method: 'POST',
    body: newFile,
    headers: {'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'}
})
