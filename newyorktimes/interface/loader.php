<?php

error_reporting( E_CORE_ERROR | E_CORE_WARNING | E_COMPILE_ERROR | E_ERROR | E_WARNING | E_PARSE | E_USER_ERROR | E_USER_WARNING | E_RECOVERABLE_ERROR );

/** Define ABSPATH as this file's directory */
define( 'ABSPATH', dirname(__FILE__) . '/' );
define( 'WSE_INC', ABSPATH.'include/' );
define( 'TEMPLEATE',ABSPATH. 'template/' );
define( 'CSS',  './css/' );
define( 'IMG', './img/' );
define( 'JS', './js/' );
//require_once( ABSPATH . WSE_INC . '/load.php' );
//require_once( ABSPATH . WSE_INC . '/version.php' );

function load_template( $page )
{
	//echo ABSPATH;
	load_header();
	require_once(TEMPLEATE.$page.".php");
	load_footer();
}

function load_header()
{
	global $navigation;
	$navigation = array(
	    "Search" => "./index.php",
	    "Image" => "#",
	    "Maps" => "#",
	    "Play" => "#",
	    "Youtube" => "#",
	    "Github" => "#",
	    "About" => "#"
	);

	require_once(TEMPLEATE."header.php");
}

function load_footer()
{
	require_once(TEMPLEATE."footer.php");
}
?>