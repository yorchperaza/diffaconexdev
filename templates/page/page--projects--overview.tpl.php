	<?php render($page['content']['metatags']); ?>
  <?php print render($page['header']); //this could be used for the banner below ?>

  <main data-role="content">
		<section class="banner map">
			<div class="container clear">
				<?php if (!empty($page['banner']['head1'])) : ?><h2><?php echo $page['banner']['head1']; ?></h2><?php endif; ?>
				<?php if (!empty($page['banner']['head2'])) : ?><h3><?php echo $page['banner']['head2']; ?></h3><?php endif; ?>
				<?php if (!empty($page['banner']['caption'])) : ?><figcaption><?php echo $page['banner']['caption']; ?></figcaption><?php endif; ?>
				<?php if (!empty($page['banner']['cta_button'])) echo $page['banner']['cta_button']; ?>
			</div>

	    <div class="google-map"><?php
	    	print render($page['google_maps']); ?>
	    </div><?php
	    if(!empty($page['google_maps_filter'])):?>
	    <div class="map-nav clear">
	    	<h3>Filter Projects</h3><?php
	    	print render($page['google_maps_filter']); ?>
			</div><?php
			endif;?>
  	</section><!-- end banner map -->

    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
    <?php print render($tabs2); ?>
    <?php print $messages; ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

    <section class="content">
    	<div class="container clear"><?php
		    print render($page['project_grid']); ?>
    	</div>
    </section>

  </main>
