<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
 	$lnk = ltrim($row->{field_field_resources_title_link}[0]['raw']['value'], '/');
	$l_opts = array('attributes' => array('target' => ($row->{field_field_resource_in_new_window}[0]['raw']['value'] === '1' ? '_blank' : '')));
	$grid_image = theme('image', array('path' => $row->{field_field_grid_image}[0]['rendered']['#item']['uri'], 'alt' => $row->field_field_resource_preview_title[0]['raw']['value']));
?>
	<div class="image">
		<!-- <h4>Info</h4> --><?php
		echo image_link($grid_image, $lnk, $l_opts); ?>
	</div>

	<h3><?php echo l($row->field_field_resource_preview_title[0]['raw']['value'], $lnk, $l_opts);?></h3>
	<p><?php echo $row->field_field_resource_short_description[0]['raw']['value'];?></p>
