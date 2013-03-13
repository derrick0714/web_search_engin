<?php


function load_template( $page )
{
	require_once(TEMPLEATE."header.php");
	require_once(TEMPLEATE.$page.".php");
	require_once(TEMPLEATE."footer.php");
}

?>