/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
type Matrice2D = Array<Array<number>>;

enum RugbyScore {
    'TRY' = 5,
    'TRANSFORMATION' = 2,
    'PENALTY' = 3,
};

enum a {
    'ONLY_PENALTY',
    'TRY_AND_PENALTY',
    'ALL',
};

const combinationsScore: Matrice2D = [];

function calculateScore(score: number, typeCombination: RugbyScore): [number, number] {
    const quotient = Math.floor(score / typeCombination);
    const remainder = score % typeCombination;

    return [quotient, remainder];
}

let score: number = parseInt(readline());

let [scorePenalty, remainderPenalty] = calculateScore(score, RugbyScore.PENALTY);

if (!remainderPenalty)
    combinationsScore.push([0, 0, scorePenalty]);

while (scorePenalty) {
    scorePenalty--;
    remainderPenalty += RugbyScore.PENALTY;

    let [scoreTry, remainderTry] = calculateScore(remainderPenalty, RugbyScore.TRY);

    while (scoreTry) {
        let [scoreTransformation, remainderTransformation] = calculateScore(remainderTry, RugbyScore.TRANSFORMATION);

        if (!remainderTransformation && scoreTry >= scoreTransformation)
            combinationsScore.push([scoreTry, scoreTransformation, scorePenalty]);

        scoreTry--;
        remainderTry += RugbyScore.TRY;
    }
}

const possibleScores = combinationsScore.sort(([aTry, aTrans, aPen],[bTry, bTrans, bPen]) => aTry < bTry ? -1 : aTry > bTry ? 1 : 0)

for (let score of possibleScores) {
    console.log(score.join(' '));
}
