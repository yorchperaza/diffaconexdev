<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
if (!empty($title)) { ?>
  <h3><?php print $title; ?></h3>
<?php
}
foreach ($rows as $id => $row) {
	if (!empty($row)) {
		print $row;
	}
}
?>