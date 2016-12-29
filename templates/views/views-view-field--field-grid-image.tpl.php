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
 	if (isset($row->field_field_article_date[0]['raw']['value']) && !empty($row->field_field_article_date[0]['raw']['value'])) {
		$date = date('M j, Y', strtotime($row->field_field_article_date[0]['raw']['value']));
	} else {
		$date = '';
	}
?>
	<div class="image">
		<?php
		$g_target = NULL;
		if(isset($row->{field_field_resources_title_link}))
		{
			$g_link = $row->{field_field_resources_title_link}[0]['raw']['value'];
			$g_target = $row->{field_field_resource_in_new_window}[0]['raw']['value'];
		}
		else
		{
			$g_link = 'node/'.$row->nid;
		}
		$l_opts = array('target' => ($g_target == '1' ? '_blank' : ''));
		$grid_image = theme('image', array('path' => $row->{field_field_grid_image}[0]['rendered']['#item']['uri'], 'alt' => ''));
		echo image_link($grid_image, $g_link, $l_opts); ?>
		<?php if (isset($row->field_field_article_date[0]['raw']['value']) && !empty($row->field_field_article_date[0]['raw']['value'])) : ?><h4><time datetime="<?php echo date('Y-m-d', strtotime($row->field_field_article_date[0]['raw']['value'])); ?>"><?php echo strtoupper($date); ?></time></h4><?php endif; ?>
	</div>