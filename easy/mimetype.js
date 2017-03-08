var N = parseInt(readline()); // Number of elements which make up the association table.
var Q = parseInt(readline()); // Number Q of file names to be analyzed.
var arrObj = {};
for (var i = 0; i < N; i++) {
    var inputs = readline().split(' ');
    var EXT = inputs[0].toLowerCase(); // file extension
    var MT = inputs[1]; // MIME type.
    arrObj[EXT] = MT;
}
for (var i = 0; i < Q; i++) {
    var FNAME = readline(); // One file name per line.
    FNAME = FNAME.toLowerCase();
    var index = FNAME.lastIndexOf(".");
    if(index != -1){
        FNAME = FNAME.substr(index+1, FNAME.length-1);
        if(arrObj[FNAME] !== undefined)
            print(arrObj[FNAME]);
        else
            print('UNKNOWN');
    }else{
        print('UNKNOWN');
    }
}