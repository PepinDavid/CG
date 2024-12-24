/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

const n: number = parseInt(readline());
var inputs: string[] = readline().split(' ');
let counterOfOne = 0;
const arrayBinary: Array<number> = []
for (let i = 0; i < n; i++) {
    const x: number = parseInt(inputs[i]);
    arrayBinary.push(x);

    if(x === 1)
        counterOfOne++;
}

let zeroBeforeMaxOne = 0;

arrayBinary.forEach((num, index) => {
    if(num === 0 && index < counterOfOne)
        zeroBeforeMaxOne++;
});

console.log(zeroBeforeMaxOne);
