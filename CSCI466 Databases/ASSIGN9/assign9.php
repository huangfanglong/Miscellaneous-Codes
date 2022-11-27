<html>
<?php
	include('login.php');
	include('library.php');
	
	try 
	{ // if something goes wrong, an exception is thrown
		$dsn = "mysql:host=courses;dbname=z1942308";
		$pdo = new PDO($dsn, $username, $password);
		$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		
		$rs = $pdo->query("SELECT * FROM S;");
		$rows = $rs->fetchALL(PDO::FETCH_ASSOC);
		
		echo "<p><b>1. Supplier details</b></p> \n";
		//Req. 1 Show all of the suppliers and their details. Show them neatly in a table. (10 pts)
		draw_table($rows);
	
		$rs = $pdo->query("SELECT * FROM P;");
		$rows = $rs->fetchALL(PDO::FETCH_ASSOC);
		
		echo "<p><b>2. Part details</b></p> \n";
		//Req. 2 Show all of the parts and their details. (10 pts)
		draw_table($rows);	
	}
	
	catch(PDOexception $e) 
	{ // handle that exception
		echo "Connection to database failed: " . $e->getMessage();
	}
?>

	<p>
	<form action="#" method="post">
		<b>3. Select Part</b>
		<select name="Part">
			<option></option>
			<option value="1">1</option>
			<option value="2">2</option>
			<option value="3">3</option>
			<option value="4">4</option>
			<option value="5">5</option>
			<option value="6">6</option>
			
			<input type="submit" name="submit1" value="Show suppliers"/><br>
		</select>
	</form>
	</p>
	
	<?php
		if(isset($_POST['submit1']))
		{
			$selectedpart = $_POST['Part'];
			echo "Part: " . $selectedpart;
			
			$prepared3 = $pdo->prepare
				('
				SELECT SP.S,SP.QTY,P.PNAME,P.WEIGHT,P.COLOR FROM SP,P WHERE SP.P = :part AND P.P = :part
				');
			$prepared3->execute(array(':part' => $selectedpart));
			$p = $prepared3->fetchAll(PDO::FETCH_ASSOC);
			draw_table($p);
		}
	?>

	<p>
	<form action="#" method="post">
		<b>4. Select Supplier</b>
		<select name="Supplier">
			<option></option>
			<option value="1">1</option>
			<option value="2">2</option>
			<option value="3">3</option>
			<option value="4">4</option>
			<option value="5">5</option>
			
			<input type="submit" name="submit" value="Show parts"/><br>
		</select>
	</form>
	</p>
	
	<?php
		if(isset($_POST['submit']))
		{
			$selectedsupplier = $_POST['Supplier'];
			echo "Supplier: " . $selectedsupplier;
			
			$prepared4 = $pdo->prepare('SELECT SP.P,SP.QTY,S.SNAME,S.STATUS,S.CITY FROM SP,S WHERE SP.S = ? AND S.S= ?');
			$prepared4->execute(array($selectedsupplier,$selectedsupplier));
			$s = $prepared4->fetchAll(PDO::FETCH_ASSOC);
			draw_table($s);
		}
	?>
	
<!--5 There must be a way to select a part and a supplier and “buy” some number of parts from them, reducing the quantity they
have left to supply by the amount “bought”. (Don’t worry about tracking the purchases, just adjust the quantity appropriately.)
(15 pts)-->
	<p>
	<form action="#" method="post">
		<label for="supplier"><b>5. S:</b></label>
		<input type="text" id="supplier" name="supplier">
		<label for="part"><b>P:</b></label>
		<input type="text" id="part" name="part">
		<label for="quantity"><b>Quantity:</b></label>
		<input type="text" id="quantity" name="quantity">
		
		<input type="submit" name="buy" value="BUY"/>
		<input type="reset" value="Clear entry"></button><br>
		<i>(Enter only the designation number followed by part number then followed by at max 3 digit quantity; e.g: S: 1 P: 2 Quantity: 150...pls)</i><br>
	</form>
	</p>
	
	<?php
		if(isset($_POST['buy']))
		{
			$selectedsupplier = $_POST['supplier'];
			$selectedpart = $_POST['part'];
			$selectedquantity = $_POST['quantity'];
			
			$prepared5 = $pdo->prepare
			('
				UPDATE SP
					SET QTY = QTY - :qty
					WHERE S = :supp AND P = :part
			');
			$prepared5->execute(array(':qty'=>$selectedquantity, ':supp'=>$selectedsupplier, ':part'=>$selectedpart));
			
			$prepared6 = $pdo->prepare
			('
				SELECT S,P,QTY FROM SP WHERE S = :supp AND P = :part
			');
			$prepared6->execute(array(':supp'=>$selectedsupplier, ':part'=>$selectedpart));
			$d = $prepared6->fetchAll(PDO::FETCH_ASSOC);
			echo "Purchase kompleted\n";
			draw_table($d);
		}
	?>
	
<!--6 There must be a form that allows a user to add a new part to the database. (15 pts)-->
	<p>
	<form action="#" method="post">		
		<label for="partname"><b>6. Part Name:</b></label>
		<input type="text" id="partname" name="partname">	
		
		<label for="partcolor"><b>Part Color:</b></label>
		<input type="text" id="partcolor" name="partcolor">	
		
		<label for="partweight"><b>Part Weight:</b></label>
		<input type="text" id="partweight" name="partweight">
		
		<input type="submit" name="add" value="Add"/>
		<input type="reset" value="Clear entry"></button><br>
		<i>Note: 'Part Name' can't be longer than 5, 'Part Color' can't be longer than 5, 'Part Weight' can't be longer than 2</i></p>
	</form>
	
	<?php
		if(isset($_POST['add']))
		{
			$addname = $_POST['partname'];
			$addcolor = $_POST['partcolor'];
			$addweight = $_POST['partweight'];
			
			$prepared7 = $pdo->prepare
			('
				INSERT INTO P (PNAME,COLOR,WEIGHT)
					VALUES(	:name,
							:color,
							:weight	)
			');
			$prepared7->execute(array(':name'=>$addname,':color'=>$addcolor,':weight'=>$addweight));
			
			$rs2 = $pdo->query("SELECT * FROM P;");
			$a = $rs2->fetchALL(PDO::FETCH_ASSOC);
			echo "Added\n";
			draw_table($a);
		}
	?>
	
<!--7 There must be a form that allows a user to choose a supplier and a part, specifying an appropriate quantity, and put the
information into the database that indicates that the chosen supplier supplies that many of the chosen part. (15 pts)-->
	<p>
	<form action="#" method="post">
		<label for="supp1"><b>7. S:</b></label>
		<input type="text" id="supp1" name="supp1">
		<label for="part1"><b>P:</b></label>
		<input type="text" id="part1" name="part1">
		<label for="quantity1"><b>Quantity:</b></label>
		<input type="text" id="quantity1" name="quantity1">
		
		<input type="submit" name="set" value="Set"/>
		<input type="reset" value="Clear entry"></button><br>
		<i>(Enter only the designation number followed by part number then followed by at max 3 digit quantity; e.g: S: 1 P: 2 Quantity: 150...pls)</i><br>
	</form>
	</p>
	
	<?php
		if(isset($_POST['set']))
		{
			$selectedsupplier1 = $_POST['supp1'];
			$selectedpart1 = $_POST['part1'];
			$selectedquantity1 = $_POST['quantity1'];
			
			$prepared8 = $pdo->prepare
			('
				UPDATE SP
					SET QTY = :quantity1
					WHERE S = :supp1 AND P = :part1
			');
			$prepared8->execute(array(':part1'=>$selectedpart1, ':quantity1'=>$selectedquantity1, ':supp1'=>$selectedsupplier1));
			
			$rs3 = $pdo->query("SELECT * FROM SP;");
			$ch = $rs3->fetchALL(PDO::FETCH_ASSOC);
			echo "Adjusted\n";
			draw_table($ch);
		}
	?>	
	
</html>