<?php
    session_start();
    $_SESSION['customer_id'] = 1;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Title -->
    <title>Cars 'R' Us || CSCI466 Group Project</title>
</head>
    <body>
        <center>
        <style>
            body
            {
                background-color:lightseagreen;
            }
            h1
            {
                color:#6B0686;
                font-size:75px; 
                font-family:monospace;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            h2
            {
                color:#6B0686;
                font-size:35px; 
                font-family:monospace;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            hr
            {
                color:#6B0686;
            }
        </style>
        <h1>Cars 'R' Us</h1>
        <a href="Cart.php">
            <img src="https://ih1.redbubble.net/image.1697398271.1378/bg,f8f8f8-flat,750x,075,f-pad,750x1000,f8f8f8.jpg" width=500 height=800 alt="Cars 'R' Us Logo" style="cursor:crosshair;"></img>
        </a>
        <a href="Cart.php" style="cursor:crosshair;"><h2>Customers</h2></a>
        <a href="Employee.php" style="cursor:crosshair;"><h2>Employee Portal</h2></a>
        </center>
    </body>
    <center>
        <hr>
        <footer>
            <!-- Copyright -->
            <p style="font-family:monospace;font-size:15px;color:#6B0686;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Daxay Patel, Brandon Romito, Joshua Turgeon</p>
        </footer>
    </center>
</html>
