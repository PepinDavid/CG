var width = parseInt(readline()); // the number of cells on the X axis
var height = parseInt(readline()); // the number of cells on the Y axis
var arrChar = [];//colonnes
for (var i = 0; i < height; i++) {
    var arr = [];//lignes
    var line = readline(); // width characters, each either 0 or .
    for(var j = 0; j < line.length; j++){
        arr.push(line[j]);
    } 
    arrChar.push(arr);
}
for (var i = 0; i < height; i++) //sur chaque colonne
{
    for(var j = 0; j < width; j++) //sur chaque ligne
    { 
        var resp = "";
        if(arrChar[i][j] == 0){
            var cpI = i, cpJ = j;
            resp += j+" "+i+" ";
            while(cpJ < width){
                cpJ++; //on se deplace sur la droite
                if(cpJ >= width){
                    resp +="-1 "+"-1 ";
                }else{
                    if(arrChar[i][cpJ] ==  0){
                        resp += cpJ+" "+i+" ";
                        break;
                    }
                }
                
            }
            while(cpI < height){
                cpI++; //on descend 
                if(cpI >= height){
                    resp += "-1 "+"-1";
                }else{
                    if(arrChar[cpI][j] ==  0){
                        resp += j+" "+cpI+" ";
                        break;
                    }                   
                }
            }
            print(resp); //on affiche le tampon de sorti
        }
    }
}