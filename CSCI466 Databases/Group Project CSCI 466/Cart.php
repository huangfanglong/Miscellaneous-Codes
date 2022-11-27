<?php
    session_start();
    echo "Your customer id is " . $_SESSION['customer_id'];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Title -->
    <title>Cars 'R' Us</title>
</head>
    <body>
        <style>
            body
            {
                background-color:lightseagreen;
            }
            hr
            {
                color:fuchsia;
            }
            input
            {
                border-color:fuchsia;
                border-width:5px;
                color:black;
                cursor:crosshair;
                font-family:monospace;
                font-size:25px;
                font-variant:small-caps;
                text-align:center;
            }
            label
            {
                color:aliceblue;
                font-size:35px; 
                font-family:monospace;
                font-variant:small-caps;
                font-weight:bolder;
                margin-bottom:auto;
                text-align:center;
            }
            p
            {
                color:aliceblue;
                font-size:40px;
                font-family:monospace;
                font-weight:100;
                font-variant:small-caps;
                font-weight:bolder;
            }
            td
            {
                border-color:blue;
                border-style:dashed;
                border-width:medium;
                color:aliceblue;
                font-family:monospace;
                font-size:25px;
                font-variant:small-caps;
                font-weight:normal;
                text-align:center;
            }
            th
            {
                border-color:blue;
                border-style:dashed;
                border-width:medium;
                color:aliceblue;
                font-family:monospace;
                font-size:25px;
                font-variant:small-caps;
                text-align:center;
            }
            tr
            {
                border-color:blue;
                border-style:dashed;
                border-width:medium;
                color:aliceblue;
                font-family:monospace;
                font-size:25px;
                font-variant:small-caps;
                height:100px;
                text-align:center;
            }
        </style>
        <center>
            
        <?php
            include("library.php");
            include("login.php");				// Change this back to yours if you're testing on your database

            error_reporting(E_ALL);
            ini_set("display_errors", 1);            

            try 
            {   // connect to server
                $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
                // set the PDO error mode to exception
                $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                echo '<div style="font:monospace;font-size:50px;font-variant:small-caps;color:aliceblue;font-weight:bold;">Cars \'R\' Us!<br>Shopping Cart</div>';
                echo '<hr>';
            }
            catch (PDOException $e) 
            {
                echo "Connection failed: " . $e->getMessage();
            }
        ?>    
        
        <!-- START INVENTORY INFO DON'T TOUCH-->
        <form method=POST action="">
        <br><br>
            <input type="submit" value="Get Inventory" name="S" style="background-color: greenyellow">   
        </form>
            
        <?php
            if (isset($_POST['S']))
            {
                $result = $_POST['S'];

                // Select All From INVENTORY Table
                $sql = "SELECT * FROM INVENTORY;";
                $result = $conn->query($sql);
                
                echo "<br>Query successful<br>";

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);

                // Display Table
                draw_table($rows);
            }
            else
            {
                echo "<br><br>";
            }  
            echo '<hr>';
        ?>
        <!-- END INVENTORY INFO DON'T TOUCH -->

        <!-- START ADD TO CART DON'T TOUCH -->
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
            <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, gold, silver, gold);" for="QTY">Quantity:</label>
        <br>
            <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="quantity" value="Enter Quantity">
        <br><br>
            <input type="submit" value="Add To Cart" style="background-color:greenyellow">
            <input type="reset" value="Clear" style="background-color:red;color:aliceblue"> 
        <br>
        
        <?php
            if (isset($_POST['quantity']) && isset($_POST['add_to_cart']))
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
                    $sql = "SELECT * FROM CART_ENTRY WHERE CUSTOMER_ID = :c_id and PART_ID = :p_id;";
                    $check = $conn->prepare($sql);
                    $check->execute(['c_id' => $customer_id,
                                    'p_id' => $_POST['add_to_cart']]);

                    if (($check->rowCount()) == 0)
                    {
                        $sql = "INSERT INTO CART_ENTRY(CUSTOMER_ID,PART_ID,PRODUCT_QUANTITY)
                                    VALUES(:c_id,:p_id,:pqty);";
                        $qty_update_cart = $conn->prepare($sql);
                        $qty_update_cart->execute(['c_id' => $customer_id,
                                                'p_id' => $desired_part_cart,
                                                'pqty' => $desired_qty_cart]);
                    }
                    else
                    {
                        $sql = "UPDATE CART_ENTRY SET PRODUCT_QUANTITY = :pqty 
                                    WHERE PART_ID = :p_id AND CUSTOMER_ID = :c_id";
                        $qty_update_cart = $conn->prepare($sql);
                        $qty_update_cart->execute(['c_id' => $customer_id,
                                                'p_id' => $desired_part_cart,
                                                'pqty' => $desired_qty_cart]);
                    }     
                    echo "CART UPDATED";
                }
                else
                {
                    echo "INSUFFICIENT INVENTORY!";
                }
            }
        ?>

        <br><br><hr>
        </form> 
        <!-- END ADD TO CART DON'T TOUCH-->

        <!-- START CART_ENTRY ADD DON'T TOUCH-->
        <form method=POST action="">
            <p><u>View Cart:</u></p>
        <br>
            <input type="submit" value="View Cart" name="AddCart" style="background-color: greenyellow">   
        </form>
            
        <?php
            if (isset($_POST['AddCart']))
            {
                // $result = $_POST['C'];
            
                // Select All From CART
                $sql = "SELECT INVENTORY.PART_ID,PART_NAME,RETAIL_PRICE_USD,ENTRY_ID,CUSTOMER_ID,PRODUCT_QUANTITY 
                            FROM INVENTORY JOIN CART_ENTRY 
                            WHERE INVENTORY.PART_ID = CART_ENTRY.PART_ID;";
                $result = $conn->prepare($sql);
                
                $result -> execute(['c_id' => $_SESSION['customer_id']]);

                // Fetch query results
                $rows = $result->fetchALL(PDO::FETCH_ASSOC);
                if (count($rows) > 0)
                {
                    echo "<br>Query successful<br>";

                    // Display Table
                    draw_table($rows); 
                }
                else
                {
                    echo "CART IS EMPTY!";
                }
            }
            else
            {
                echo "<br><br>";
            }  
        ?>
        <!-- END CART_ENTRY ADD DON'T TOUCH-->

        <!-- START REMOVE FROM CART DON'T TOUCH -->
        <form method=POST action="">
            <p>Step 1 = Select a Part to Remove:</p>
        
        <?php
            echo '<select name="remove_from_cart">
                  <option value="" disabled>Select A Part</option>';
                
                      
            $sql = "SELECT INVENTORY.PART_ID, PART_NAME, CART_ENTRY.PRODUCT_QUANTITY
                        FROM INVENTORY JOIN CART_ENTRY 
                        WHERE CART_ENTRY.PART_ID = INVENTORY.PART_ID;";
            $parts = $conn->query($sql);
          
            foreach ($parts as $part)
            {
                list($part_id,$name,$quant) = $part;
                echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";

                // foreach ($part as $head=> $value)
                // {
                //     echo "<option value=\"$part_id\">$part_id $name</option>\n";
                // } 
                // echo "<option value=\"$part_id\">$part_id $name</option>\n";

            }
            echo '</select>';
        ?>
                
        <br>
            <p>Step 2 = Select Quantity:</p>
            <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, gold, silver, gold);" for="QTY">Quantity:</label>
        <br>
            <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="update_quantity" value="Enter Quantity">
        <br><br>
            <input type="submit" value="Remove From Cart" style="background-color:greenyellow">
            <input type="reset" value="Clear" style="background-color:red;color:aliceblue"> 
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
        <!-- END REMOVE FROM CART DON'T TOUCH-->

        <!-- START CART_ENTRY EMPTY DON'T TOUCH-->
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

                echo "<br>Query successful<br>";
            }
            else
            {
                echo "<br><br>";
            }  
        ?>
        <!-- END CART_ENTRY EMPTY DON'T TOUCH -->
        
        <?php
            unset($_SESSION);
        ?>

        </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Homepage.php" style="cursor:crosshair;"><h2>Home</h2></a>
            <!-- Copyright -->
            <p style="font-family:monospace;font-size:15px;color:#6B0686;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Daxay Patel, Brandon Romito, Joshua Turgeon</p>
        </footer>
    </center>
</html>
