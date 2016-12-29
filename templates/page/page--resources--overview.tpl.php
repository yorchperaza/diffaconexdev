	<?php render($page['content']['metatags']); ?>
  <main data-role="content">
		<section class="banner<?php echo ($page['banner']['xlg_banner'] == true) ? ' banner-xlg' : ''; ?>"<?php echo (!empty($page['banner']['image'])) ? ' style="background-image: url(' . $page['banner']['image'] . ');"' : ''; ?>>
			<div class="background">
				<?php if ($page['banner']['has_container'] == true) : ?>
				<div class="container clear">
					<?php if (!empty($page['banner']['head1'])) : ?><h2><?php echo $page['banner']['head1']; ?></h2><?php endif; ?>
					<?php if (!empty($page['banner']['head2'])) : ?><h3><?php echo $page['banner']['head2']; ?></h3><?php endif; ?>
					<?php if (!empty($page['banner']['caption'])) : ?><figcaption><?php echo $page['banner']['caption']; ?></figcaption><?php endif; ?>
					<?php if (!empty($page['banner']['cta_button'])) echo $page['banner']['cta_button']; ?>
				</div>
				<?php endif; ?>
			</div>
			<?php
			if(!isset($language) || $language->language == 'en'):
				if ($page['subnav_resources']): ?>
			<div class="sub-nav">
				<div class="container">
				<?php print render($page['subnav_resources']); ?>
				</div>
			</div><?php
				endif;
			endif; ?>
		</section>

		<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
		<?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>

		<?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
		<?php print render($tabs2); ?>
		<?php print $messages; ?>
		<?php print render($page['help']); ?>
		<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

		<?php
		print render($page['resources_overview']);?>
	</main>
