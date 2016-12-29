	<?php render($page['content']['metatags']); ?>
  <main data-role="content">
		<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
		<?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>

		<?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
		<?php print render($tabs2); ?>
		<?php print $messages; ?>
		<?php print render($page['help']); ?>
		<?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

		<section class="slideshow-container"><?php
		if(!empty($page['banner'])):
			for($i=0, $n=sizeof($page['banner']); $i<$n; $i++):?>
			<section id="banner-<?php echo $i; ?>" class="banner<?php echo ($i==0) ? ' current' : ' hidden'; ?>"<?php echo (!empty($page['banner'][$i]['image'])) ? ' style="background-image: url(' . $page['banner'][$i]['image'] . ');'.(!empty($page['banner'][$i]['banner_hex']) ? " background-color: #".$page['banner'][$i]['banner_hex'].';': '').'"' : ''; ?>>
				<div class="background">
					<div class="container clear"><?php
						// Handle old homepage banner as well as new implementation
						if (!empty($page['banner'][$i]['head1'])) : ?>
							<h2<?php echo (!empty($page['banner'][$i]['head_hex']) ? ' style="color: #'.$page['banner'][$i]['head_hex'].'"' : '');?>><?php echo $page['banner'][$i]['head1']; ?></h2><?php
						elseif(!empty($page['banner_heading'])):?>
							<h2><?php print $page['banner_heading'];?></h2><?php
						endif; ?>
						<?php
						if (!empty($page['banner'][$i]['caption'])) : ?>
							<figcaption><?php echo $page['banner'][$i]['caption']; ?></figcaption>
						<?php
						elseif(isset($page['banner_caption']['content']) && !empty($page['banner_caption']['content'])):?>
							<figcaption><?php print $page['banner_caption']['content'];?></figcaption><?php
						endif; ?>
					</div>
				</div>
				<?php if ( isset($page['banner'][$i]['orange_bar']) && !empty($page['banner'][$i]['orange_bar']) ) : ?>
				<div class="tagline">
					<div class="container clear">
						<?php print $page['banner'][$i]['orange_bar'];?>
					</div>
				</div>
				<?php endif; ?>
			</section><?php
			endfor;
		else:?>
			<section id="banner" class="banner">
				<div class="background">
					<div class="container clear">
						<h2><?php print $page['banner_heading'];?></h2>
						<figcaption><?php print $page['banner_caption']['content'];?></figcaption>
					</div>
				</div>
				<div class="tagline">
					<div class="container clear">
						<?php print $page['orange_bar']['content'];?>
					</div>
				</div>
			</section>
		<?php
		endif;
		if (!empty($page['banner']) && count($page['banner']) > 1) : ?>
			<div class="container button-container">
				<section class="buttons">
				<?php for($i=1, $n=sizeof($page['banner']); $i<$n; $i++): ?>
					<?php if(!empty($page['banner'][$i]['control_text'])) : ?>
					<div class="button<?php echo ($i==0) ? ' hidden' : ''; ?> clear" data-banner="banner-<?php echo $i; ?>">
						<i class="fa fa-chevron-up"></i>
						<span class="link"><?php echo $page['banner'][$i]['control_text'];?></span>
					</div>
					<?php endif; ?>
				<?php endfor; ?>
				<?php if(!empty($page['banner'][0]['control_text'])) : ?>
				<div class="button hidden clear" data-banner="banner-0">
					<i class="fa fa-chevron-up"></i>
					<span class="link"><?php echo $page['banner'][0]['control_text'];?></span>
				</div>
				<?php endif; ?>
				</section>
			</div>
			<?php endif; ?>
		</section>

		<section class="industries">
			<?php echo $page['industry_section'];?>
		</section>
		<section class="solutions">
			<div class="background">
				<div class="container clear">
					<?php echo $page['blue_section'];?>
				</div>
			</div>
			<div class="project-metrics sticky">
				<?php echo $page['homepage_metrics']; ?>
			</div>
		</section><?php
		// temporarily exclude LOTE sites
		if($language->language == 'en'):?>
		<section class="promotions with-headline">
			<div class="container clear">
				<?php echo $page['resource_section'];?>
			</div>
		</section><?php
		endif;?>

  </main> <!-- /#wrapper -->
