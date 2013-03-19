<?php 
// Connects to Database 
$server="";
$username="";
$password="";
$database="";
$connection = mysql_connect($server, $username, $password) or die(mysql_error()); 
mysql_select_db($database) or die(mysql_error()); 
?>