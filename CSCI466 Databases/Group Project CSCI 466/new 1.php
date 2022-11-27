<html> 
	<center>
	<body>
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
                $result = $_POST['Orders'];

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
                
                $sql = "SELECT ORDER_ID,CUSTOMER_ID FROM ORDERS WHERE ORDER_STATUS = 'PROCESSING';";	
                $result_enabled = $conn->query($sql);
				
                foreach ($result_enabled as $row)
                {
                    foreach ($row as $key => $order)
                    {
                        $orders[$order] = 'enabled';
                    }
                }

                $sql = "SELECT ORDER_ID, CUSTOMER_ID FROM ORDERS WHERE STATUS='SHIPPED' GROUP BY ORDER_ID;";
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
                $sql = "SELECT ORDERS.ORDER_ID, ORDERS.CUSTOMER_ID, CUSTOMERS.FIRST_NAME FROM ORDERS, CUSTOMERS;";
				
                $result = $conn->query($sql);
            
                foreach ($result as $row)
                {
                    {
                        list($orderid,$cid,$name) = $row;
                    }
                }

                if ($active == 'enabled')
                {
                    if (isset($selected_order) && $selected_order == $order_id)
                    {
                        echo "<option value=\"$order_id\" selected>$order_id $name $cid</option>\n";
                    }
                    else
                    {
                        echo "<option value=\"$order_id\">$order_id $name $cid</option>\n";
                    }
                }
                else
                {
                    echo "<option value=\"$order_id\" disabled>$order_id $name *SHIPPED!*</option>\n";
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