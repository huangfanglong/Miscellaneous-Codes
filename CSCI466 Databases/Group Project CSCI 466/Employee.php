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

        </style>
    <center>
    
    <?php
        include("library.php");
        include("login.php");						// Change this back to yours if you're testing on your database

        error_reporting(E_ALL);
        ini_set("display_errors", 1);

        try 
        {   // connect to server
            $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
            // set the PDO error mode to exception
            $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
            echo '<div style="font:monospace;font-size:50px;font-variant:small-caps;color:aliceblue;font-weight:bold;">Employee Portal</div>';
            echo '<hr>';
        }
        catch (PDOException $e) 
        {
            echo "Connection failed: " . $e->getMessage();
        }
    ?> 
            
    <!-- START SELECT PART TO DISPLAY -->
    <form method=POST action="">
        <p><u>Select a Part to Display:</u></p>
        
    <?php  
        echo '<select name="part">
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
                echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";
            }
            else
            {
                echo "<option value=\"$part_id\" disabled>$part_id $name *OUT OF STOCK!*</option>\n";
            }
            $i++;
        }
        echo '</select>';
        ?>
        
        <br><br>
            <input type="submit" value="View Part" style="background-color:greenyellow">   
        </form>
            
        <?php
        if (isset($_POST['part']))
        {
            $result = $_POST['part'];

            $sql = "SELECT * FROM INVENTORY WHERE PART_ID = '$result';";
            $result = $conn->query($sql);
            
            echo "<br>Query successful<br>";

            // Fetch query results
            $rows = $result->fetchALL(PDO::FETCH_ASSOC);

            // Display Table
            draw_table($rows);
        }
        echo "<br><br>";
        echo '<hr>';
        ?> 
    <!-- END SELECT PART TO DISPLAY -->

    <!-- START ADD NEW PART -->
    <form method=POST action="./NewPart.php">
        <p><u>New Part Information</u></p>
        <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image: linear-gradient(to bottom right, gold, silver, gold);" for="new_part_price">New Part Price:</label>
    <br>
        <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image: linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="new_part_price" value="New Part Price">
    <br><br>
        <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image: linear-gradient(to bottom right, gold, silver, gold);" for="new_pname">New Part Name:</label>
    <br>
        <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image: linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="new_pname" value="New Part Name">
    <br><br>
        <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image: linear-gradient(to bottom right, gold, silver, gold);" for="new_pqty">New Part Quantity:</label>
    <br>
        <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image: linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="new_pqty" value="New Part Quantity">
    <br><br>
        <input type="submit" value="Add Part" style="background-color:greenyellow">
        <input type="reset" value="Clear" style="background-color:red;color:aliceblue"> 
    <br>
    </form>
      
    <?php 
        if (isset($_SESSION['success_np']))
        {
            if ($_SESSION['success_np'] == true)
            {
                echo "<br>PART ADDED SUCCESSFULLY<br>";
            }
        }
    ?>
    
    <br><br>
    <hr>
    <!-- END ADD NEW PART -->
             
    <!-- START UPDATE INVENTORY -->
    <form method=POST action="">
        <p><u>Update Inventory</u><br><br>Step 1 = Select a Part to Add to Inventory:</p>
        
    <?php
        echo '<select name="update_pid">
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
            // $sql = "SELECT DISTINCT PART_NAME FROM INVENTORY WHERE PART_ID = '$part_id';";
            // $result = $conn->query($sql);
        
            // foreach ($result as $row)
            // {
            //     foreach ($row as $head=>$value)
            //     {
            //         $name = $value;
            //     }
            // }

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
                echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";

                // echo "<option value=\"$part_id\" disabled> $part_id $name</option>\n";
            }
            $i++;
        } 
        echo '</select>';
    ?>
     
    <p>Step 2 = Select Quantity:</p>
        <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, gold, silver, gold);" for="QTY">Quantity:</label>
    <br>
        <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="text" name="update_quantity" value="Enter Quantity">
    <br><br>
        <input type="submit" value="Update Inventory" style="background-color:greenyellow">
        <input type="reset" value="Clear" style="background-color:red;color:aliceblue"> 
    <br>
        
    <?php
        if (isset($_POST['update_quantity']) && isset($_POST['update_pid']))
        {
            $desired_qty = $_POST['update_quantity'];
            $desired_part = $_POST['update_pid'];
        
                // UPDATE OLD QTY in PARTS
                $sql = "UPDATE INVENTORY SET QUANTITY=(QUANTITY+:qty) WHERE PART_ID = '$desired_part';";
                // Prepare statement
                $qty_update = $conn->prepare($sql);
                // execute prepare statement
                $qty_update->execute(array(':qty'=>$desired_qty));
                echo "QUANTITY UPDATED";
        }
    ?>
    
    <?php
        unset($_SESSION['success_np']);
    ?>

    <br><br>
    <!-- END UPDATE INVENTORY -->
	
	<!-- VIEW OUTSTANDING CUSTOMER ORDERS AND THEIR INFO, UPDATE THEM, ADD NOTES, ETC -->
	<!-- An order fulfillment page that allows store employees to see details on individual orders, and mark them as shipped, add notes, contact the user, etc. -->
	<hr>
	<!-- See details on each individual orders -->
	<p><u>Order Fulfillment</u><br>
	
	<form method=POST action="">
        <br><br>
            <input type="submit" value="Current Orders" name="Orders" style="background-color: greenyellow">   
        </form>
            
        <?php
            if (isset($_POST['Orders']))
            {
                $result = $_POST['S'];

                // Select All From <ORDERS> Table and display contact info
                $sql = "SELECT ORDERS.ORDER_ID, ORDERS.ORDER_STATUS, ORDERS.PAYMENT_TYPE, ORDERS.ORDER_TOTAL_USD, CUSTOMERS.EMAIL, CUSTOMERS.PHONE_NUMBER, CUSTOMERS.FIRST_NAME, CUSTOMERS.LAST_NAME 
						FROM ORDERS, CUSTOMERS
						WHERE CUSTOMERS.CUSTOMER_ID = ORDERS.CUSTOMER_ID";
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
		
		<!-- Select order -->
		<form method=POST action="">
            <p>Select ongoing orders:</p>
        
        <?php
            echo '<select name="select_order">
                  <option value="" disabled>Select order</option>';
                
                $sql = "SELECT ORDER_ID FROM ORDERS WHERE ORDER_STATUS = 'PROCESSING';";
                $result_enabled = $conn->query($sql);

                foreach ($result_enabled as $row)
                {
                    foreach ($row as $key => $order)
                    {
                        $orders[$order] = 'enabled';
                    }
                }

                $sql = "SELECT ORDER_ID FROM ORDERS WHERE STATUS='SHIPPED' GROUP BY ORDER_ID;";
                $result_disabled = $conn->query($sql);

                foreach ($result_disabled as $row)
                {
                    foreach ($row as $key => $order)
                    {
                        $orders[$order] = 'disabled';
                    }
                }
                ksort($orders, SORT_NATURAL);

            foreach ($orders as $order_id => $active)
            {
                $sql = "SELECT DISTINCT ORDER_ID 
                            FROM ORDERS WHERE ORDER_ID = '$order_id';";
                $result = $conn->query($sql);
            
                foreach ($result as $row)
                {
                    {
                        list($name,$quant) = $row;
                    }
                }

                if ($active == 'enabled')
                {
                    if (isset($selected_order) && $selected_order == $order_id)
                    {
                        echo "<option value=\"$order_id\" selected>$order_id $name $quant</option>\n";
                    }
                    else
                    {
                        echo "<option value=\"$order_id\">$order_id $name $quant</option>\n";
                    }
                }
                else
                {
                    echo "<option value=\"$order_id\" disabled>$order_id $name *OUT OF STOCK!*</option>\n";
                }
            } 
            echo '</select>';
        ?>

	<!-- Add notes -->
	<br>
		<p>Add notes(optional):</p>
		<label for="NOTE">Note:</label>
		<br>
        <input type="text" id="note" name="note" value=" ">
        <br><br>
        <input type="reset" value="Clear" style="background-color:red;color:aliceblue"> 
		<i>Maximum 250 characters</i>
    <br>
	
	<!-- Change order status -->
		<input type="radio" id="shipped" name="status" value="SHIPPED">
		<label for="shipped">SHIPPED</label>
		<input type="radio" id="declined" name="status" value="DECLINED">
		<label for="declined">DECLINED</label>
		<input type="radio" id="refunded" name="status" value="REFUNDED">
		<label for="refunded">REFUNDED</label><br>
		
		<input type="submit" name ="submit" value="Submit" style="background-color:greenyellow">
	
	<?php
        if (isset($_POST['submit']))
        {
            $note = $_POST['note'];
            $selected_order = $_POST['select_order'];
            $customer_id = $_SESSION['customer_id'];
			$status = $_POST['status'];
			
			$prepared = $pdo->prepare			// Add notes
			('
				UPDATE ORDERS
					SET NOTES = :note
					WHERE ORDER_ID = :orderid
			');
			$prepared->execute(array(':note'=>$note, ':orderid'=>$selected_order));

			$prepared = $pdo->prepare			// Update order status
			('
				UPDATE ORDERS
					SET ORDER_STATUS = :status
					WHERE ORDER_ID = :orderid
			');
			$prepared->execute(array(':status'=>$status, ':orderid'=>$selected_order));
			
        }
        ?>

    <br><br><hr>
    </form>

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
