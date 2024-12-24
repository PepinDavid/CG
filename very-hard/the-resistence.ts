/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * 80% success
 **/

interface IMorseTranslate {
    [key: string]: string
}

const ALPHA_TO_MORSES: IMorseTranslate = {
    'A': '.-',
    'B': '-...',
    'C': '-.-.',
    'D': '-..',
    'E': '.',
    'F': '..-.',
    'G': '--.',
    'H': '....',
    'I': '..',
    'J': '.---',
    'K': '-.-',
    'L': '.-..',
    'M': '--',
    'N': '-.',
    'O': '---',
    'P': '.--.',
    'Q': '--.-',
    'R': '.-.',
    'S': '...',
    'T': '-',
    'U': '..-',
    'V': '...-',
    'W': '.--',
    'X': '-..-',
    'Y': '-.--',
    'Z': '--..',
}

function decryptMorse(morsesDictionnary: string[], morseMessage: string, possibilities: {[key: string]: string[]} = {}): string[] {
    if (morseMessage in possibilities)
        return possibilities[morseMessage];

    if (!morseMessage.length)
        return [''];

    const results: string[] = [];
    const prefixes: string[] = [];

    morsesDictionnary = morsesDictionnary.filter(word => morseMessage.includes(word));

    for (let morseWord of morsesDictionnary) {
        if (morseMessage.startsWith(morseWord)) {
            prefixes.push(morseWord);
        }
    }

    for (let prefix of prefixes) {
        const remainingMessage = morseMessage.slice(prefix.length);
        const subResults = decryptMorse(morsesDictionnary, remainingMessage, possibilities);

        for (let subResult of subResults) {
            results.push(prefix + subResult)
        }
    }

    possibilities[morseMessage] = results;

    return results;
}

const morseMessage: string = readline();
const dictionnary: Array<string> = [];
const N: number = parseInt(readline());
const morsesDictionnary: string[] = [];

for (let i = 0; i < N; i++) {
    const word = readline();

    dictionnary.push(word);
    let wordMorse = '';

    for (let letter of word) {
        wordMorse += ALPHA_TO_MORSES[letter];
    }

    morsesDictionnary.push(wordMorse);
}

const possibilities = {};
const results = decryptMorse(morsesDictionnary, morseMessage, possibilities);

console.log(results.length);
