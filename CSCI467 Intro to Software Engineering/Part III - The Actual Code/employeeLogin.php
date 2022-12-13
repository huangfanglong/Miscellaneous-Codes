<?php
    session_start();

    $NUM = (rand(1,100));

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
        <h1>Employee portal</h1>
        <a href="Cart.php">
            <img src="https://www.thehumancapitalhub.com/images/uploads_articles/12277-All_You_Need_to_Know_About_Employee_Performance_Review_and_Appraisal.jpg" width=1000 height=370 alt="BBL PARTS LOGO" style="cursor:pointer;"></img>
        </a>

        <form method=POST action="">
           <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;" for="Emp">Please enter employee login details to see employee portals:</label>
        <br><br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;" for="Emp">Please enter employee login id:</label>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="elogin">(For demonstation purposes, login id is: 012)</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="enterLog">
        <br><br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;" for="Emp">Please enter employee password:</label>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="elog">(For demonstation purposes, login pass is also: 012)</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="enterPass">
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="submit" name="login" value="Login"/>
            
        <?php
        // Login for employees
            if(isset($_POST['enterLog']) && $_POST['enterLog'] == "012" && isset($_POST['enterPass']) && $_POST['enterPass'] == "012" && isset($_POST['login']))
            {
             echo '<a href="Shipping.php" style="cursor:pointer;"><h2>Shipping Portal</h2></a>
                <a href="Receiving.php" style="cursor:pointer;"><h2>Receiving Portal</h2></a>
                <a href="Admin.php" style="cursor:pointer;"><h2>Admin Portal</h2></a>';
            }
            else if (isset($_POST['enterLog']) && $_POST['enterLog'] != "012" && isset($_POST['login']))
            {
              echo '<br><br>';
              echo 'Incorrect login. Please try again.';
            }
        ?>
        </form> 

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





