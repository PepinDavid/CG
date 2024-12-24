/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
var inputs: string[] = readline().split(' ');
let start: number = parseInt(inputs[0]);
const n: number = parseInt(inputs[1]);

for (let i = 0; i < n; i++) {
    let count = start.toString(2).split('').reduce((acc, b) => acc += b === '0' ? 4 : 3, 0);

    if (start === count)
        break;

    start = count;
}

console.log(start);
