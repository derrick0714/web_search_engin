<?php

require_once( './loader.php' );



$key_words = $_GET["key"];
$output = query( $key_words);
var_dump($output);
exit(0);

$result = format_result($output);
load_template("query");


function query( $key_words )
{
	$cmd = "demo/helper ".$key_words;
	exec($cmd ,$output);
	return $output;
}

function format_result( $output )
{
	//var_dump($rs);
	$len =count($output);
	$result = array();
	$j=0;
	for( $i = 0; $i < $len; $i+=4)
	{
		$one_result = array();
		$one_result['url'] = $output[$i];
		$one_result['title'] = $output[$i+1];
		$one_result['round'] = $output[$i+2];
		$one_result['bm25'] = $output[$i+3];
		$result[$j++] =$one_result;
	}
	//var_dump($result);

	return $result;
}

?>