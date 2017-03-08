var L = parseInt(readline());
var H = parseInt(readline());
var T = readline();
var asciiString = [];
for(var i = 0; i < T.length; i++) 
{
     var nb;
     nb = T.charCodeAt(i);
     printErr(nb)
     if(nb > 64 && nb < 91) //si majuscule
        asciiString[i] = (nb - 65);
    else if(nb > 96 && nb < 123)//si minuscule
        asciiString[i] = (nb - 97);
    else //sinon autre
        asciiString[i] = 26; // correspond au "?"
}
printErr(asciiString)
for (var i = 0; i < H; i++) {
    var ROW = readline();
    //printErr(ROW)
    var s= "";
    for(var j = 0; j < T.length; j++)  //pour chaque lettre du mot
    {
        var nbLettre = asciiString[j]; //on prend le numero de lettre (0 a 25)  
        for(var k = 0; k < L; k++) //dessine la largeur de chaque lettre sur la ligne i
        {            
            //on va cherche le "char" correspond 
            // on doit prendre le numero de la lettre * la largeur pour etre sur
            // le bon char et on avance le curseur a chaque tour pour faire la largeur
            s += ROW[k+L*nbLettre]; 
        }  
    }
    print(s)
}