/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var N = parseInt(readline());
var MESSAGE = readline();
console.error(MESSAGE)

if(N > 0){
    MESSAGE = decode(N, MESSAGE);
}else{
    MESSAGE = encode(Math.abs(N), MESSAGE);
}

console.log(MESSAGE);

function decode(N, message) {
    
    while (N) {
        let copyMessage = message.split('');
        const encodingMessage = [];
        const lengthCuts = []
        let numberOfCutMessage = 1;
        
        while (copyMessage.length) {
            lengthCuts.push(copyMessage.splice(0, numberOfCutMessage).length);
            numberOfCutMessage++;
        }
    
        copyMessage = message.split('');
        lengthCuts.reverse();
    
        while (lengthCuts.length) {
            const counterLetter = lengthCuts[0];
    
            if (lengthCuts.length % 2 === 0) {
                encodingMessage.push(copyMessage.splice(0, counterLetter));
            } else {
                encodingMessage.push(copyMessage.splice(copyMessage.length - counterLetter, counterLetter));
            }
    
            lengthCuts.shift();
        }
    
        message = encodingMessage.reverse().map(v => v.join('')).join('');
        N--;
    }
    
    return message; 
}

function encode(N, message) {
    while (N) {
        const encodingMessage = [];
        const spliceMessage = [];
        let lettersSized = 0;

        message = message.split('');

        while(message.length) {
            lettersSized++;
            spliceMessage.push(message.splice(0, lettersSized))
        }


        for(let i = 0; i < spliceMessage.length; i++) {
            const letters = spliceMessage[i];

            if (i % 2 === 0)
                encodingMessage.push(...letters)
            else
                encodingMessage.unshift(...letters)
        }

        message = encodingMessage.join('');
        N--;
    }

    return message;
}