/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

function PGCD(x, y): number {
    const remainders: number[] = []
    let X = Math.abs(x);
    let Y = y;
    let remainder = X % Y;

    while (remainder !== 0) {
        X = Y;
        Y = remainder;

        remainders.push(remainder);

        remainder = X % Y;
    }

    return remainders.pop()!;
}

function isInteger(x, y) {
    return (x / y).toString().split('.').length === 1;
}

function response(x, y) {
    if (y === 0)
        return 'DIVISION BY ZERO';

    if (x === 0)
        return '0';

    if (x < 0 && y < 0) {
        x = Math.abs(x);
        y = Math.abs(y);
    } else if (y < 0 && x > 0) {
        x = -x;
        y = Math.abs(y);
    }

    const quotient = x / y;

    if (isInteger(x, y))
        return (quotient).toString();

    let divisor = PGCD(x, y);
    const [integerPart, decimalPart] = (quotient).toString().split('.');

    if (divisor > 1) {
        console.error(`x: ${x}, y ${y}, divisor: ${divisor}`)

        if (isInteger(x, divisor))
            x /= divisor;

        if (isInteger(y, divisor))
            y /= divisor;
    }

    const xPart = Math.round(y * parseFloat(`0.${decimalPart}`))

    if (parseInt(integerPart) !== 0)
        return `${integerPart} ${xPart}/${y}`;
    else
        return `${x < 0 ? -xPart : xPart}/${y}`;
}

const N: number = parseInt(readline());

for (let i = 0; i < N; i++) {
    const xY: string = readline();
    const [x, y] = xY.split('/').map(v => parseInt(v));

    console.log(response(x, y))
}

