	<?php render($page['content']['metatags']); ?>
  <main data-role="content">
		<section class="banner<?php echo ($page['banner']['xlg_banner'] == true) ? ' banner-xlg' : ''; ?>"<?php echo (!empty($page['banner']['image'])) ? ' style="background-image: url(' . $page['banner']['image'] . ');"' : ''; ?>>
			<div class="background">
				<?php if ($page['banner']['has_container'] == true) : ?>
				<div class="container clear">
					<?php if (!empty($page['banner']['head1'])) : ?><h2><?php echo $head1; ?></h2><?php endif; ?>
					<?php if (!empty($page['banner']['head2'])) : ?><h3><?php echo $head2; ?></h3><?php endif; ?>
					<?php if (!empty($page['banner']['caption'])) : ?><figcaption><?php echo $caption; ?></figcaption><?php endif; ?>
					<?php if (!empty($page['banner']['cta_button'])) echo $cta_button; ?>
				</div>
				<?php endif; ?>
			</div>
		</section>

		<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
    <a id="main-content"></a>
    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
    <?php print render($tabs2); ?>
    <?php print $messages; ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
    <section class="content">
    	<div class="container clear">
	    	<article><?php
					print render($page['project_heading']);
					print render($page['content']);
					echo l(t('<i class="fa fa-angle-left"></i> Back to projects'), language_link('node/133'), array('html' => TRUE, 'attributes' => array('class' => 'button button-back'))); ?>
	    	</article>
	    	<aside class="sticky-aside" role="complementary">
			    <?php
					if ($page['sidebar_second']):
						print render($page['sidebar_second']);
					endif ?>
	    	</aside>
			</div>
    </section><?php
    if(isset($page['project_highlights']) && !empty($page['project_highlights'])):?>
    <section class="with-headline">
    	<div class="container clear">
    		<h2><?php echo t('Related projects');?></h2><?php
				print render($page['project_highlights']);// requires aconex module ?>
    	</div>
    </section><?php
    endif;?>

  </main>
