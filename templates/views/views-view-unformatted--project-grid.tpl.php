<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif;
	//simple 3 row counter
	$ri = 1;
	foreach ($rows as $id => $row): ?>
  <article class="article-highlight<?php if ($ri % 3 == 0 ) { print ' clear-after'; } ?>">
    <?php print $row; ?>
	</article><?php
		$ri++;
	endforeach; ?>
