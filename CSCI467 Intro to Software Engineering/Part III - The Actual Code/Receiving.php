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
    <title>Receiving Portal</title>
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
            echo '<div style="font:monospace;font-size:50px;font-variant:small-caps;color:aliceblue;font-weight:bold;">Receiving Portal</div>';
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
            $sql = "SELECT DISTINCT PART_NAME
                            FROM INVENTORY WHERE PART_ID = '$part_id';";
            $result = $conn->query($sql);
            
            foreach ($result as $row)
            {
                {
                    list($name,$quant) = $row;
                }
            }

            echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";
            $i++;
        }
        echo '</select>';
        ?>
        
        <br><br>
            <input type="submit" value="View Part" style="background-color:lightblue">   
        </form>
            
        <?php
        if (isset($_POST['part']))
        {
            $result = $_POST['part'];

            $sql = "SELECT * FROM INVENTORY WHERE PART_ID = '$result';";
            $result = $conn->query($sql);

            // Fetch query results
            $rows = $result->fetchALL(PDO::FETCH_ASSOC);

            // Display Table
            draw_table($rows);
        }
        echo "<br><br>";
        echo '<hr>';
        ?> 
    <!-- END SELECT PART TO DISPLAY -->

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
        <p><u>Update Inventory</u><br><br>Step 1 = Select a Part update inventory quantity:</p>
        
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
            $sql = "SELECT DISTINCT PART_NAME
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
                echo "<option value=\"$part_id\">$part_id $name $quant</option>\n";
            }
            $i++;
        } 
        echo '</select>';
    ?>
     
    <p>Step 2 = Enter amount to add to inventory:</p>
        <label style="font-family:monospace;font-size:25px;color:black;font-weight:bolder;background-image:linear-gradient(to bottom right, lightblue, silver, lightblue);" for="QTY">Enter Quantity:</label>
    <br>
        <input style="font-family:monospace;font-size:25px;color:black;text-align:center;background-image:linear-gradient(to bottom, silver, grey, lightgrey);" type="number" name="update_quantity">
    <br><br>
        <input type="submit" value="Update Inventory" style="background-color:lightblue">
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
                $qty_update->execute(['qty' => $desired_qty]);
                echo "QUANTITY UPDATED";
        }
    ?>
    
    <?php
        unset($_SESSION['success_np']);
    ?>

    <br><br>
    <!-- END UPDATE INVENTORY -->

    </center>
    </body>
    <center>
        <footer>
            <hr>
            <a href="Homepage.php" style="cursor:pointer;"><h2>Home</h2></a>
            <a href="Shipping.php" style="cursor:pointer;"><h2>Shipping Portal</h2></a>
            <a href="Admin.php" style="cursor:pointer;"><h2>Admin Portal</h2></a>
            <a href="employeeLogin.php" style="cursor:pointer;"><h2>Employee Portal</h2></a>

            <!-- Copyright -->
            <p style="font-family:monospace;font-size:15px;text-align:center;">Copyright © 2022. All Rights Reserved. Powered by Long Huang, Brandon Romito, Luke Bodnar</p>
        </footer>
    </center>
</html>
