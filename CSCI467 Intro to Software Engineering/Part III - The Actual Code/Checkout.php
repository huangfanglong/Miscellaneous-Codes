<?php
    session_start();
    $_SESSION['customer_id'];
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
        
      

        <!-- START CART_ENTRY ADD-->
        <?php
                $customer_id = $_SESSION['customer_id'];
                // Select All From CART
                $sql = "SELECT INVENTORY.PART_ID,CUSTOMER_ID,PART_NAME,RETAIL_PRICE_USD,PRODUCT_QUANTITY,RETAIL_PRICE_USD * PRODUCT_QUANTITY AS TOTALS 
                            FROM INVENTORY JOIN CART_ENTRY 
                            WHERE INVENTORY.PART_ID = CART_ENTRY.PART_ID AND $customer_id = CART_ENTRY.CUSTOMER_ID;";
                $result = $conn->prepare($sql);
                
                $result -> execute(['c_id' => $_SESSION['customer_id']]);

                $totalPrice = 0;
                // Fetch query results

                $rows = $result->fetchALL(PDO::FETCH_ASSOC);
                if (count($rows) > 0)
                {
                    // Display Table
                    draw_table($rows); 
                

                echo "<table border=1 cellspacing=1>";
                echo "<tr><th>Shipping and Handling charge</th></tr>";  
                echo  "<tr><td>12.00</td></tr>";
                echo  "</table>";

                $sql = "SELECT SUM(RETAIL_PRICE_USD * PRODUCT_QUANTITY) AS Total_Items FROM INVENTORY JOIN CART_ENTRY WHERE INVENTORY.PART_ID = CART_ENTRY.PART_ID AND $customer_id = CART_ENTRY.CUSTOMER_ID;";

                $result = $conn->prepare($sql);

                $result -> execute(['c_id' => $_SESSION['customer_id']]);

                $rows = $result->fetchALL(PDO::FETCH_ASSOC);
                if (count($rows) > 0)
                {
                draw_table($rows);
                } 
     

                //Get total retail price
                $sql = "SELECT SUM((RETAIL_PRICE_USD * PRODUCT_QUANTITY) + 12) AS Final_Total FROM INVENTORY JOIN CART_ENTRY WHERE INVENTORY.PART_ID = CART_ENTRY.PART_ID AND $customer_id = CART_ENTRY.CUSTOMER_ID;";
 
                $result = $conn->prepare($sql);

                $result -> execute(['c_id' => $_SESSION['customer_id']]);

                $rows = $result->fetchALL(PDO::FETCH_ASSOC);
                if (count($rows) > 0)
                {
                draw_table($rows);
                } 
            }
            else
            {
                echo "CART IS EMPTY!";
            }
        ?>
        <!-- END CART_ENTRY ADD-->


        <!--Buy button for info input-->
        <a href="Billing.php" style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);cursor:pointer;"><h2>Buy Parts</h2></a>
        <br>

        <!-- START REMOVE FROM CART-->
        <form method=POST action="">
            <p>Step 1 = Select a Part to Remove:</p>
        
        <?php
            echo '<select name="remove_from_cart">
                  <option value="" disabled>Select A Part</option>';
                
                      
            $sql = "SELECT INVENTORY.PART_ID, PART_NAME, CART_ENTRY.PRODUCT_QUANTITY
                        FROM INVENTORY JOIN CART_ENTRY 
                        WHERE CART_ENTRY.PART_ID = INVENTORY.PART_ID AND $customer_id = CART_ENTRY.CUSTOMER_ID;";
            $parts = $conn->query($sql);
          
            foreach ($parts as $part)
            {
                list($part_id,$name,$quant) = $part;
                echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";

            }
            echo '</select>';
        ?>
        
        <!--REMOVE PARTS -->
        <br>
            <p>Step 2 = Select Quantity:</p>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter quantity to remove:</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="update_quantity">
        <br><br>
            <input type="submit" value="Remove From Cart" style="background-color:lightblue">
            <input type="reset" value="Clear" style="background-color:red;color:black"> 
        <br>
        
        <?php
            if (isset($_POST['update_quantity']) && isset($_POST['remove_from_cart']))
            {
                $new_desired_qty = $_POST['update_quantity'];
                $new_desired_part = $_POST['remove_from_cart'];
                
                $sql = "SELECT PRODUCT_QUANTITY FROM CART_ENTRY 
                            WHERE PART_ID = '$new_desired_part';";
                $result = $conn->query($sql);            

                foreach ($result as $row)
                {
                    list($prod_in_cart) = $row;
                }
                if ($new_desired_qty <= $prod_in_cart)
                {
                    // UPDATE OLD QTY in PARTS
                    $sql = "UPDATE CART_ENTRY SET PRODUCT_QUANTITY=(PRODUCT_QUANTITY-:rpqty) 
                                WHERE PART_ID = '$new_desired_part';";
                    // Prepare statement
                    $qty_update = $conn->prepare($sql);
                    // execute prepare statement
                    $qty_update->execute(['rpqty' => $new_desired_qty]);
                
                    echo "CART UPDATED";
                }
                else
                {
                    echo "INSUFFICIENT QUANTITY!";
                }
            }
        ?>

        <br><br><hr>
        </form> 
        <!-- END REMOVE FROM CART-->

        <!-- START CART_ENTRY EMPTY-->
        <form method=POST action="">
        <br>
            <input type="submit" value="Empty Cart" name="EmptyCart" style="background-color:red; color:aliceblue">
        </form>
            
        <?php
            if (isset($_POST['EmptyCart']))
            {
                // $result = $_POST['C'];
            
                // Select All From CART
                $sql = "DELETE FROM CART_ENTRY WHERE PRODUCT_QUANTITY > 0;";
                $result = $conn->prepare($sql);
                
                $result -> execute();

                echo "<br>Cart has been emptied. Please return to calalog.<br>";
            }
            else
            {
                echo "<br><br>";
            }  
        ?>
        <!-- END CART_ENTRY EMPTY-->
        
        <?php
            unset($_SESSION);
        ?>

        </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Cart.php" style="cursor:pointer;"><h2>Catalog</h2></a>
            <a href="Homepage.php" style="cursor:pointer;"><h2>Home</h2></a>
            <!-- Copyright -->
            <p style="font-family:Sans-serif;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>
