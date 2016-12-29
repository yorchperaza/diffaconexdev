<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?><h2><?php print $title; ?></h2><?php endif; ?>
<?php if (!empty($title)): ?><section class="resource-videos clear"><?php endif; ?>

<?php
foreach ($rows as $id => $row) {
	if ($view->current_display != 'listing')
		echo '<article class="article-highlight">';
	print $row;
	if ($view->current_display != 'listing')
		echo '</article>';
}
?>

<?php if (!empty($title)): ?></section><?php endif; ?>