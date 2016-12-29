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
			if(!isset($language) || $language->language == 'en'):?>
			<div class="sub-nav region-nav">
				<div class="container">
					<a href="#" data-region="north-america"><span><?php echo t('North America');?></span></a>
					<a href="#" data-region="south-america"><span><?php echo t('Central/South America');?></span></a>
					<a href="#" data-region="europe"><span><?php echo t('Europe');?></span></a>
					<a href="#" data-region="africa"><span><?php echo t('Middle East/Africa');?></span></a>
					<a href="#" data-region="asia"><span><?php echo t('Asia');?></span></a>
					<a href="#" data-region="australia"><span><?php echo t('Australia/NZ');?></span></a>
					<label for="location"><?php echo t('Select a region:');?></label>
					<select name="location" class="custom-select">
						<option value="north-america"><?php echo t('North America');?></option>
						<option value="south-america"><?php echo t('Central/South America');?></option>
						<option value="europe"><?php echo t('Europe');?></option>
						<option value="africa"><?php echo t('Middle East/Africa');?></option>
						<option value="asia"><?php echo t('Asia');?></option>
						<option value="australia"><?php echo t('Australia/NZ');?></option>
					</select>
				</div>
			</div><?php
			endif;?>

		</section>

			<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>

	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

			<?php
			print render($page['events_listing']);
			?>
	</main>
