let conwaystyle = (L, loop, arrStr) => {
    loop++;
    if(L > loop){
        let newStr = [];
        let cpt = 0;
        let temp = arrStr[0];
        for(let i = 0; i < arrStr.length; i++){
            if(temp == arrStr[i])
                cpt++;
            else{
                newStr.push(cpt);
                newStr.push(temp);
                cpt = 1;
                temp = arrStr[i];
            }
            if(i+1 == arrStr.length){
                newStr.push(cpt);
                newStr.push(temp);
            }
        }
        return conwaystyle(L, loop, newStr);
    }
    return arrStr;
}

var R = readline();
var L = parseInt(readline());
let loop = 0;
let str = []
str.push(R);
str = conwaystyle(L, loop, str);
str = str.join(" ");
print(str);