<?php
    session_start();
    $_SESSION['customer_id'];
    
    $min = 12.00;
    $max = 2500.00;
    $NUM = (rand ($min*10, $max*10) / 10);
    $NUM2 = (rand(1,1000));
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Title -->
    <title>Checkout</title>
</head>
    <body>
    <style>
            body
            {
                background-color:lightgrey;
            }
            hr
            {
                color:blue;
            }
            input
            {
                border-color:black;
                border-width:2px;
                color:black;
                cursor:pointer;
                font-family:Sans-serif;
                font-size:15px;
                font-variant:small-caps;
                text-align:center;
            }
            label
            {
                color:black;
                font-size:35px; 
                font-family:Sans-serif;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            p
            {
                color:black;
                font-size:30px;
                font-family:Sans-serif;
                font-weight:100;
                font-variant:small-caps;
                font-weight:bolder;
            }
            td
            {
                border-color:black;
                border-style:solid;
                border-width:small;
                color:black;
                font-family:Sans-serif;
                font-size:18px;
                font-variant:small-caps;
                font-weight:normal;
                text-align:center;
            }
            th
            {
                border-color:black;
                border-style:solid;
                border-width:medium;
                color:black;
                font-family:Sans-serif;
                font-size:18px;
                font-variant:small-caps;
                text-align:center;
            }
            tr
            {
                border-color:black;
                border-style:solid;
                border-width:medium;
                color:black;
                font-family:Sans-serif;
                font-size:18px;
                font-variant:small-caps;
                height:35px;
                text-align:center;
            }
        </style>
        <center>
            
        <?php
            include("library.php");
            include("login.php");

            error_reporting(E_ALL);
            ini_set("display_errors", 1);            

            try 
            {   // connect to server
                $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
                // set the PDO error mode to exception
                $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                echo '<div style="font:Sans-serif;font-size:50px;font-variant:small-caps;color:black;font-weight:bold;">Checkout<br></div>';
                echo '<hr>';
            }
            catch (PDOException $e) 
            {
                echo "Connection failed: " . $e->getMessage();
            }
        ?>    
        
      

<!--ENTER BILLING INFO -->
        <br>
        <form action="#" method="POST">
            <p>Please Enter Billing Info</p>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Name</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="add_cus_name">
        <br><br>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Email</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="add_cus_Email">
        <br><br>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Mailing Address</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="add_cus_Mail">
        <br><br>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Credit Card Number </label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="number" name="add_cus_Card" maxlength="16">

            <br><br>
        <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Credit Card CVV </label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="number" name="add_cus_cvv" maxlength="3">
        <br><br>
        <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="submit" name="addinfo" value="Confirm order"/>
        
        <?php
        //insert customer info
            if(isset($_POST['addinfo']) && !empty($_POST['add_cus_name'])&& !empty($_POST['add_cus_Email'])&& !empty($_POST['add_cus_Mail'])&& !empty($_POST['add_cus_Card']) && !empty($_POST['add_cus_cvv']))//Check for valid input
            {
                $Customer_Name = $_POST['add_cus_name'];
                $Customer_Email = $_POST['add_cus_Email'];
                $Customer_Mail = $_POST['add_cus_Mail'];
                $Customer_Card = $_POST['add_cus_Card'];
                $Customer_id = $_SESSION['customer_id'];

                //Insert customer biling info into database
                $sql = "INSERT INTO CUSTOMERS(CUSTOMER_ID,NAME_,EMAIL,CARD_NUMBER,MAILING)
                                    VALUES(:id,:name_,:Email,:Card_,:Mail);";

                    $Billing_enter = $conn->prepare($sql);
                        $Billing_enter->execute(['id' => $Customer_id,
                        'name_' => $Customer_Name,
                        'Email' => $Customer_Email,
                        'Card_' => $Customer_Card,
                        'Mail' => $Customer_Mail]);
                echo "-Thank you! You have placed your order.-";
            }

            

            // insert information into orders
            if (isset($_POST['addinfo']) && !empty($_POST['add_cus_name'])&& !empty($_POST['add_cus_Email'])&& !empty($_POST['add_cus_Mail'])&& !empty($_POST['add_cus_Card']) && !empty($_POST['add_cus_cvv']))
            {
                $Customer_id = $_SESSION['customer_id'];
                $ORDER_ID = $_SESSION['customer_id'];
                $ORDER_STAT = 'Ordered';

                
                $sql = "INSERT INTO ORDERS(ORDER_ID,CUSTOMER_ID,ORDER_STATUS,ORDER_TOTAL_USD)
                VALUES(:o_id,:c_id,:o_stat,:o_tot);";

                $Billing_enter = $conn->prepare($sql);
                $Billing_enter->execute(['o_id' => $NUM2,'c_id' => $Customer_id,'o_stat' => $ORDER_STAT,'o_tot' => $NUM]);
    
            }

        ?>
        </form>
        <?php
            unset($_SESSION);
        ?>

        </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Homepage.php" style="cursor:pointer;"><h2>Home</h2></a>
            <!-- Copyright -->
            <p style="font-family:Sans-serif;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>
