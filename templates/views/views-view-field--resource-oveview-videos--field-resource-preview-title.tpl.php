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
 $width = $row->{field_field_resources_video}[0]['rendered']['#display']['settings']['width'];
 $height = $row->{field_field_resources_video}[0]['rendered']['#display']['settings']['height'];
 $node_id = $row->nid;
 $url = 'brightcove_dialog/nojs/video/' . $width . '/' . $height . '/node/' . $node_id . '/field_resources_video/0';
?>
<?php
	$l_opts = array('attributes' => array('rel' => 'field_resources_video', 'class' => array('field_resources_video use-ajax')));
	echo '<h3>' . l($row->{field_field_resource_preview_title}[0]['raw']['value'], $url, $l_opts) . '</h3>'; ?>