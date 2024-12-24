/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
enum EDash {
    TOP = '-',
    BOTTOM = '_'
}

enum EType {
    AND = 'AND',
    OR = 'OR',
    XOR = 'XOR',
    NAND = 'NAND',
    NOR = 'NOR',
    NXOR = 'NXOR',
}

const NORMAL_LEVEL = {
    false: '_',
    true: '-',
};

const n: number = parseInt(readline());
const m: number = parseInt(readline());

const inputDigit = {};
const outputDigit = {};

for (let i = 0; i < n; i++) {
    var inputs: string[] = readline().split(' ');
    const inputName: string = inputs[0];
    const inputSignal: string = inputs[1];

    inputDigit[inputName] = inputSignal;
}

const responses: string[] = [];

for (let i = 0; i < m; i++) {
    var inputs: string[] = readline().split(' ');
    let resp = '';
    const outputName: string = inputs[0];
    const type: string = inputs[1];
    const inputName1: string = inputs[2];
    const inputName2: string = inputs[3];
    
    resp += `${outputName} `;

    const iName1 = inputDigit[inputName1];
    const iName2 = inputDigit[inputName2];

    for (let i = 0; i < iName1.length; i++) {
        const dash1 = iName1[i];
        const dash2 = iName2[i];

        switch (type) {
            case EType.AND:
                if (dash1 === dash2)
                    resp += dash1;
                else
                    resp += NORMAL_LEVEL['false'];
                break;

            case EType.OR:
                if (dash1 === dash2)
                    resp += dash1;
                else
                    resp += NORMAL_LEVEL['true'];
                break;

            case EType.XOR:
                if (dash1 === dash2 && dash1 === NORMAL_LEVEL['false'])
                    resp += NORMAL_LEVEL['false'];
                else if (dash1 === dash2 && dash1 === NORMAL_LEVEL['true'])
                    resp += NORMAL_LEVEL['false'];
                else
                    resp += NORMAL_LEVEL['true'];
                break;

            case EType.NAND:
                if (dash1 === dash2 && dash1 === NORMAL_LEVEL['true'])
                    resp += NORMAL_LEVEL['false'];
                else if (dash1 === dash2 && dash1 === NORMAL_LEVEL['false'])
                    resp += NORMAL_LEVEL['true'];
                else
                    resp += NORMAL_LEVEL['true'];
                break;

            case EType.NOR:
                if (dash1 === dash2 && dash1 === NORMAL_LEVEL['true'])
                    resp += NORMAL_LEVEL['false'];
                else if (dash1 === dash2 && dash1 === NORMAL_LEVEL['false'])
                    resp += NORMAL_LEVEL['true'];
                else
                    resp += NORMAL_LEVEL['false'];
                break;
            case EType.NXOR:
                if (dash1 === dash2 && dash1 === NORMAL_LEVEL['false'])
                    resp += NORMAL_LEVEL['true'];
                else if (dash1 === dash2 && dash1 === NORMAL_LEVEL['true'])
                    resp += NORMAL_LEVEL['true'];
                else
                    resp += NORMAL_LEVEL['false'];
                break;
        }
    }

    responses.push(resp);
}

for (const response of responses) {
    console.log(response);
}
