<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
 if (isset($row->{field_field_resources_title_link}[0]['raw']['value']) && !empty($row->{field_field_resources_title_link}[0]['raw']['value']))
 {
	 $link = $row->{field_field_resources_title_link}[0]['raw']['value'];
	 $l_opts = array('target' => '_blank');
 }
 else
 {
	 $link = 'node/' . $row->nid;
	 $l_opts = array();
 }
$output = html_entity_decode($output, ENT_QUOTES, 'UTF-8');
?>
<h3><?php echo l($output, $link, array('attributes' => $l_opts)); ?></h3>
