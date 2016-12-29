<?php
/**
 * Template for a Homepage V2 node.
 */
?>
<?php if (isset($homepage_banner)): ?>
  <div class="homepage-v2__hero">
    <?php print render($homepage_banner); ?>
  </div>
<?php endif; ?>

<section class="homepage-v2__content <?php print $classes; ?>">
  <?php if (isset($homepage_logos)): ?>
    <div class="homepage-v2__logos">
      <div class="container">
        <?php print $homepage_logos; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['field_homepage_v2_solutions_text'])): ?>
    <div class="homepage-v2__solutions">
      <div class="container">
        <?php print render($content['field_homepage_v2_solutions_head']); ?>
        <?php print render($content['field_homepage_v2_solutions_text']); ?>
        <?php print render($content['field_homepage_v2_solutions_img']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (isset($homepage_metrics)): ?>
    <div class="homepage-v2__metrics">
      <div class="container">
        <?php print $homepage_metrics; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (isset($homepage_industries)): ?>
    <div class="homepage-v2__industries">
      <?php print $homepage_industries; ?>
    </div>
  <?php endif; ?>

  <?php if (isset($homepage_mosaic)): ?>
    <div class="homepage-v2__projects">
      <div class="container">
        <?php print render($content['field_homepage_v2_projects_head']); ?>
      </div>
      <?php print $homepage_mosaic; ?>
    </div>
  <?php endif; ?>

  <?php if (isset($homepage_resources)): ?>
    <div class="homepage-v2__resources">
      <div class="container">
        <?php print render($content['field_homepage_v2_resources_head']); ?>

        <div class="promotions clear">
          <?php print $homepage_resources; ?>
        </div>
      </div>
    </div>
  <?php endif; ?>
</section>
