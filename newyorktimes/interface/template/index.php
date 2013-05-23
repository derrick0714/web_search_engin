
<div class="searchResults" id="searchResults">
    <? 
	$result= $GLOBALS['result'];
	foreach( $result as $key=>$value)
	{
	?>
	<div >
		<p><a href="<?=$value['url']?>"><?=$value['title']?></a> score:<?=$value['bm25']?> </p>
		<p> time: <?=$value['time']?></p>
		<p> -----------</p>
	</div>
	<?
	} 
	?>
</div>


