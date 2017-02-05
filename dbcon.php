<?php //http://www.dapuralena.com/lampubni/tambah.php?ids=sc0001&pesan=tes to user
$host="localhost";
$user="dapd1669_taufik";
$password="admin123";
$database="dapd1669_lampubni";

$item_per_page = 10;
//$connecDB = mysqli_connect($host, $user, $password,$database)or die('could not connect to database'); //for pagination

if (!defined('SERVERNAME')) define('SERVERNAME', 'localhost');
    if (!defined('USERNAME')) define('USERNAME', 'dapd1669_taufik');
    if (!defined('PASSWORD')) define('PASSWORD', 'admin123');
    if (!defined('DBNAME')) define('DBNAME', 'dapd1669_lampubni');

    $conn = new mysqli(SERVERNAME, USERNAME, PASSWORD, 'dapd1669_lampubni');




ini_set('display_errors',FALSE);
$koneksi=mysql_connect($host,$user,$password);
mysql_select_db($database,$koneksi);
//cek koneksi
if($koneksi){
	echo "berhasil koneksi";
}else{
	echo "gagal koneksi";
}



?>

