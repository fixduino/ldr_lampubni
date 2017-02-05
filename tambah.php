 
<?php
   date_default_timezone_set('Asia/Jakarta');
   include("dbcon.php");
   if(isset($_GET['ids'])and($_GET['pesan'])) {
	
   	$s = time ();
	$dt1=date("H:i:s",$s);
    $tgljam =date("Y-m-d H:i:s",$s);
	
	$null="";
    $ids1=$_GET['ids'];
	$pesan1=$_GET['pesan'];
	$on="ON";
	$off="OFF";
	$cmd="";
/*
 	if ($rfid1==$null) {
			echo "data nothing ";
			
		}
	else {
		
	$q = mysql_query("select * from tblampu where lokasi='$rfid1' and kamar='$kamar1'");
	if (mysql_num_rows($q) == 1) {
	//kalau rfid  dan kamar sudah terdaftar di database
	$cmd=$on;
	//redirect ke halaman index
	echo "<br>";echo "<br>";	
	 echo "['lampu:',";
			echo "$idnya
			";
			echo "]";
	echo " ---- ";
			echo "['Kamar:',";
		echo "$kamar1";
		echo "]";
	echo "Akses Diterima "; echo " ---- ";
	 echo "['command:'#";
			echo "$cmd";
			echo "]";
	//header('location:index.php');
	} else {

	$cmd=$off;
	//header('location:login.php?error=4');
	 echo "<br>";echo "<br>";	
     echo "['RFID:',";
		echo "$rfid1";echo " ---- ";
		echo "]";
		echo "['Kamar:',";
		echo "$kamar1";
		echo "]";
	 echo "Akses Ditolak "; echo " ---- ";
	 echo "['command:'#";
			echo "$cmd";
			echo "]";
	 
	}

*/
	 echo "<br>";echo "<br>";	
     echo "['sensorid:',";
		echo "$ids1";echo " ---- ";
		echo "]";
		echo "['pesan:',";
		echo "$pesan1";
		echo "]";


    $Sql="insert into tbterima (sensorid, waktu, pesan)  values ( '".$ids1."','".$tgljam."','".$pesan1."')";
     mysql_query($Sql);
			
	


$token_bot="216353971:AAHyd_ZKzWFAUeSGI2fdkQJfdhmLZYLG0G0";
$data['chat_id']=-1001078936434;
$data['text']=$ids1.":".$pesan1; 
function kirimperintah($perintah,$token_bot,array $keterangan=null) 
{ 
$url="https://api.telegram.org/bot".$token_bot."/"; 
$url.=$perintah."?"; 
$ch=curl_init(); 
curl_setopt($ch,CURLOPT_URL,$url); 
curl_setopt($ch,CURLOPT_RETURNTRANSFER, 1); 
curl_setopt($ch,CURLOPT_POSTFIELDS,$keterangan); 
$output = curl_exec($ch); 
curl_close($ch); 
return $output; 
} 
kirimperintah("sendMessage",$token_bot,$data); 
echo 'done';

	//	}    


	
	
	// $sql1 = sprintf("SELECT kamar FROM tbkamar WHERE rfid LIKE '%s%%'", mysql_real_escape_string($rfid1));
	//	$cari = mysql_query($sql1);
	 

	
	}
    else {

          $result=mysql_query("select * from tbterima order by id desc");//,$link);
    }

?>

