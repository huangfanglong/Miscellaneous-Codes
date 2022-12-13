<html> 
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
	<body>
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
                echo '<div style="font:monospace;font-size:50px;font-variant:small-caps;font-weight:bold;">Admin Portal</div>';
                echo '<hr>';
            }
            catch (PDOException $e) 
            {
                echo "Connection failed: " . $e->getMessage();
            }
        ?>   
	
	<!-- See details on each individual orders -->
	<p><u>Order Management</u><br>
	
        <?php
            
                // Select All From <ORDERS> Table and display contact info
                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
						FROM ORDERS, CUSTOMERS
						WHERE CUSTOMERS.CUSTOMER_ID = ORDERS.CUSTOMER_ID";
                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
    
        ?>
		
        <hr>


		<!-- Select order -->

        <form action="#" method="POST">
            <p>Search for order by order status</p>
            <input type="submit" name="Ordered" value="View Ordered"/>
        </form>
        </p>

        <?php
            if(isset($_POST['Ordered']))//Check for valid input
            {

                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE ORDERS.ORDER_STATUS = 'Ordered' AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            }
            ?>
            <form action="#" method="POST">
            <input type="submit" name="Processing" value="View Processing"/>
            </form>
            <?php
            if(isset($_POST['Processing']))//Check for valid input
            {

                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE ORDERS.ORDER_STATUS = 'Processing' AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            }
            ?>
            <form action="#" method="POST">
            <input type="submit" name="Shipped" value="View Shipped"/>
            </form>
            <?php
            if(isset($_POST['Shipped']))//Check for valid input
            {

                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE ORDERS.ORDER_STATUS = 'Shipped' AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            }

            ?>

        <hr>
        <form action="#" method="POST">
            <p>Search for order by order number</p>
            <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Order Number</label>
            <br><br>
            <input type="number" name="order_id" placeholder="Search by order number"/>

            <input type="submit" name="addpart" value="Search Orders"/>

        </form>
        </p>

        <?php
            if(!empty($_POST["order_id"])&& isset($_POST['addpart']))//Check for valid input
            {

                $ORDER_ID = $_POST['order_id'];

                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE $ORDER_ID = ORDERS.ORDER_ID AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            }
            else
                {

                }
        ?>



        <hr>
        <form action="#" method="POST">
            <p>Search for order by price range</p>
            <br><br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter lowest amount</label>
            <br>
            <input type="number" name="order_id" placeholder="Search by price range"/>

            <br><br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Highest amount</label>
            <br> 
            <input type="number" name="order_id2" placeholder="Search by price range"/>

            <input type="submit" name="addpart" value="Search Orders"/>

        </form>
        </p>

        
        <?php
        // sort orderer by price range
            if(!empty($_POST["order_id"])&& !empty($_POST["order_id2"]) && isset($_POST['addpart']))//Check for valid input
            {

                $ORDER_ID = $_POST['order_id'];
                $ORDER_ID2 = $_POST['order_id2'];

                $sql = "SELECT ORDERS.ORDER_ID,ORDERS.CUSTOMER_ID, ORDERS.ORDER_STATUS, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.NAME_,CUSTOMERS.CARD_NUMBER,CUSTOMERS.MAILING
                FROM ORDERS, CUSTOMERS
                WHERE $ORDER_ID < ORDERS.ORDER_TOTAL_USD AND $ORDER_ID2 > ORDERS.ORDER_TOTAL_USD AND ORDERS.CUSTOMER_ID = CUSTOMERS.CUSTOMER_ID";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);

            }
            else
            {

            }
        ?>
        <hr>





        <hr>
        <form action="#" method="POST">
            <p>Update Charges</p>
            <input type="submit" name="Update" value="View Charges"/>

        </form>
 

        <?php

                if(isset($_POST["Update"]))//Check for valid input
                {
                $sql = "SELECT * FROM CHARGES";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
                }
        ?>

        <form action="#" method="POST">
            <br>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Select charge to change</label>
            <br> <br>
            <input type="text" name="selectcharge" placeholder="Enter charge id to change">
            <input type="text" name="weights" placeholder="Enter new weight">
            <input type="text" name="price" placeholder="Enter new price">

            <input type="submit" name="change" value="Set Charge"/>
        </form>


        <?php

            if(isset($_POST["change"]))//Check for valid input
            {
                $WEIGHTS = $_POST['weights'];
                $PRICE = $_POST['price'];
                $selectcharge = $_POST['selectcharge'];
                

                $sql = "UPDATE CHARGES SET WEIGHT_ = $WEIGHTS WHERE CHARGE = $selectcharge;";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                $sql = "UPDATE CHARGES SET CHARGES_USD = $PRICE WHERE CHARGE = $selectcharge;";

                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                echo "Charge has been changed!";
            }
            else
            {
 
            }
        ?>

        </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Homepage.php" style="cursor:pointer;"><h2>Home</h2></a>
            <a href="Shipping.php" style="cursor:pointer;"><h2>Shipping Portal</h2></a>
            <a href="Receiving.php" style="cursor:pointer;"><h2>Receiving Portal</h2></a>
            <a href="employeeLogin.php" style="cursor:pointer;"><h2>Employee Portal</h2></a>
            <!-- Copyright -->
            <p style="font-family:Sans-serif;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>