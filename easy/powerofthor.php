<?php

fscanf(STDIN, "%d %d %d %d",
    $lightX, // the X position of the light of power
    $lightY, // the Y position of the light of power
    $initialTX, // Thor's starting X position
    $initialTY // Thor's starting Y position
);

// game loop
while (TRUE)
{
    $resp = '';
    fscanf(STDIN, "%d",
        $remainingTurns // The remaining amount of turns Thor can move. Do not remove this line.
    );

    // Write an action using echo(). DON'T FORGET THE TRAILING \n
    // To debug (equivalent to var_dump): error_log(var_export($var, true));
    if($initialTY > $lightY)
    {
        $initialTY--;
        $resp .= 'N';
    }
    else if($initialTY < $lightY)
    {
        $initialTY++;
        $resp .= 'S';
    }
    
    if($initialTX > $lightX)
    {
        $initialTX--;
        $resp .= 'W';
    }
    else if($initialTX < $lightX)
    {
        $initialTX++;
        $resp .= 'E';
    }
    // A single line providing the move to be made: N NE E SE S SW W or NW
    echo($resp."\n");
}
?>