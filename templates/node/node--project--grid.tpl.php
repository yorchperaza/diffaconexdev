<?php
/**
 * Template for a Project node in Grid view mode.
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="project__header">

    <?php if (!empty($content['field_project_portfolio'])): ?>
      <?php print render($content['field_project_portfolio']); ?>
    <?php endif; ?>

    <?php if (!empty($content['field_grid_image'])): ?>
      <?php print render($content['field_grid_image']); ?>
    <?php endif; ?>

    <?php if (!empty($content['field_project_industry'])): ?>
      <?php print render($content['field_project_industry']); ?>
    <?php endif; ?>

    <?php if (!empty($content['field_project_size'])): ?>
      <?php print render($content['field_project_size']); ?>
    <?php endif; ?>
  </div>

  <h3>
    <a href="<?php print $node_url; ?>">
      <?php print $title; ?>
    </a>
  </h3>
  <?php print render($content); ?>
</div>
