<!-- <div class="result_top">
	<form class="form-search" action="query.php" method="get">
	  <input name="key" type="text" class="input-xlarge" value=<?php echo "\"".$_GET["key"]."\""?>>
	  <button type="submit" class="btn">Search</button>
	</form>
</div>
<div class="container">
	<? 
	$result= $GLOBALS['result'];
	foreach( $result as $key=>$value)
	{
	?>
	<div class="one_result">
		<p><a href="http://<?=$value['url']?>"><?=$value['title']?></a> BM25:<?=$value['bm25']?></p>
		<p> <?=$value['round']?></p>
	</div>
	<?
	} 
	?>


</div>
 -->

 

<div class="searchResults" id="searchResults">
    <ol class="searchResultsList flush">
    </ol>
</div>


