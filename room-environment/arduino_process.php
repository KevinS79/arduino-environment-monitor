<?php
	$time = $_GET['time'];
	$temp = $_GET['temp'];
	$humidity = $_GET['humidity'];

	include('datalogin.php');

	$query = "INSERT INTO room_temp (temperature, humidity) VALUES ($temp, $humidity)";

	mysql_query($query) or die("Query Error: " . mysql_error());
	
	mysql_close($connection);

	echo "DATA RECIEVED BY SCRIPT...\n";
	echo "temp: $temp\n";
	echo "humidity: $humidity\n";
	echo "SUCCESS\n";
?>