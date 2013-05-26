
<div class="searchResults" id="searchResults">
    <? 
	$result= $GLOBALS['result'];
	foreach( $result as $key=>$value)
	{
	?>
	<div >
		<p><b>Title:</b><a class="result" href="<?=$value['url']?>"><?=$value['title']?></a> <b>Score:</b><?=$value['bm25']?> </p>
		<p> <b>Date:</b> <?=$value['time']?> <b>Location:</b> <?=$value['location']?></p>
		<p> -----------</p>
	</div>
	<?
	} 
	?>
</div>
<center><h1><b>MAPS</b></h1></center>
 <div id="map-canvas" ></div>


