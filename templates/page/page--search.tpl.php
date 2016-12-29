		<?php render($page['content']['metatags']); ?>
    <section class="content">
    	<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <a id="main-content"></a>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	    <div class="container clear">
	    		<section class="clear">
	    		<?php print render($page['content']); ?>
	    		</section>
			</div>
    </section>
