<?php
    session_start();

    $NUM = (rand(1,1000));

    $_SESSION['customer_id'] = $NUM;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Title -->
    <title>BLL PARTS || CSCI467 Group Project</title>
</head>
    <body>
        <center>
        <style>
            body
            {
                background-color:lightgrey;
            }
            h1
            {
                font-size:75px; 
                font-family:Sans-serif;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            h2
            {
                font-size:35px; 
                font-family:Sans-serif;
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
        <h1>BLL PARTS</h1>
        <a href="Cart.php">
            <img src="https://s3.amazonaws.com/fzautomotive/dealers/60d23e4018a98.jpg" width=1000 height=370 alt="BBL PARTS LOGO" style="cursor:pointer;"></img>
        </a>
        <a href="Cart.php" style="cursor:pointer;"><h2>Customers Catalog</h2></a>
        <a href="employeeLogin.php" style="cursor:pointer;"><h2>Employee Portal</h2></a>
 
        </center>
    </body>
    <center>
        <hr>
        <footer>
            <!-- Copyright -->
            <p style="font-family:monospace;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>
