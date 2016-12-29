<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php
	$i = 1;
	foreach ($rows as $id => $row): ?>
    <article class="article-highlight<?php if($i % 3 == 0) echo ' clear-after';?>">
    <?php print $row; ?>
    </article>
<?php
		$i++;
	endforeach; ?>