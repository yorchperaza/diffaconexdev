<?php

/**
 * @file
 * Template for Homepage V2 hero.
 */
?>
<div class="homepage-hero">
  <div class="homepage-hero__text">
    <?php if (!empty($content['field_banner_heading_1'])): ?>
        <h1>
          <?php print render($content['field_banner_heading_1']); ?>
        </h1>

        <?php if (!empty($content['field_banner_orange_bar'])): ?>
          <?php print render($content['field_banner_orange_bar']); ?>
        <?php endif; ?>
    <?php endif; ?>

    <?php if (!empty($content['field_banner_caption'])): ?>
      <div class="homepage-hero__caption">
        <?php print render($content['field_banner_caption']); ?>
      </div>
    <?php endif; ?>
  </div>

  <?php foreach (array('sm', 'md', 'lg', 'xlg') as $size): ?>
    <?php if (!empty($content['field_hero_image_' . $size])): ?>

      <?php $file = $content['field_hero_image_' . $size]['#items'][0]; ?>
      <?php $file_url = file_create_url($file['uri']); ?>
      <?php $style = "background-image: url($file_url)"; ?>

      <div class="homepage-hero__image visible-<?php print $size; ?>" style="<?php print $style; ?>">
        <?php print render($content['field_hero_image_' . $size]); ?>
      </div>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
