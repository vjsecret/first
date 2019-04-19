<!DOCTYPE html>
<html>
<head>
<meta charset=utf-8>
<title>php</title>

</head>

<body>
<?php /*?><?php
	echo"<td>test1</td><br>";
	echo"\n";
	echo"<td>test2</td>";
?><?php */?>

<?php
	$name=$_POST["id1"];
	$age=$_POST["id2"];
	$gender=$_POST["id3"];
	echo"姓名 $name <br>";
	echo"年齡 $age <br>";
	echo"性別 $gender <br>";
	
	if ($gender=="man" && $age>=18){
			echo"您該去當兵了<br>";
		}
		else
			echo"您不用當兵<br>";
?>
</body>
</html>