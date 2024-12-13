/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

const EARTH_RADIUS = 6371;

function pow2(num: number): number {
    return Math.pow(num, 2);
}

function calculateDistance(longitudeA: number, longitudeB: number, latitudeA: number, latitudeB: number) : number {
    const x = (longitudeB - longitudeA) * Math.cos((latitudeA + latitudeB) / 2);
    const y = latitudeB - latitudeA;

    return Math.sqrt(pow2(x) + pow2(y)) * EARTH_RADIUS;
}

function parseStringToFloat(decimalString: string): number {
    return parseFloat(decimalString.replace(',', '.'))
}

const LON: number = parseStringToFloat(readline());
const LAT: number = parseStringToFloat(readline());
const N: number = parseInt(readline());

let betterAddress = '';
let lessFar = Infinity;

for (let i = 0; i < N; i++) {
    const DEFIB: string = readline();
    const informationsDefib = DEFIB.split(';');
    const lengthInformation = informationsDefib.length;
    const [longitudeString, latitudeString] = informationsDefib.splice(lengthInformation - 2, 2);
    const [_, address] = informationsDefib;
    const longitude = parseStringToFloat(longitudeString);
    const latitude = parseStringToFloat(latitudeString);

    const distance = calculateDistance(LON, longitude, LAT, latitude);

    if (distance < lessFar) {
        lessFar = distance;
        betterAddress = address;
    }
}

// Write an answer using console.log()
// To debug: console.error('Debug messages...');

console.log(betterAddress);
