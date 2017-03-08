var inputs = readline().split(' ');
var lightX = parseInt(inputs[0]); // the X position of the light of power
var lightY = parseInt(inputs[1]); // the Y position of the light of power
var initialTX = parseInt(inputs[2]); // Thor's starting X position
var initialTY = parseInt(inputs[3]); // Thor's starting Y position

// game loop
while (true) {
    var remainingTurns = parseInt(readline()); // The remaining amount of turns Thor can move. Do not remove this line.
    var resp = "";
    // Write an action using print()
    // To debug: printErr('Debug messages...');
    
    if(initialTY > lightY)
    {
        initialTY--;
        resp = "N";
    }
    else if(initialTY < lightY)
    {
        initialTY++;
        resp = "S";
    }
    
    if(initialTX > lightX)
    {
        initialTX--;
        resp += "W";
    }
    else if(initialTX < lightX)
    {
        initialTX++;
        resp += "E";
    }
    // A single line providing the move to be made: N NE E SE S SW W or NW
    print(resp);
}