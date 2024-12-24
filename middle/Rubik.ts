/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

const N: number = parseInt(readline());
const sizeCube = Math.pow(N, 3);
const cubesNotVisible = Math.pow(N - 2, 3)

if (N === 1)
    console.log(1);
else if(N === 2)
    console.log(Math.pow(2, 3))
else
    console.log(Math.pow(N, 3) - Math.pow(N - 2, 3))
