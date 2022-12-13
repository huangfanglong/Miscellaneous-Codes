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
                echo '<div style="font:Sans-serif;font-size:50px;font-variant:small-caps;color:black;font-weight:bold;">BLL PARTS CATALOG<br></div>';
                echo '<hr>';
            }
            catch (PDOException $e) 
            {
                echo "Connection failed: " . $e->getMessage();
            }
        ?>    
        
        <!-- START INVENTORY-->
        <?php

                // Select All From INVENTORY Table
                $sql = "SELECT PART_ID,PART_NAME,RETAIL_PRICE_USD,DESCRIPTION_,QUANTITY FROM INVENTORY;";
                $result = $conn->query($sql);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            echo '<hr>';
        ?>
        <!-- END INVENTORY -->

        <!-- START ADD TO CART -->
        <form method=POST action="">
            <p>Step 1 = Select a Part to Buy:</p>
        
        <?php
            echo '<select name="add_to_cart">
                  <option value="" disabled>Select A Part</option>';
                
                $sql = "SELECT PART_ID FROM INVENTORY WHERE QUANTITY!=0;";
                $result_enabled = $conn->query($sql);

                foreach ($result_enabled as $row)
                {
                    foreach ($row as $key => $item)
                    {
                        $parts[$item] = 'enabled';
                    }
                }

                $sql = "SELECT PART_ID FROM INVENTORY WHERE QUANTITY=0 GROUP BY PART_ID;";
                $result_disabled = $conn->query($sql);

                foreach ($result_disabled as $row)
                {
                    foreach ($row as $key => $item)
                    {
                        $parts[$item] = 'disabled';
                    }
                }
                ksort($parts, SORT_NATURAL);

            $i = 1;
            foreach ($parts as $part_id => $active)
            {
                $sql = "SELECT DISTINCT PART_NAME, QUANTITY 
                            FROM INVENTORY WHERE PART_ID = '$part_id';";
                $result = $conn->query($sql);
            
                foreach ($result as $row)
                {
                    {
                        list($name,$quant) = $row;
                    }
                }

                if ($active == 'enabled')
                {
                    if (isset($desired_part) && $desired_part == $part_id)
                    {
                        echo "<option value=\"$part_id\" selected>$part_id $name $quant</option>\n";
                    }
                    else
                    {
                        echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";
                    }
                }
                else
                {
                    echo "<option value=\"$part_id\" disabled>$part_id $name *OUT OF STOCK!*</option>\n";
                }
                $i++;
            } 
            echo '</select>';
        ?>
        
        <br>
            <p>Step 2 = Select Quantity:</p>
            <label style="font-family:Sans-serif;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Quantity:</label>
        <br>
            <input style="font-family:Sans-serif;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="quantity">
        <br><br>
            <input type="submit" value="Add To Cart" style="background-color:lightblue">
            <input type="reset" value="Clear" style="background-color:red;color:black"> 
        <br>
        
        <?php
            if (!empty($_POST['quantity']) && isset($_POST['add_to_cart']))
            {
                $desired_qty_cart = $_POST['quantity'];
                $desired_part_cart = $_POST['add_to_cart'];
                $customer_id = $_SESSION['customer_id'];

                $sql = "SELECT QUANTITY FROM INVENTORY 
                            WHERE PART_ID = '$desired_part_cart';";
                $result = $conn->query($sql);            

                foreach ($result as $row)
                {
                    list($prod_in_stock) = $row;
                }
                
                if ($desired_qty_cart <= $prod_in_stock)
                {
                        $sql = "INSERT INTO CART_ENTRY(CUSTOMER_ID,PART_ID,PRODUCT_QUANTITY)
                                    VALUES(:c_id,:p_id,:pqty);";
                        $qty_update_cart = $conn->prepare($sql);
                        $qty_update_cart->execute(['c_id' => $customer_id,
                                                'p_id' => $desired_part_cart,
                                                'pqty' => $desired_qty_cart]);
      
                    echo "CART UPDATED";
                }
                else
                {
                    echo "INSUFFICIENT INVENTORY!";
                }
            }
        ?>

        <br><br><hr>
        <a href="Checkout.php" style="font-family:Sans-serif;font-size:25px;text-align:center;cursor:pointer;"><h2>Checkout</h2></a>
        </form> 
        <!-- END ADD TO CART-->
        
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
