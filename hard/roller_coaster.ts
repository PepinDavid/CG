/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var inputs: string[] = readline().split(' ');
const L: number = parseInt(inputs[0]);
let C: number = parseInt(inputs[1]);
const N: number = parseInt(inputs[2]);
let groups: Array<number> = []
for (let i = 0; i < N; i++) {
    groups.push(parseInt(readline()));
}

let gain = 0;
let queuePosition = 0;
const cache = {};

while (C > 0) {
    if(cache[queuePosition] !== undefined) {
        let [tourGain, nextPosition] = cache[queuePosition];

        gain += tourGain;
        queuePosition = nextPosition;
    } else {
        let tourGain = 0;
        let occupiedSeats = 0;
        let initialPosition = queuePosition;

        while (occupiedSeats + groups[queuePosition] <= L) {
            occupiedSeats += groups[queuePosition];
            tourGain += groups[queuePosition];
            queuePosition = (queuePosition + 1) % N;

            if (queuePosition === initialPosition) break;
        }

        cache[initialPosition] = [tourGain, queuePosition];
        gain += tourGain;
    }

    C--;
}


console.log(gain);
