<?php

require_once( './loader.php' );



$key_words = $_GET["key"];
$type = $_GET["type"];
if( !isset($type))
	$type = "relevance";

$output = query( $key_words, $type);
//var_dump($output);
//exit(0);

$result = format_result($output);
load_template("index");


function query( $key_words, $type )
{
	

	$cmd = "demo/helper ".$type." ".$key_words;
	exec($cmd ,$output);
	return $output;
}

function format_result( $output )
{
	//var_dump($output);
	$len =count($output);
	$result = array();
	$j=0;
	for( $i = 1; $i < $len; $i+=4)
	{
		$one_result = array();
		$one_result['url'] = $output[$i];
		$one_result['bm25'] = $output[$i+1];
		$one_result['time'] = $output[$i+2];
		$one_result['title'] = $output[$i+3];
		
		
		$result[$j++] =$one_result;
	}
	//var_dump($result);

	return $result;
}

?>