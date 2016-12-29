<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<section class="content<?php echo ($view->current_display != 'listing') ? ' with-headline' : ''; ?> clear<?php print $classes; ?>">
	<div class="container clear">
		<?php if ($view->current_display != 'listing') : ?><h2><?php echo t('Videos'); ?></h2><?php endif; ?>
	
		<?php print render($title_prefix); ?>
		<?php if ($title): ?>
			<?php print $title; ?>
		<?php endif; ?>
		<?php print render($title_suffix); ?>
		<?php if ($header): ?>
			<div class="view-header">
				<?php print $header; ?>
			</div>
		<?php endif; ?>
	
		<?php if ($rows): ?>
			 <?php print $rows; ?>
		<?php endif; ?>
	
		<?php
		if($view->current_display != 'listing'):
			echo l(t('View all videos'), 'node/1312', array('attributes' => array('class' => array('button'))));
		elseif ($pager): ?>
			<?php print $pager; ?>
		<?php endif; ?>
	
		<?php if ($more): ?>
			<?php print $more; ?>
		<?php endif; ?>
	
		<?php if ($footer): ?>
			<?php print $footer; ?>
		<?php endif; ?>
	</div>
</section>