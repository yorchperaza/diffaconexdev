<?php

/**
 * @file
 * Default theme implementation for field collection items.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) field collection item label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-field-collection-item
 *   - field-collection-item-{field_name}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="hero">
  <div class="hero__text">
    <?php if (!empty($content['field_hero_title'])): ?>
      <h1 class="hero__title">
        <?php print render($content['field_hero_title']); ?>
      </h1>
    <?php endif; ?>

    <?php if (!empty($content['field_hero_subtitle'])): ?>
      <h2 class="hero__subtitle">
        <?php print render($content['field_hero_subtitle']); ?>
      </h2>
    <?php endif; ?>
  </div>

  <div class="hero__logos">
    <div class="container">
      <?php // Use the same logos as the homepage. ?>
      <?php $hero_logos = aconex_logo_logic(); ?>
      <?php print $hero_logos['customer_logos']; ?>
    </div>
  </div>

  <?php foreach (array('sm', 'md', 'lg', 'xlg') as $size): ?>
    <?php if (!empty($content['field_hero_image_' . $size])): ?>
      <div class="hero__image visible-<?php print $size; ?>">
        <?php print render($content['field_hero_image_' . $size]); ?>
      </div>
    <?php endif; ?>
  <?php endforeach; ?>

  <?php print render($content); ?>
</div>
