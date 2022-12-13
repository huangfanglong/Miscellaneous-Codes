<?php
        session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Title -->
    <title>BLL PARTS</title>
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
                border-color:blue;
                border-width:2px;
                color:black;
                cursor:pointer;
                font-family:monospace;
                font-size:25px;
                font-variant:small-caps;
                text-align:center;
            }
            label
            {
                color:black;
                font-size:35px; 
                font-family:monospace;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            p
            {
                color:black;
                font-size:40px;
                font-family:monospace;
                font-weight:100;
                font-variant:small-caps;
                font-weight:bolder;
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
            echo '<div style="font:monospace;font-size:50px;font-variant:small-caps;font-weight:bold;">Shipping Portal</div>';
            echo '<hr>';
        }
        catch (PDOException $e) 
        {
            echo "Connection failed: " . $e->getMessage();
        }
    ?> 
            
        <form action="#" method="POST">
        <p>View all Orders</p>
        <input type="submit" name="View_Orders" value="View Orders"/>
        </form>
        <?php
        if(isset($_POST["View_Orders"]))//Check for valid input
        {
            // Select All From <ORDERS> Table and display contact info
            $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                    FROM ORDERS, CUSTOMERS
                    WHERE CUSTOMERS.CUSTOMER_ID = ORDERS.CUSTOMER_ID";
            $result = $conn->query($sql);

            // Fetch query results
            $rows = $result->fetchALL(PDO::FETCH_ASSOC);

            // Display Table
            draw_table($rows);
        }

    ?>
    
    <br><br>
    <hr>
    <!-- END ADD NEW PART -->
             
    <!-- START UPDATE INVENTORY -->
    <form action="#" method="POST">
        <p><u>Print Shipping label</u><br><br>Enter order id to print label:</p>
            <input type="number" name="order_id" placeholder="Enter an order id"/>
            <input type="submit" name="sorder" value="Print Label"/>

        </form>
        </p>

        <?php
            if(!empty($_POST["order_id"])&& isset($_POST['sorder']))//Check for valid input
            {

                $ORDER_ID = $_POST['order_id'];

                $sql = "SELECT ORDERS.ORDER_ID,CUSTOMERS.NAME_,CUSTOMERS.EMAIL,ORDERS.ORDER_TOTAL_USD,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE $ORDER_ID = ORDERS.ORDER_ID AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);

                echo "Shipping Label has been printed with the following information.<br>";
                echo 'The order status has been changed to SHIPPED for this order.';


                $ORDER_ID = $_POST['order_id'];

                $sql = "UPDATE ORDERS SET ORDER_STATUS = 'Shipped' WHERE $ORDER_ID = ORDERS.ORDER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                echo '<hr><hr>';
                echo 'Email has been sent to the following customer email.';

                $sql = "SELECT CUSTOMERS.NAME_,CUSTOMERS.EMAIL
                FROM ORDERS, CUSTOMERS
                WHERE $ORDER_ID = ORDERS.ORDER_ID AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                draw_table($rows);
            }
        ?>

    <!-- END UPDATE INVENTORY -->

    </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Homepage.php" style="cursor:pointer;"><h2>Home</h2></a>
            <a href="Receiving.php" style="cursor:pointer;"><h2>Receiving Portal</h2></a>
            <a href="Admin.php" style="cursor:pointer;"><h2>Admin Portal</h2></a>
            <a href="employeeLogin.php" style="cursor:pointer;"><h2>Employee Portal</h2></a>
            <!-- Copyright -->
            <p style="font-family:monospace;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>
