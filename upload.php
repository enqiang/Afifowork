<?php
if ($_FILES["file"]["error"] > 0){
	echo "Error: " . $_FILES["file"]["error"] . "<br />";
}else{
	$mysql_server_name='localhost';
	$mysql_username='userx';
	$mysql_password='';
	$mysql_database='nodechat';
	$conn=mysql_connect($mysql_server_name,$mysql_username,$mysql_password,$mysql_database);
	if (!$conn)
  	{
 	 	die('Could not connect: ' . mysql_error());
  	}
	mysql_select_db($mysql_database,$conn);
	//get the filename without extension.
	$filename=str_replace(strrchr($_FILES["file"]["name"], "."),"",$_FILES["file"]["name"]);
	$sql="INSERT INTO file_table (name , path) VALUES ('".$filename."','savefile/".$_FILES["file"]["name"]."')";
	if($result=mysql_query($sql)){
		echo "已插入数据库";
	}else{
		echo "插入数据库失败";
		echo mysql_error();
	}
	mysql_close($conn);
	
  	echo "Upload: " . $_FILES["file"]["name"] . "<br />";
  	echo "Type: " . $_FILES["file"]["type"] . "<br />";
  	echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
  	//echo "Stored in: " . $_FILES["file"]["tmp_name"] . "<br />";
  	
  	if (file_exists("savefile/" . $_FILES["file"]["name"])){
      	echo $_FILES["file"]["name"] . " already exists.";
    }else{
      	move_uploaded_file($_FILES["file"]["tmp_name"],"savefile/".$_FILES["file"]["name"]);
      	echo "Stored in: " . "savefile/" . $_FILES["file"]["name"];
    }
}
?>
