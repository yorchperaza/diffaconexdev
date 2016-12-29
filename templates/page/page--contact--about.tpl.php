	<?php render($page['content']['metatags']); ?>
  <?php print render($page['header']); //this could be used for the banner below ?>

  <main data-role="content">
		<section class="banner map">
			<div class="container clear">
				<?php if ($title): ?>
	      <h2><?php print $title ?></h2>
				<?php endif; ?>
			</div>
	    <div class="google-map"><?php
	    	print render($page['google_office_maps']); ?>
	    </div><?php
	    //if($language->language == 'en'):?>
	    <div class="sub-nav region-nav">
				<div class="container">
					<a href="#" data-region="NorthAmerica"><span><?php echo t('North America');?></span></a>
					<a href="#" data-region="CentralandSouthAmerica"><span><?php echo t('Central/South America');?></span></a>
					<a href="#" data-region="Europe"><span><?php echo t('Europe');?></span></a>
					<a href="#" data-region="MiddleEastAfrica"><span><?php echo t('Middle East/Africa');?></span></a>
					<a href="#" data-region="Asia"><span><?php echo t('Asia');?></span></a>
					<a href="#" data-region="AustraliaNZ"><span><?php echo t('Australia/NZ');?></span></a>
					<label for="location"><?php echo t('Select a region:');?></label>
					<select name="location" class="custom-select">
						<option value="NorthAmerica"><?php echo t('North America');?></option>
						<option value="CentralandSouthAmerica"><?php echo t('Central/South America');?></option>
						<option value="Europe"><?php echo t('Europe');?></option>
						<option value="MiddleEastAfrica"><?php echo t('Middle East/Africa');?></option>
						<option value="Asia"><?php echo t('Asia');?></option>
						<option value="AustraliaNZ"><?php echo t('Australia/NZ');?></option>
					</select>
				</div>
			</div><?php
			//endif;?>
  	</section><!-- end banner map -->

    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
    <?php print render($tabs2); ?>
    <?php print $messages; ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?><?php
		print render($page['contact_about']);?>

  </main>
