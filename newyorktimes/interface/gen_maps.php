<?php

include_once("maps/GoogleMap.php");
include_once("maps/JSMin.php");

$MAP_OBJECT = new GoogleMapAPI(); $MAP_OBJECT->_minify_js = isset($_REQUEST["min"])?FALSE:TRUE;
//setDSN is optional
//$MAP_OBJECT->setDSN("mysql://user:password@localhost/db_name");
//var_dump($MAP_OBJECT);
//$geocodes = $MAP_OBJECT->getGeoCode("Vail, CO");
//var_dump($geocodes);

$geocodes_full = $MAP_OBJECT->geoGetCoordsFull("Vail, CO");


$lines = file('location.data0');
// Loop through our array, show HTML source as HTML source; and line numbers too.
foreach ($lines as $line_num => $line) {
	if($line == "\n")
		continue;	
    $geocodes = $MAP_OBJECT->getGeoCode($line);
    var_dump($geocodes);
   
    echo $line."<br>";
    echo $geocodes['lon']."<br>";
    echo $geocodes['lat']."<br>";
   break;
}

echo "ok!\n";

?>