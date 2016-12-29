<?php

/**
 * Produce article detail page
 *
 * @param: node mixed
 * @return: string
**/
function views_article_view($node)
{
	$article_html = '';
	if($node->field_article_date[LANGUAGE_NONE][0]['value'])
	{
		$date = strtotime($node->field_article_date[LANGUAGE_NONE][0]['value']);
		$article_html .= '<time datetime="'.date('Y-m-d', $date).'">'.date('F j, Y', $date).'</time>';
	}
	$article_html .= '<h1>'.$node->field_resource_preview_title[LANGUAGE_NONE][0]['value'].'</h1>';

	if($node->field_article_byline[LANGUAGE_NONE][0]['value'])
		//$article_html .= '<strong>'.$node->field_article_byline[LANGUAGE_NONE][0]['value'].'</strong>';

	if($node->field_resource_short_description[LANGUAGE_NONE][0]['value'])
		$article_html .= '<h3>'.$node->field_resource_short_description[LANGUAGE_NONE][0]['value'].'</h3>';

	$article_html .= $node->field_resource_body[LANGUAGE_NONE][0]['value'];

	return $article_html;
}


/**
 * Produce grid of client logos
 *
**/
function views_events_listing()
{
	//We'll use the language only to show the listing with results in THAT language or namerica ONLY if no results in their language
	global $language;

	$namerica_view = views_get_view_result('event_listing', 'namerica');
	$csamerica_view = views_get_view_result('event_listing', 'csamerica');
	$europe_view = views_get_view_result('event_listing', 'europe');
	$meast_africa_view = views_get_view_result('event_listing', 'meast_africa');
	$asia_view = views_get_view_result('event_listing', 'asia');
	$aus_nz_view = views_get_view_result('event_listing', 'aus_nz');

	$results_class = (empty($namerica_view)) ? ' no-results' : '';
	$events_html = '<section id="north-america" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('North America').'</h2>';
	if(!empty($namerica_view))
	{
		foreach($namerica_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	else
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';

	$results_class = (empty($csamerica_view)) ? ' no-results' : '';
	if(!empty($csamerica_view) || $language->language == 'en')
	$events_html .= '<section id="south-america" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('Central / South America').'</h2>';
	if(!empty($csamerica_view))
	{
		foreach($csamerica_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	elseif($language->language == 'en')
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	if(!empty($csamerica_view) || $language->language == 'en')
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';

	$results_class = (empty($europe_view)) ? ' no-results' : '';
	if(!empty($europe_view) || $language->language == 'en')
	$events_html .= '<section id="europe" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('Europe').'</h2>';
	if(!empty($europe_view))
	{
		foreach($europe_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	elseif($language->language == 'en')
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	if(!empty($europe_view) || $language->language == 'en')
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';

	$results_class = (empty($meast_africa_view)) ? ' no-results' : '';
	if(!empty($meast_africa_view) || $language->language == 'en')
	$events_html .= '<section id="africa" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('Middle East / Africa').'</h2>';
	if(!empty($meast_africa_view))
	{
		foreach($meast_africa_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	elseif($language->language == 'en')
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	if(!empty($meast_africa_view) || $language->language == 'en')
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';

	$results_class = (empty($asia_view)) ? ' no-results' : '';
	if(!empty($asia_view) || $language->language == 'en')
	$events_html .= '<section id="asia" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('Asia').'</h2>';
	if(!empty($asia_view))
	{
		foreach($asia_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	elseif($language->language == 'en')
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	if(!empty($asia_view) || $language->language == 'en')
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';

	$results_class = (empty($aus_nz_view)) ? ' no-results' : '';
	if(!empty($aus_nz_view) || $language->language == 'en')
	$events_html .= '<section id="australia" class="content with-headline' . $results_class . '">
										<div class="container clear">
											<h2>'.t('Australia / New Zealand').'</h2>';
	if(!empty($aus_nz_view))
	{
		foreach($aus_nz_view as $na => $event)
		{
			$link = trim($event->field_field_resources_title_link[0]['raw']['value'], '/');
			$iopts =  array('attributes' => array('target' => ($event->field_field_resource_in_new_window[0]['raw']['value'] == '1' ? '_blank' : '')));
			$eimg = theme('image', array('path' => $event->field_field_grid_image[0]['raw']['uri'], 'alt' => $event->node_title));
			$date = date('M j', strtotime($event->field_field_article_date[0]['raw']['value'])).($event->field_field_article_date[0]['raw']['value'] != $event->field_field_article_date[0]['raw']['value2'] ? '-'.date('j, Y', strtotime($event->field_field_article_date[0]['raw']['value2'])) : date(', Y', strtotime($event->field_field_article_date[0]['raw']['value'])));

			$events_html .= '<article class="article-highlight'.($na == 2 ? ' clear-after': '').'">
												<div class="image">
													<h4><time datetime="'.date('Y-m-d', strtotime($event->field_field_article_date[0]['raw']['value'])).'">'.strtoupper($date).'</time></h4>'.
													image_link($eimg, $link, $iopts).
												'</div>
												<h3>'.l($event->node_title, $link, $iopts).'</h3>
												<h4>'.$event->field_field_event_venue[0]['raw']['value'].(!empty($event->field_field_project_country[0]['raw']['value']) ? (!empty($event->field_field_event_venue[0]['raw']['value']) ? ' &mdash; ' : '').$event->field_field_project_country[0]['raw']['value'] :'').'</h4>
												<p>'.$event->field_field_resource_short_description[0]['raw']['value'].'</p>
											</article>';
		}
	}
	elseif($language->language == 'en')
	{
		$events_html .= '<h3>'.t('Check back soon for upcoming events in this region.').'</h3>';
	}
	if(!empty($aus_nz_view) || $language->language == 'en')
	$events_html .= '<a href="#" class="button-top">Back to top <i class="fa fa-angle-up"></i></a>
		</div>
	</section>';


	return $events_html;

}


/**
 * Produce grid of client logos
 *
**/
function views_client_logo_grid($industryId, $industryTable = 'field_data_field_project_industry')
{
	$logo_opts = array('industry' => $industryId,
										'region' => $_SESSION['akamai']['region_tid'],
										'limit' => 4,
										'industry_table' => $industryTable);

	$client_nodes = get_client_logo($logo_opts);

	$grid_html = '<div class="container clear">
									<h2>'.t('$1 Trillion in project value').'</h2>
									';

	$n = sizeof($client_nodes);
	foreach($client_nodes as $c=>$client)
	{
		$client_image = file_load($client->field_client_grid_image_fid);
		$grid_html .= '<div class="image column one-fourth'.(($c+1) == $n ? ' clear-after':'').'">
										<span>'.
										theme('image', array('path' => $client_image->uri, 'alt' => $client->title)).
									"	</span>
									</div>\n";
	}

	$grid_html .= "
								</div>\n";

	return $grid_html;
}

/**
 * Creates a custom view for homepage blue section
 *
 * @return: string
**/
function views_homepage_blue_section()
{
	$headline = language_block('73', 'homepage_content');
	$image = language_block('74', 'homepage_content');
	$left = language_block('75', 'homepage_content');
	$right = language_block('76', 'homepage_content');
	$blue_html = '<section class="intro">'.
									$headline['content'].
									$image['content'].
								'</section>
								<article>'.
									$left['content'].
								'</article><article class="clear-after">'.
									$right['content'].
								'</article>';

	return $blue_html;
}

/**
 * Creates a custom view for homepage industry section
 *
 * @return: string
**/
function views_homepage_industry_section($heading = '')
{
	global $language;

	$left_p_image = $mid_p_image = $right_p_image = '';

	$ind = language_block('72', 'homepage_content');

	// We will use the 'parent' option for LOTE pages
	$project_opts = array('region' => $_SESSION['akamai']['region_info']->tid);

	// 1st level industry
	$term_industry =  taxonomy_get_tree(6, 0, 1, FALSE);

	//construction
	$proj_left = '';
	if(!empty($term_industry))
	{
		$project_excludes = array();

		if($language->language != 'en')
			$project_opts['parent'] = $term_industry[0]->tid;
		else
			$project_opts['industry'] = $term_industry[0]->tid;

		$proj_left = get_project_random($project_opts);
		if($proj_left)
		{
			$left_p_image = theme('image', array('path' => file_load($proj_left->field_grid_image_fid)->uri,
																					'alt' => $proj_left->field_grid_image_alt));
			$project_excludes[] = $proj_left->nid;
		}
		$proj_left_hover = language_block('84', 'homepage_content');

		//infrastructure
		$mid_p_image = '';
		if($language->language != 'en')
			$project_opts['parent'] = $term_industry[1]->tid;
		else
			$project_opts['industry'] = $term_industry[1]->tid;

		//$project_opts['exclude'] = $project_excludes;
		$proj_mid = get_project_random($project_opts);
		if($proj_mid)
		{
			$mid_p_image = theme('image', array('path' => file_load($proj_mid->field_grid_image_fid)->uri,
																					'alt' => $proj_mid->field_grid_image_alt));
			$project_excludes[] = $proj_mid->nid;
		}
		$proj_mid_hover = language_block('85', 'homepage_content');

		//energy & resources
		$right_p_image = '';
		if($language->language != 'en')
			$project_opts['parent'] = $term_industry[2]->tid;
		else
			$project_opts['industry'] = $term_industry[2]->tid;

		//$project_opts['exclude'] = $project_excludes;
		$proj_right = get_project_random($project_opts);
		if($proj_right)
		{
			$right_p_image = theme('image', array('path' => file_load($proj_right->field_grid_image_fid)->uri,
																						'alt' => $proj_right->field_grid_image_alt));
			$project_excludes[] = $proj_right->nid;
		}
		$proj_right_hover = language_block('86', 'homepage_content');
	}

	$cpage = language_link("node/1300");
	$infpage = language_link("node/1325");
	$erpage = language_link("node/1302");

  if (!$heading) {
    $heading = $ind['content'];
  }

  // Add caption to images.
  $left_p_image .= '<div class="text">' . $proj_left_hover['content'] . '</div>';
  $mid_p_image .= '<div class="text">' . $proj_mid_hover['content'] . '</div>';
  $right_p_image .= '<div class="text">' . $proj_right_hover['content'] . '</div>';

	$industry_html = '<div class="container clear">
											<section class="intro">'.
											$heading .
											'</section>
											<div class="article-container clear">
												<article class="article-highlight">
													<div class="image">
														<div class="value">'.$proj_left->field_project_size_value.'</div>
														<div class="image-overlay">'.
														image_link($left_p_image, $cpage).
														'</div>
														<div class="info hidden">
															'.$proj_left_hover['content'].'
														</div>
													</div>
													<h3>'.l(t('Construction'), $cpage).'</h3>
												</article>
												<article class="article-highlight">
													<div class="image">
														<div class="value">'.$proj_mid->field_project_size_value.'</div>
														<div class="image-overlay">'.
															image_link($mid_p_image, $infpage).
														'</div>
														<div class="info hidden">
															'.$proj_mid_hover['content'].'
														</div>
													</div>
													<h3>'.l(t('Infrastructure'), $infpage).'</h3>
												</article>
												<article class="article-highlight clear-after">
													<div class="image">
														<div class="value">'.$proj_right->field_project_size_value.'</div>
														<div class="image-overlay">'.
															image_link($right_p_image, $erpage).
														'</div>
														<div class="info hidden">
															'.$proj_right_hover['content'].'
														</div>
													</div>
													<h3>'.l(t('Energy & Resources'), $erpage).'</h3>
												</article>
											</div>
										</div>';

	return $industry_html;
}

/**
 * Creates a custom view for home page project metrics section
 * 
 * @return: string
 */
function views_homepage_project_metrics($heading = '', $project_title = 'Project Users', $mail_title = 'Mail', $document_title = 'Documents') {
	$homepage_metrics = variable_get("acx_homepage_metrics", false);
	if ($homepage_metrics === false) {
		return;
	}

  if (!$heading) {
    $heading = '<a id="metrics-header-toggle" href="#"><i class="fa fa-chevron-down"></i> Project Activity</a>';
  }

	$html = '
				<div class="header">
					<h3>' . $heading . '</h3>
				</div>
				<div class="metric-container">
					<div class="metric-description">
						<div class="left">
							<p><span id="metric-projects">' . number_format($homepage_metrics['firstday']['projects'] + ( (time() - $homepage_metrics['start_of_month']) * $homepage_metrics['project_delta'] ) ) . '</span><br>
							' . $project_title . '</p>
						</div>
						<div class="right">
							<img src="' . path_to_theme() . '/images/icons/users.png" alt="Users">
						</div>
						<div class="clear"></div>
					</div>
					<div class="metric-description">
						<div class="left">
							<p><span id="metric-mail">' . number_format($homepage_metrics['firstday']['mail'] + ( (time() - $homepage_metrics['start_of_month']) * $homepage_metrics['mail_delta'] ) ) . '</span><br>
							' . $mail_title . '</p>
						</div>
						<div class="right">
							<img src="' . path_to_theme() . '/images/icons/mail.png" alt="Mail">
						</div>
						<div class="clear"></div>
					</div>
					<div class="metric-description">
						<div class="left">
							<p><span id="metric-documents">' . number_format($homepage_metrics['firstday']['documents'] + ( (time() - $homepage_metrics['start_of_month']) * $homepage_metrics['documents_delta'] ) ) . '</span><br>
							' . $document_title . '</p>
						</div>
						<div class="right">
							<img src="' . path_to_theme() . '/images/icons/documents.png" alt="Documents">
						</div>
						<div class="clear"></div>
					</div>
				</div>
				<script>
				  var mail_start = ' . $homepage_metrics['firstday']['mail'] . ';
				  var projects_start = ' . $homepage_metrics['firstday']['projects'] . ';
				  var documents_start = ' . $homepage_metrics['firstday']['documents'] . ';
				  
				  var mail_delta = ' . $homepage_metrics['mail_delta'] . ';
				  var projects_delta = ' . $homepage_metrics['project_delta'] . ';
				  var documents_delta = ' . $homepage_metrics['documents_delta'] . ';
				  
				  var start_of_month = ' . $homepage_metrics['start_of_month'] . ';
				</script>';
	return $html;
}
/**
 * Creates a custom view for homepage resources section
 *
 * @return: string
**/
function views_homepage_resource_section($node)
{
	$lt_img_opts = $md_img_opts = $rt_img_opts = array();
	$target_blank = array('target' => '_blank');

	$resource_headline = language_block('77', 'homepage_content');
	$resource_left = node_load($node->field_body_cta_left[LANGUAGE_NONE][0]['nid']);
	$lt_term = taxonomy_term_load($resource_left->field_resource_type[LANGUAGE_NONE][0]['tid']);
	$lt_img = array('path' => file_build_uri($resource_left->field_grid_image[LANGUAGE_NONE][0]['filename']),
								  'alt' => $resource_left->field_grid_image[LANGUAGE_NONE][0]['alt']);
	$lt_img = theme('image', $lt_img);
	$lt_lnk = !empty($resource_left->field_resources_title_link[LANGUAGE_NONE][0]['value']) ? trim($resource_left->field_resources_title_link[LANGUAGE_NONE][0]['value'], '/') : 'node/'.$resource_left->nid;
	if($resource_left->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1')
		$lt_img_opts = $target_blank;

	$resource_middle = node_load($node->field_body_cta_middle[LANGUAGE_NONE][0]['nid']);
	$md_term = taxonomy_term_load($resource_middle->field_resource_type[LANGUAGE_NONE][0]['tid']);
	$md_img = array('path' => file_build_uri($resource_middle->field_grid_image[LANGUAGE_NONE][0]['filename']),
								  'alt' => $resource_middle->field_grid_image[LANGUAGE_NONE][0]['alt']);
	$md_img = theme('image', $md_img);
	$md_lnk = !empty($resource_middle->field_resources_title_link[LANGUAGE_NONE][0]['value']) ? trim($resource_middle->field_resources_title_link[LANGUAGE_NONE][0]['value'], '/') : 'node/'.$resource_middle->nid;
	if($resource_middle->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1')
		$md_img_opts = $target_blank;

	$resource_right = node_load($node->field_body_cta_right[LANGUAGE_NONE][0]['nid']);

	// Handle event vs. resource in right column
	if($resource_right->type == 'events')
	{
		$rt_term = new stdClass;
		$rt_term->name = t('Event');
		$rt_h3 = $resource_right->field_resource_preview_title[LANGUAGE_NONE][0]['value'];
		$rt_body = $resource_right->field_resource_short_description[LANGUAGE_NONE][0]['value'];
	}
	else
	{
		$rt_term = taxonomy_term_load($resource_right->field_resource_type[LANGUAGE_NONE][0]['tid']);
		$rt_h3 = (string)$resource_right->field_cta_headline[LANGUAGE_NONE][0]['value'];
		$rt_body = $resource_right->field_cta_body[LANGUAGE_NONE][0]['value'];
	}
	$rt_img = array('path' => file_build_uri($resource_right->field_grid_image[LANGUAGE_NONE][0]['filename']),
								  'alt' => $resource_right->field_grid_image[LANGUAGE_NONE][0]['alt']);
	$rt_img = theme('image', $rt_img);
	$rt_lnk = !empty($resource_right->field_resources_title_link[LANGUAGE_NONE][0]['value']) ? trim($resource_right->field_resources_title_link[LANGUAGE_NONE][0]['value'], '/') : 'node/'.$resource_right->nid;
	if($resource_right->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1')
		$rt_img_opts = $target_blank;

	$resource_html = $resource_headline['content'].'
											<article class="article-highlight">
												<div class="image">'.
													(!empty($lt_term) ? '<h4>'.strtoupper($lt_term->name).'</h4>' : '').
													image_link($lt_img, $lt_lnk, array('attributes' => $lt_img_opts)).
											 '</div>
												<h3>'.l((string)$resource_left->field_cta_headline[LANGUAGE_NONE][0]['value'], $lt_lnk, array('attributes' => $lt_img_opts)).'</h3>
												<p>'.$resource_left->field_cta_body[LANGUAGE_NONE][0]['value'].'</p>
											</article>
											<article class="article-highlight">
												<div class="image">'.
													(!empty($md_term) ? '<h4>'.strtoupper($md_term->name).'</h4>' : '').
													image_link($md_img, $md_lnk, array('attributes' => $md_img_opts)).
											 '</div>
												<h3>'.l((string)$resource_middle->field_cta_headline[LANGUAGE_NONE][0]['value'], $md_lnk, array('attributes' => $md_img_opts)).'</h3>
												<p>'.$resource_middle->field_cta_body[LANGUAGE_NONE][0]['value'].'</p>
											</article>
											<article class="article-highlight clear-after">
												<div class="image">'.
													(!empty($rt_term) ? '<h4>'.strtoupper($rt_term->name).'</h4>' : '').
													image_link($rt_img, $rt_lnk, array('attributes' => $rt_img_opts)).
											 '</div>
												<h3>'.l($rt_h3, $rt_lnk, array('attributes' => $rt_img_opts)).'</h3>
												<p>'.$rt_body.'</p>
											</article>';

	return $resource_html;
}

/**
 * Creates a custom view for jobs page
 *
 * @param: mixed
 * @return: string
**/
function views_jobs_depts($node)
{

	$depts_html = '<div class="container clear">
									<h2>'.$node->field_department_header[LANGUAGE_NONE][0]['value'].'</h2>'.
									'<div class="tab-nav">
										<a class="selected" data-id="sales-marketing" href="#sales-marketing">'.t('Product & Engineering').'</a>
										<a data-id="it" href="#it">'.t('Sales & Marketing').'</a>
										<a data-id="customer-support" href="#customer-support">'.t('Customer Support').'</a>
										<a data-id="corporate" href="#corporate">'.t('Corporate').'</a>
									</div>
									<section id="sales-marketing" class="tab clear show">'.
										$node->field_product_engineering[LANGUAGE_NONE][0]['value'].
									'</section>
									<section id="it" class="tab clear">'.
										$node->field_sales_marketing[LANGUAGE_NONE][0]['value'].
									'</section>
									<section id="customer-support" class="tab clear">'.
										$node->field_customer_support[LANGUAGE_NONE][0]['value'].
									'</section>
									<section id="corporate" class="tab clear">'.
										$node->field_corporate[LANGUAGE_NONE][0]['value'].
									'</section>'.
								'</div>';

	return $depts_html;
}

/**
 * Creates a custom view for jobs page
 *
 * @param: mixed
 * @return: string
**/
function views_jobs_main($node)
{
	return $node->body[LANGUAGE_NONE][0]['value'];
}

/**
 * Creates a custom view for jobs page
 *
 * @param: mixed
 * @return: string
**/
function views_jobs_offices($node)
{
	global $language;

	// These office nodes should not change - easy retrieval
	$sanfran = node_load(language_node(189)->nid);
	$london = node_load(language_node(174)->nid);
	$dubai = node_load(language_node(166)->nid);
	$bangalore = node_load(language_node(805)->nid);
	$hongkong = node_load(language_node(155)->nid);
	$melbourne = node_load(language_node(151)->nid);

	$offices_html = '<div class="container clear">'.
										$node->field_offices_copy[LANGUAGE_NONE][0]['value'].
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $sanfran->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$sanfran->title.'</figcaption>
										</figure>'.
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $london->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$london->title.'</figcaption>
										</figure>'.
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $dubai->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$dubai->title.'</figcaption>
										</figure>'.
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $bangalore->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$bangalore->title.'</figcaption>
										</figure>'.
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $hongkong->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$hongkong->title.'</figcaption>
										</figure>'.
										'<figure class="column one-sixth inline-column">'.
											theme('image', array('path' => $melbourne->field_office_picture[LANGUAGE_NONE][0]['uri'])).
											'<figcaption>'.$melbourne->title.'</figcaption>
										</figure>
									</div>';

	return $offices_html;
}


/**
 * Creates a custom view for jobs page
 *
 * @param: mixed
 * @return: string
**/
function views_jobs_perks($node)
{
	$us_off = entity_load('field_collection_item', array($node->field_us_offers[LANGUAGE_NONE][0]['value']));
	$india_off = entity_load('field_collection_item', array($node->field_india_offers[LANGUAGE_NONE][0]['value']));
	$aus_off = entity_load('field_collection_item', array($node->field_australia_offers[LANGUAGE_NONE][0]['value']));
	$other_off = entity_load('field_collection_item', array($node->field_other_offers[LANGUAGE_NONE][0]['value']));

	$chk_img = '/'.path_to_theme('aconex').'/images/icons/checkbox.png';

	$us_offers = '';
	foreach($us_off as $id => $offer)
	{
		$us_offers = '<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_1[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_2[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column last">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_3[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>';
	}
	$india_offers = '';
	foreach($india_off as $id => $offer)
	{
		$india_offers = '<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_1[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_2[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column last">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_3[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>';
	}
	$aus_offers = '';
	foreach($aus_off as $id => $offer)
	{
		$aus_offers = '<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_1[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_2[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column last">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_3[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>';
	}
	$other_offers = '';
	foreach($other_off as $id => $offer)
	{
		$other_offers = '<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_1[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_2[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>
									<figure class="column one-third inline-column last">
										<img class="icon-checkbox" src="'.$chk_img.'">
										<figcaption>'.$offer->field_offer_3[LANGUAGE_NONE][0]['value'].'</figcaption>
									</figure>';
	}

	$perks_html = '<div class="container clear">'.
									$node->field_what_we_offer[LANGUAGE_NONE][0]['value'].
									'<div class="tab-nav">
										<a class="selected" data-id="united-states" href="#united-states">'.t('United States').'</a>
										<a data-id="india" href="#india">'.t('India').'</a>
										<a data-id="australia" href="#australia">'.t('Australia').'</a>
										<a data-id="other" href="#other">'.t('Other').'</a>
										</div>
										<section id="united-states" class="tab clear show">'.
											$us_offers.
										'</section>
										<section id="india" class="tab clear">'.
											$india_offers.
										'</section>
										<section id="australia" class="tab clear">'.
											$aus_offers.
										'</section>
										<section id="other" class="tab clear">'.
											$other_offers.
										'</section>
									</div>
								</div>';

	return $perks_html;
}

/**
 * Creates a custom view for jobs page
 *
 * @param: mixed
 * @return: array
**/
function views_jobs_values($node)
{
	$values_html = '<div class="container clear">'.
										$node->field_values_copy[LANGUAGE_NONE][0]['value'].
										'<figure class="column one-fifth inline-column">'.
											theme('image', array('path' => $node->field_values_icon_1[LANGUAGE_NONE][0]['taxonomy_term']->field_values_icon[LANGUAGE_NONE][0]['uri'], 'alt' => $node->field_values_icon_1[LANGUAGE_NONE][0]['taxonomy_term']->name, 'attributes' => array('class' => array('icon-value')))).
											'<figcaption>'.$node->field_values_icon_1[LANGUAGE_NONE][0]['taxonomy_term']->name.'</figcaption>
										</figure>
										<figure class="column one-fifth inline-column">'.
											theme('image', array('path' => $node->field_values_icon_2[LANGUAGE_NONE][0]['taxonomy_term']->field_values_icon[LANGUAGE_NONE][0]['uri'], 'alt' => $node->field_values_icon_2[LANGUAGE_NONE][0]['taxonomy_term']->name, 'attributes' => array('class' => array('icon-value')))).
											'<figcaption>'.$node->field_values_icon_2[LANGUAGE_NONE][0]['taxonomy_term']->name.'</figcaption>
										</figure>
										<figure class="column one-fifth inline-column">'.
											theme('image', array('path' => $node->field_values_icon_3[LANGUAGE_NONE][0]['taxonomy_term']->field_values_icon[LANGUAGE_NONE][0]['uri'], 'alt' => $node->field_values_icon_3[LANGUAGE_NONE][0]['taxonomy_term']->name, 'attributes' => array('class' => array('icon-value')))).
											'<figcaption>'.$node->field_values_icon_3[LANGUAGE_NONE][0]['taxonomy_term']->name.'</figcaption>
										</figure>
										<figure class="column one-fifth inline-column">'.
											theme('image', array('path' => $node->field_values_icon_4[LANGUAGE_NONE][0]['taxonomy_term']->field_values_icon[LANGUAGE_NONE][0]['uri'], 'alt' => $node->field_values_icon_4[LANGUAGE_NONE][0]['taxonomy_term']->name, 'attributes' => array('class' => array('icon-value')))).
											'<figcaption>'.$node->field_values_icon_4[LANGUAGE_NONE][0]['taxonomy_term']->name.'</figcaption>
										</figure>
										<figure class="column one-fifth inline-column clear-after">'.
											theme('image', array('path' => $node->field_values_icon_5[LANGUAGE_NONE][0]['taxonomy_term']->field_values_icon[LANGUAGE_NONE][0]['uri'], 'alt' => $node->field_values_icon_5[LANGUAGE_NONE][0]['taxonomy_term']->name, 'attributes' => array('class' => array('icon-value')))).
											'<figcaption>'.$node->field_values_icon_5[LANGUAGE_NONE][0]['taxonomy_term']->name.'</figcaption>
										</figure>
									</div>';

	return $values_html;
}

/**
 * Creates a custom view for Industries details for all other pages in current category
 *
 * @param: int
 * @return: array
**/
function views_industry_others_grid($parent)
{
	$industries_nodes = array();

	$term = taxonomy_term_load($parent);

	// Get the other terms of this parent
	$other_industries = taxonomy_get_children($parent);

	// Create the grid HTML
	$industries_html = '<h2>'.t('See how Aconex is used on '.$term->name)."</h2>\n";

	$pos = 1;
	foreach($other_industries as $tid => $term)
	{
		// Get the nodes for the other industry categories
		$level2_query = db_select('node', 'n');
		$level2_query->join('taxonomy_index', 'ti', 'n.nid = ti.nid');
		$level2_query->fields('n', array('nid'))
									->fields('ti', array('tid'))
									->condition('n.type', 'industries', '=')
									->condition('ti.tid', $tid, '=')
									->range(0, 1);

		$level2 = $level2_query->execute();
		if($level2->rowCount() == 1)
		{
			$sub_industry = $level2->fetchObject();
			$i_node = node_load($sub_industry->nid);
			$image = get_project_image($tid, $_SESSION['akamai']['region_tid']);
			$project_image = file_load($image->field_grid_image_fid);

			$industries_html .= '<article class="article-highlight article-highlight-overview'.($pos == 3 ? ' clear-after': '').'">'.
													theme('image', array('path' => $project_image->uri, 'alt' => $image->field_grid_image_alt)).
													'<h3>'.l($i_node->title, 'node/'.$i_node->nid).'</h3>'.
													"</article>\n";
		}
		$pos++;
	}
	$industries_html .= "\n";

	return $industries_html;
}

/**
 * Produce leadership page
 *
**/
function views_leadership()
{
	// Each leader thumb header
	$mgmt_hd_view = views_get_view_result('leadership', 'mgmt_top');
	// Leadership blocks
	$mgmt_view = views_get_view_result('leadership', 'management');

	$leadership_html = '<section class="content tabs leadership-tabs">
												<div class="container clear">
												<h2>'.t('Management Team').'</h2>
												<div class="tab-nav clear">';

												foreach($mgmt_hd_view as $hd => $hdleader)
												{
													$lid = str_replace(' ', '-', $hdleader->_field_data['nid']['entity']->title);
													$limg = theme('image', array('path' => $hdleader->field_field_leadership_thumb[0]['raw']['uri'], 'alt' => $hdleader->_field_data['nid']['entity']->title));
													$leadership_html .= '<a class="thumb'.($hd == 0 ? ' selected' : '').'" data-id="'.$lid.'" href="#'.$lid.'">'.
																									$limg.
																									'<span class="label">'.$hdleader->field_field_job_title_thumb[0]['raw']['value'].'</span>
																								</a>';
												}
	$leadership_html .= '</div>';

												foreach($mgmt_view as $mg => $leader)
												{
													$lid = str_replace(' ', '-', $leader->node_title);
													$limg = theme('image', array('path' => $leader->field_field_leadership_image[0]['raw']['uri'], 'alt' => $leader->node_title));

													$leadership_html .= '<section id="'.$lid.'" class="tab clear'.($mg == 0 ? ' show' : '').'">
																								<div class="column one-half">'.
																									$limg.'
																								</div>
																								<div class="column one-half clear-after">
																									<h3>'.$leader->node_title.'</h3>
																									<h4>'.$leader->field_field_job_title[0]['raw']['value'].'</h4>
																									<p>'.$leader->field_body[0]['rendered']['#markup'].'</p>
																									</div>
																								</section>';
												}
	$leadership_html .= '</div>
											</section>';

	// Board section
	$board_hd_view = views_get_view_result('leadership', 'board_top');
	// Leadership blocks
	$board_view = views_get_view_result('leadership', 'board');
	$leadership_html .= '<section class="content tabs leadership-tabs">
												<div class="container clear">
												<h2>'.t('Board of Directors').'</h2>
												<div class="tab-nav clear">';

												foreach($board_hd_view as $hd => $hdleader)
												{
													$lid = str_replace(' ', '-', $hdleader->_field_data['nid']['entity']->title);
													$limg = theme('image', array('path' => $hdleader->field_field_leadership_thumb[0]['raw']['uri'], 'alt' => $hdleader->_field_data['nid']['entity']->title));
													$leadership_html .= '<a class="thumb'.($hd == 0 ? ' selected' : '').'" data-id="'.$lid.'" href="#'.$lid.'">'.
																									$limg.
																									'<span class="label">'.$hdleader->field_field_job_title_thumb[0]['raw']['value'].'</span>
																								</a>';
												}
	$leadership_html .= '</div>';

												foreach($board_view as $mg => $leader)
												{
													$lid = str_replace(' ', '-', $leader->node_title);
													$limg = theme('image', array('path' => $leader->field_field_leadership_image[0]['raw']['uri'], 'alt' => $leader->node_title));

													$leadership_html .= '<section id="'.$lid.'" class="tab clear'.($mg == 0 ? ' show' : '').'">
																								<div class="clear-after">
																									<h3>'.$leader->node_title.'</h3>
																									<p>'.$leader->field_body[0]['rendered']['#markup'].'</p>
																									</div>
																								</section>';
												}
	$leadership_html .= '</div>
											</section>';

	return $leadership_html;
}


/**
 * Produce left/right aligned content section
 *
**/
function views_left_right_section($sections, $is_project = FALSE, $filter = array())
{
	// Banner will appear according to preferred weight (low to high), but regionality should take precedence
	$section_html = '';
	$exclude = array();
	if (isset($sections) && is_array($sections))
	{
		foreach ($sections as $s => $eid)
		{
			$curr_section = entity_load('field_collection_item', array($eid['value']));
			foreach($curr_section as $f=>$val)
			{
				$sec_img = $img_caption = '';
				if($is_project)
				{
					$p_image = new project();
					$p_image->omit = $exclude;

					if($filter['org_type'])
					{
						$p_image->type = 'org_type';
						$p_image->tax_id = $filter['org_type'];
					}
					elseif($filter['industry'])
					{
						$p_image->type = 'industry';
						$p_image->tax_id = $filter['industry'];
					}

					$image = $p_image->get_project_random();
					if($p_image)
					{
						$project_image = file_load($image->field_featured_circle_image_fid);
						$sec_img = theme('image', array('path' => $project_image->uri, 'alt' => $image->field_featured_circle_image_alt));
						$img_caption = '<p>' . $image->title;
						$img_caption .= (isset($image->field_project_size_value) && !empty($image->field_project_size_value)) ? '<br>'.$image->field_project_size_value . '</p>' : '</p>';
						// don't duplicate images
						$exclude[] = $image->nid;
					}
				}
				else
				{
					$sec_img = theme('image', array('path' => $val->field_section_image[LANGUAGE_NONE][0]['uri'], array('alt' => $val->field_section_image[LANGUAGE_NONE][0]['alt'])));
					$img_caption = (!empty($val->field_section_image[LANGUAGE_NONE][0]['image_field_caption']['value']) ? $val->field_section_image[LANGUAGE_NONE][0]['image_field_caption']['value'] : '');
				}

				$ft1 = taxonomy_term_load($val->field_section_icon_1[LANGUAGE_NONE][0]['tid']);
				$ft1_ico = theme('image', array('path' => $ft1->field_feature_icon[LANGUAGE_NONE][0]['uri']));
				$ft2_ico = $ft3_ico = $ft4_ico = $ft5_ico = '';
				if(isset($val->field_section_icon_2[LANGUAGE_NONE][0]['tid']))
				{
					$ft2 = taxonomy_term_load($val->field_section_icon_2[LANGUAGE_NONE][0]['tid']);
					$ft2_ico = theme('image', array('path' => $ft2->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}
				if(isset($val->field_section_icon_3[LANGUAGE_NONE][0]['tid']))
				{
					$ft3 = taxonomy_term_load($val->field_section_icon_3[LANGUAGE_NONE][0]['tid']);
					$ft3_ico = theme('image', array('path' => $ft3->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}
				if(isset($val->field_section_icon_4[LANGUAGE_NONE][0]['tid']))
				{
					$ft4 = taxonomy_term_load($val->field_section_icon_4[LANGUAGE_NONE][0]['tid']);
					$ft4_ico = theme('image', array('path' => $ft4->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}
				if(isset($val->field_section_icon_5[LANGUAGE_NONE][0]['tid']))
				{
					$ft5 = taxonomy_term_load($val->field_section_icon_5[LANGUAGE_NONE][0]['tid']);
					$ft5_ico = theme('image', array('path' => $ft5->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}

				$section_id = (!empty($val->field_section_id[LANGUAGE_NONE][0]['value']))?$val->field_section_id[LANGUAGE_NONE][0]['value']:'';

				$section_html .= '<section id="'.$section_id.'" class="clear">
														<h2>'.$val->field_section_heading[LANGUAGE_NONE][0]['value'].'</h2>
														<figure>'.
															$sec_img.
															(!empty($img_caption) ? '<figcaption>'.$img_caption.'</figcaption>': '').
														'</figure>
														<div class="copy clear">
															<div class="icon">'.
																$val->field_section_icon_1[LANGUAGE_NONE][0]['value'].
																$ft1_ico.'
															</div>
															<h3>'.$val->field_section_heading_1[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_1[LANGUAGE_NONE][0]['value'].'</p>';
															// The rest are not required
				if(!empty($val->field_section_heading_2[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_2[LANGUAGE_NONE][0]['value']))
				{
					$section_html .=		(!empty($ft2_ico) ?
															'<div class="icon">'
																.$ft2_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_2[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_2[LANGUAGE_NONE][0]['value'].'</p>';
				}
				if(!empty($val->field_section_heading_3[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_3[LANGUAGE_NONE][0]['value']))
				{
					$section_html .=		(!empty($ft3_ico) ?
															'<div class="icon">'.
																$ft3_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_3[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_3[LANGUAGE_NONE][0]['value'].'</p>';
				}
				if(!empty($val->field_section_heading_4[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_4[LANGUAGE_NONE][0]['value']))
				{
					$section_html .=		(!empty($ft4_ico) ?
															'<div class="icon">'.
																$ft4_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_4[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_4[LANGUAGE_NONE][0]['value'].'</p>';
				}
				if(!empty($val->field_section_heading_5[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_5[LANGUAGE_NONE][0]['value']))
				{
					$section_html .=		(!empty($ft5_ico) ?
															'<div class="icon">'.
																$ft5_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_5[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_5[LANGUAGE_NONE][0]['value'].'</p>';
				}

				$section_html .= "
													</div>
												</section>\n";
			}
		}
	}

  return $section_html;
}

/**
 * Produce left/right aligned content section
 *
**/
function views_left_right_solution_section($sections) {
	// Banner will appear according to preferred weight (low to high), but regionality should take precedence
	$section_html = '';
	$exclude = array();
	if (isset($sections) && is_array($sections)) {
		foreach ($sections as $s => $eid) {
			$curr_section = entity_load('field_collection_item', array($eid['value']));

			foreach ($curr_section as $f=>$val) {
				$sec_img = $img_caption = '';
				
				$sec_img = theme('image', array('path' => $val->field_section_image[LANGUAGE_NONE][0]['uri'], array('alt' => $val->field_section_image[LANGUAGE_NONE][0]['alt'])));
				$img_caption = (!empty($val->field_section_image[LANGUAGE_NONE][0]['image_field_caption']['value']) ? $val->field_section_image[LANGUAGE_NONE][0]['image_field_caption']['value'] : '');
				$img_target_url = (!empty($val->field_section_image_target_url[LANGUAGE_NONE][0]['url']) ? $val->field_section_image_target_url[LANGUAGE_NONE][0]['url'] : '');
				$target = (!empty($val->field_section_image_target_url[LANGUAGE_NONE][0]['attributes']['target'])) ? ' target="' . $val->field_section_image_target_url[LANGUAGE_NONE][0]['attributes']['target'] . '"' : '';

				$ft1 = taxonomy_term_load($val->field_section_icon_1[LANGUAGE_NONE][0]['tid']);
				$ft1_ico = theme('image', array('path' => $ft1->field_feature_icon[LANGUAGE_NONE][0]['uri']));
				$ft2_ico = $ft3_ico = $ft4_ico = $ft5_ico = '';

				$links = $val->field_section_link_collection[LANGUAGE_NONE];
				$flag = false;
				$links_html = '';

				if (isset($links) && is_array($links)) {
					$links_html .= '<div class="section-links">';

					foreach ($links as $k => $v) {
						$cur_link = entity_load('field_collection_item', array($v['value']));
						foreach ($cur_link as $key => $value) {
							if (!empty($value->field_link[LANGUAGE_NONE][0]['title']) && !empty($value->field_link[LANGUAGE_NONE][0]['url'])) {
								$target = (!empty($value->field_link[LANGUAGE_NONE][0]['attributes']['target'])) ? ' target="' . $value->field_link[LANGUAGE_NONE][0]['attributes']['target'] . '"' : '';
								$flag = true;
								$links_html .= '<a href="'.$value->field_link[LANGUAGE_NONE][0]['url'].'" class="'.(($value->field_link_type[LANGUAGE_NONE][0]['value']==1)?'video-link':'').'" '.$target.'>'.$value->field_link[LANGUAGE_NONE][0]['title'].'</a>';
							}
						}
					}

					$links_html .= '</div>';
				}

				if (isset($val->field_section_icon_2[LANGUAGE_NONE][0]['tid'])) {
					$ft2 = taxonomy_term_load($val->field_section_icon_2[LANGUAGE_NONE][0]['tid']);
					$ft2_ico = theme('image', array('path' => $ft2->field_feature_icon[LANGUAGE_NONE][0]['uri']));
				}

				if (isset($val->field_section_icon_3[LANGUAGE_NONE][0]['tid'])) {
					$ft3 = taxonomy_term_load($val->field_section_icon_3[LANGUAGE_NONE][0]['tid']);
					$ft3_ico = theme('image', array('path' => $ft3->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}

				if (isset($val->field_section_icon_4[LANGUAGE_NONE][0]['tid'])) {
					$ft4 = taxonomy_term_load($val->field_section_icon_4[LANGUAGE_NONE][0]['tid']);
					$ft4_ico = theme('image', array('path' => $ft4->field_feature_icon[LANGUAGE_NONE][0]['uri']));

				}

				if (isset($val->field_section_icon_5[LANGUAGE_NONE][0]['tid'])) {
					$ft5 = taxonomy_term_load($val->field_section_icon_5[LANGUAGE_NONE][0]['tid']);
					$ft5_ico = theme('image', array('path' => $ft5->field_feature_icon[LANGUAGE_NONE][0]['uri']));
				}

				$section_id = (!empty($val->field_section_id[LANGUAGE_NONE][0]['value']))?$val->field_section_id[LANGUAGE_NONE][0]['value']:'';

				$section_html .= '
					<section id="'.$section_id.'" class="clear '.(($flag)?'':'no-links').'">
						<div class="container">
							<div class="copy clear">
								<h2>'.$val->field_section_heading[LANGUAGE_NONE][0]['value'].'</h2>
								<p>'.$val->field_section_description[LANGUAGE_NONE][0]['value'].'</p>
								<div class="icon">'.
									$val->field_section_icon_1[LANGUAGE_NONE][0]['value'].
									$ft1_ico.'
								</div>
								<h3>'.$val->field_section_heading_1[LANGUAGE_NONE][0]['value'].'</h3>
								<p>'.$val->field_section_copy_1[LANGUAGE_NONE][0]['value'].'</p>';
				
				// The rest are not required
				if (!empty($val->field_section_heading_2[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_2[LANGUAGE_NONE][0]['value'])) {
					$section_html .=		(!empty($ft2_ico) ?
															'<div class="icon">'
																.$ft2_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_2[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_2[LANGUAGE_NONE][0]['value'].'</p>';
				}

				if (!empty($val->field_section_heading_3[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_3[LANGUAGE_NONE][0]['value'])) {
					$section_html .=		(!empty($ft3_ico) ?
															'<div class="icon">'.
																$ft3_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_3[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_3[LANGUAGE_NONE][0]['value'].'</p>';
				}

				if (!empty($val->field_section_heading_4[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_4[LANGUAGE_NONE][0]['value'])) {
					$section_html .=		(!empty($ft4_ico) ?
															'<div class="icon">'.
																$ft4_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_4[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_4[LANGUAGE_NONE][0]['value'].'</p>';
				}

				if (!empty($val->field_section_heading_5[LANGUAGE_NONE][0]['value']) && !empty($val->field_section_copy_5[LANGUAGE_NONE][0]['value'])) {
					$section_html .=		(!empty($ft5_ico) ?
															'<div class="icon">'.
																$ft5_ico.'
															</div>' : '').
															'<h3>'.$val->field_section_heading_5[LANGUAGE_NONE][0]['value'].'</h3>
															<p>'.$val->field_section_copy_5[LANGUAGE_NONE][0]['value'].'</p>';
				}

				$section_html .= $links_html;

				$section_html .= '						</div>
														<figure>'.(($img_target_url!='')?'<a href="'.$img_target_url.'" '.$target.'>'.$sec_img.'</a>':$sec_img).'</figure>
													</div>
												</section>';
			}
		}
	}

	return $section_html;
}


function views_section_menu_anchors($sections, $body_id, $body_title) {
	$anchor_html = '';
	if ( isset($body_id) && !empty($body_id) && isset($body_title) && !empty($body_title) ) {
		$anchor_html .= '<a href="#'.$body_id[LANGUAGE_NONE][0]['value'].'"><span>'.$body_title[LANGUAGE_NONE][0]['value'].'</span></a>';
	}

	$exclude = array();
	if (isset($sections) && is_array($sections)) {
		foreach ($sections as $s => $eid) {
			$curr_section = entity_load('field_collection_item', array($eid['value']));
			foreach ($curr_section as $f=>$val) {
				$anchor_html .= '<a href="#'.$val->field_section_id[LANGUAGE_NONE][0]['value'].'"><span>'.$val->field_section_anchor_title[LANGUAGE_NONE][0]['value'].'</span></a>';
			}
		}
	}

	return $anchor_html;
}


/**
 * Creates login form
 *
**/
function views_login_form()
{
	$base_path = base_path();
	$remember_me = ( isset($_COOKIE['location_login_nid']) && !empty($_COOKIE['location_login_nid']) ) ? ' checked="checked"' : '';

	$form_login = '<form method="get" action="'.$base_path.'login-redirect" name="login_form">
									<div class="login-select">
									'.get_login_location_select('login').'
									<button type="submit" name="submit" value="'.t('GO').'" class="button">'.t('GO').'</button>
									</div>
									<div class="login-remember-me">
										<input type="checkbox" id="remember_login_location" name="remember_login_location" value="1"' . $remember_me . '><label for="remember_login_location">'.t('Remember my selection').'</label>
									</div>
									<div class="error"></div>
								</form>';

	return $form_login;
}


/**
 * Creates custom view for Industries Overview page
 *
**/
function views_industry_overview()
{
	global $language;

	$industries_nodes = $project_excludes = array();
	$project_image_opts = array('industry' => NULL,
															'region' => $_SESSION['akamai']['region_tid'],
															'exclude' => NULL,
															'solution' => NULL,
															'parent' => NULL,
															'priority' => 'industry');

	// Get the first level for Industries
	$term_industry =  taxonomy_get_tree(6, 0, 1, FALSE);
	foreach($term_industry as $i=>$industry)
	{
		// Get the node for the main industry category
		$level1_query = db_select('node', 'n');
		$level1_query->join('taxonomy_index', 'ti', 'n.nid = ti.nid');
		$level1_query->fields('n', array('nid'))
								->fields('ti', array('tid'))
								->condition('n.type', 'industries', '=')
								->condition('ti.tid', $industry->tid, '=')
								->condition('n.language', $language->language, '=');

		$level1_query = $level1_query->execute();
		while($main_industry = $level1_query->fetchObject())
		{
		  $level1_node = node_load($main_industry->nid);
			$industries_nodes[$i]['level1'] = $level1_node;
		}

		// Get nodes for the sub-category industry section
		if($language->language == 'en')
		{
			$level2_query = db_select('node', 'n');
			$level2_query->join('taxonomy_index', 'ti', 'n.nid = ti.nid');
			$level2_query->join('taxonomy_term_hierarchy', 'tth', 'ti.tid = tth.tid');
			$level2_query->fields('n', array('nid'))
									->fields('ti', array('tid'))
									->fields('tth', array('parent'))
									->condition('n.type', 'industries', '=')
									->condition('tth.parent', $industry->tid, '=');
			//dpq($level2_query);
			$level2 = $level2_query->execute();
			foreach($level2->fetchAll() as $s=>$sub_industry)
			{
				$level2_node = node_load($sub_industry->nid);
				$industries_nodes[$i]['level2'][$s]['industry'] = $level2_node;
				// Get a project image to use with this view
				$project_image_opts['industry'] = $sub_industry->tid;
				//$image = get_project_image($sub_industry->tid, $_SESSION['akamai']['region_tid']);
				$image = get_project_random($project_image_opts);
				$industries_nodes[$i]['level2'][$s]['project_image'] = $image;
			}
		}
		else
		{
			// LOTE does not go further than level 1
			// Get a project image to use with this view
			$project_image_opts['parent'] = $industry->tid;
			$project_image_opts['exclude'] = $project_excludes;

			$image = get_project_random($project_image_opts);
			$industries_nodes[$i]['indimage'] = $image;
			$project_excludes[] = $image->nid;
		}
	}

	// Create the grid HTML
	$industries_html = '';
	if($language->language == LANGUAGE_NONE || $language->language == 'en')
	{
		for($i=0, $n=sizeof($industries_nodes); $i<$n; $i++)
		{
			$industries_html .= '<div class="column one-third'.(($i+1) == $n ? ' clear-after':'').'">
														<h2>'.l($industries_nodes[$i]['level1']->title, 'node/'.$industries_nodes[$i]['level1']->nid).'<i class="fa fa-angle-down"></i>'."</h2>\n";

			foreach($industries_nodes[$i]['level2'] as $s=>$sub_category)
			{
				$project_image = file_load($sub_category['project_image']->field_grid_image_fid);
				$project_image = theme('image', array('path' => $project_image->uri, 'alt' => $sub_category['project_image']->field_grid_image_alt));
				$industries_html .= '<article>'.
														image_link($project_image, 'node/'.$sub_category['industry']->nid).
														'<h3>'.l($sub_category['industry']->title, 'node/'.$sub_category['industry']->nid).'</h3>'.
														"</article>\n";
			}
			$industries_html .= "</div>\n";
		}
	}
	else
	{
		// Trim the listing for LOTE sites
		for($i=0, $n=sizeof($industries_nodes); $i<$n; $i++)
		{
			$l1link = language_link('node/'.$industries_nodes[$i]['level1']->nid);
			$industries_html .= '<div class="column one-third'.(($i+1) == $n ? ' clear-after':'').'">
														<h2>'.l($industries_nodes[$i]['level1']->title, $l1link).'<i class="fa fa-angle-down"></i>'."</h2>\n";

			$project_image = file_load($industries_nodes[$i]['indimage']->field_grid_image_fid);
			$project_image = theme('image', array('path' => $project_image->uri, 'alt' => $industries_nodes[$i]['indimage']->field_grid_image_alt));
			$industries_html .= '<article>'.
													image_link($project_image, $l1link).
													"</article>\n";

			$industries_html .= "</div>\n";
		}
	}

	return $industries_html;
}


/**
 * Show 3 org types
 *
**/
function views_org_type_overview()
{
  global $language;
	$org_nodes = array();

	// Get the first level for Industries
	$term_orgs = taxonomy_get_tree(16, 0, 1, FALSE);
	foreach($term_orgs as $i=>$org)
	{
		// Get the node for the main industry category
		$level1_query = db_select('node', 'n');
		$level1_query->join('taxonomy_index', 'ti', 'n.nid = ti.nid');
		$level1_query->fields('n', array('nid'))
								->fields('ti', array('tid'))
								->condition('n.type', 'industries', '=')
								->condition('ti.tid', $org->tid, '=')
                ->condition('n.language', $language->language);
//		dpq($level1_query, 'qry org type');

		$level1_query = $level1_query->execute();
		while($main_industry = $level1_query->fetchObject())
		{
		  $level1_node = node_load($main_industry->nid);
			$org_nodes[$i]['level1'] = $level1_node;
			$image = get_project_image($org->tid, $_SESSION['akamai']['region_tid']);
			$org_nodes[$i]['project_image'] = $image;
		}
	}

	// Create the grid HTML
	$org_types_html = '<h2>'.t('Organization Types').'</h2>';
	for($i=0, $n=sizeof($org_nodes); $i<$n; $i++)
	{
		$project_image = file_load($org_nodes[$i]['project_image']->field_grid_image_fid);
		$project_image = theme('image', array('path' => $project_image->uri, 'alt' => $org_nodes['project_image']->field_grid_image_alt));
		$org_types_html .= '<article class="article-highlight article-highlight-overview' . (($i+1) % 3 == 0 ? ' clear-after' : '') . '">'.
												image_link($project_image, 'node/'.$org_nodes[$i]['level1']->nid).
												'<h3>'.l($org_nodes[$i]['level1']->title, 'node/'.$org_nodes[$i]['level1']->nid).'</h3>'.
												"</article>\n";
	}

	return $org_types_html;
}


/**
 * Produce homepage banner
 *
**/
function views_homepage_banner($collection)
{

	// Banner will appear according to preferred weight (low to high), but regionality should take precedence
	$display_banner = array();
	if(isset($collection[LANGUAGE_NONE]))
	{
		$generic_display_banner = NULL;
		$firstBanner = true;
		$demandBaseMatch = false;
		
		foreach ($collection[LANGUAGE_NONE] as $b => $fields)
		{
      $field_collection_id = $collection[LANGUAGE_NONE][$b]['value'];
			$banner = entity_load('field_collection_item', array($field_collection_id));
			foreach($banner as $f=>$val)
			{
				$image = $val->field_banner_image[LANGUAGE_NONE][0]['uri'];
				$hex = $val->field_banner_hex_code[LANGUAGE_NONE][0]['value'];
				$head1 = $val->field_banner_heading_1[LANGUAGE_NONE][0]['value'];
				$head_hex = isset($val->field_banner_heading_hex_code[LANGUAGE_NONE][0]['value']) ? $val->field_banner_heading_hex_code[LANGUAGE_NONE][0]['value'] : NULL;
				$caption = isset($val->field_banner_caption[LANGUAGE_NONE][0]['value']) ? $val->field_banner_caption[LANGUAGE_NONE][0]['value'] : NULL;
				$control_text = $val->field_banner_control_text[LANGUAGE_NONE][0]['value'];
				$orange_bar = $val->field_banner_orange_bar[LANGUAGE_NONE][0]['value'];
				$region_tid = $val->field_banner_region[LANGUAGE_NONE];
				$industry_sector = isset($val->field_project_industry[LANGUAGE_NONE][0]['tid']) ? $val->field_project_industry[LANGUAGE_NONE][0]['tid'] : false;
			}
			
			if(is_current_region($region_tid) && (demandbase_user_sector($industry_sector)===true) )
			{
				// If the user falls into DemandBase specific industry 
				$display_banner[] = array(
          'id' => $field_collection_id,
          'image' => file_create_url($image),
          'banner_hex' => $hex,
          'head1' => $head1,
          'head_hex' => $head_hex,
          'caption' => $caption,
          'control_text' => $control_text,
          'orange_bar' => $orange_bar,
          'region' => $region_tid
        );
				$demandBaseMatch = true;
			}
			elseif(is_current_region($region_tid) && $industry_sector == false) {
				// If the slide is not assigned a DemandBase Industry
				$generic_display_banner[] = array(
          'id' => $field_collection_id,
          'image' => file_create_url($image),
          'banner_hex' => $hex,
          'head1' => $head1,
          'head_hex' => $head_hex,
          'caption' => $caption,
          'control_text' => $control_text,
          'orange_bar' => $orange_bar,
          'region' => $region_tid
        );
													
				// If this is not the first banner and no DemandBase indusry_sector is chosen, display as generic slide
				// to all visitors whether they are a demandbase match or not
				if (!$firstBanner) {
					$display_banner[] = array(
            'id' => $field_collection_id,
            'image' => file_create_url($image),
            'banner_hex' => $hex,
            'head1' => $head1,
            'head_hex' => $head_hex,
            'caption' => $caption,
            'control_text' => $control_text,
            'orange_bar' => $orange_bar,
            'region' => $region_tid
          );
				}
			}
			$firstBanner = false;
		}
	}
	// UPDATE: part of larger temporary adjustment, if we're empty - use the first banner
	// UPDATE 2: If demandbase industry specific banner empty, return generic banner
	if(!$demandBaseMatch)
		return $generic_display_banner;

	return $display_banner;

}


/**
 * Produce banner for current page
 *
**/
function views_page_banner($collection)
{
	// Banner will appear according to preferred weight (low to high), but regionality should take precedence
	$display_banner = array();
	if(isset($collection[LANGUAGE_NONE]))
	{
		foreach ($collection[LANGUAGE_NONE] as $b => $fields)
		{
			$banner = entity_load('field_collection_item', array($collection[LANGUAGE_NONE][$b]['value']));
			foreach($banner as $f=>$val)
			{
				$image = $val->field_banner_image[LANGUAGE_NONE][0]['uri'];
				$head1 = $val->field_banner_heading_1[LANGUAGE_NONE][0]['value'];
				$head2 = $val->field_banner_heading_2[LANGUAGE_NONE][0]['value'];
				$cta = $val->field_banner_button_text[LANGUAGE_NONE][0]['value'];
				$cta_link = $val->field_banner_button_url[LANGUAGE_NONE][0]['url'];
				$caption = $val->field_banner_caption[LANGUAGE_NONE][0]['value'];
				$region_tid = $val->field_banner_region[LANGUAGE_NONE];//[0]['tid'];
	    }
	    $has_container = (!empty($head1) || !empty($head2) || !empty($cta) || !empty($cta_link) || !empty($caption)) ? true : false;
	    $xlg_banner = (!empty($head1) && !empty($head2) && !empty($cta) && !empty($cta_link)) ? true : false;
	    $cta_button = '';
			if (!empty($cta) && !empty($cta_link))
			{
				$ext = url_is_external($cta_link) === TRUE;
				$btn_opts = array('external' => $ext,
													'attributes' => array('class' => 'button'));

				if($ext)
					$btn_opts['attributes']['target'] = '_blank';

				$cta_button = l($cta, $cta_link, $btn_opts);
			}
			$display_banner = array('image' => (!empty($image) ? file_create_url($image) : ''),
															'head1' => $head1,
															'head2' => $head2,
															'cta_button' => $cta_button,
															'caption' => $caption,
															'has_container' => $has_container,
															'xlg_banner' => $xlg_banner,
															'region' => $region_tid);

	    // Now some simple region test logic to see if we stop here...
			if(is_current_region($region_tid))
			{
				break;
			}
		}
	}

	return $display_banner;

}

/**
 * Produce plain banner for current page
 *
**/
function views_page_banner_plain($image)
{
	$display_banner = array('image' => (!empty($image['uri']) ? file_create_url($image['uri']) : ''),
													'head1' => '',
													'head2' => '',
													'cta_button' => '',
													'caption' => '',
													'has_container' => false,
													'region' => '');
	return $display_banner;
}

/**
 * Produces nice custom project header
 * Would be a little messy to attempt with views/grouping & translation
 *
**/
function views_project_heading($node)
{
	$ind = taxonomy_term_load($node->field_project_industry[LANGUAGE_NONE][0]['tid']);
	$project_heading = '<h1>'.$node->field_project_sub_heading[LANGUAGE_NONE][0]['value'].'</h1>';
	$project_heading .= '<h3>';
	$project_heading .= ( !empty($node->title) || !empty($ind->name) ) ? '<span>' : '';

	$project_heading .= (!empty($node->title)) ? t('Project name: ').$node->title : '';
	$project_heading .= ( !empty($node->title) && !empty($ind->name) ) ? '&nbsp;|&nbsp;' : '';
	$project_heading .= (!empty($ind->name)) ? t('Industry: ').$ind->name : '';

	$project_heading .= ( !empty($node->title) || !empty($ind->name) ) ? '</span>' : '';

	$project_heading .= ( !empty($node->field_project_size[LANGUAGE_NONE][0]['value']) || !empty($node->field_project_country[LANGUAGE_NONE][0]['value']) ) ? '<span>' : '';

	$project_heading .= (!empty($node->field_project_size[LANGUAGE_NONE][0]['value'])) ? t('Project size: ').$node->field_project_size[LANGUAGE_NONE][0]['value'] : '';
	$project_heading .= ( !empty($node->field_project_size[LANGUAGE_NONE][0]['value']) && !empty($node->field_project_country[LANGUAGE_NONE][0]['value']) ) ? '&nbsp;|&nbsp;' : '';
	$project_heading .= (!empty($node->field_project_country[LANGUAGE_NONE][0]['value'])) ? t('Location: ').$node->field_project_country[LANGUAGE_NONE][0]['value'] : '';

	$project_heading .= ( !empty($node->field_project_size[LANGUAGE_NONE][0]['value']) || !empty($node->field_project_country[LANGUAGE_NONE][0]['value']) ) ? '</span>' : '';

	$project_heading .= '</h3>';

	return $project_heading;

}

/**
 * Produce 3x grid of project highlights for use in page body
 *
**/
function views_project_highlights($industry_tid = NULL, $solution_tid = NULL, $nid_exclude = NULL)
{
	// Left/Middle/Right sections
	$p_opts = array('industry' => $industry_tid, 'region' => $_SESSION['akamai']['region_info']->tid, 'priority' => 'industry', 'exclude' => array());
	if($nid_exclude)
		$p_opts['exclude'][] = $nid_exclude;

	if($solution_tid)
	{
		$p_opts['solution'] = $solution_tid;
		$p_opts['priority'] = 'solution';
	}

	$left_project = get_project_random($p_opts);
	if($left_project)
	{
		$left_p_image = theme('image', array('path' => file_load($left_project->field_grid_image_fid)->uri,
																				 'alt' => $left_project->field_grid_image_alt));
		$left_ind = taxonomy_term_load($left_project->field_project_industry_tid);
		$lp_html = '<article class="article-highlight article-highlight-quote">
									<div class="image">
										<h4>'.$left_ind->name.'</h4>
										<div class="value">'.$left_project->field_project_size_value.'</div>'.
										$left_p_image.
									'</div>
									<figure>
										<h3>'.l($left_project->title, 'node/'.$left_project->nid).'</h3>
										<blockquote>'.$left_project->field_project_pull_quote_value.'</blockquote>
										<figcaption>'.$left_project->field_pull_quote_credit_value.'</figcaption>
									</figure>
								</article>';
	}
	else
	{
		$lp_html = '';
	}

	if($left_project)
		$p_opts['exclude'][] = $left_project->nid;

	$middle_project = get_project_random($p_opts);
	if($middle_project)
	{
		$middle_p_image = theme('image', array('path' => file_load($middle_project->field_grid_image_fid)->uri,
																			      'alt' => $middle_project->field_grid_image_alt));
		$middle_ind = taxonomy_term_load($middle_project->field_project_industry_tid);
		$mp_html = '<article class="article-highlight article-highlight-quote">
									<div class="image">
										<h4>'.$middle_ind->name.'</h4>
										<div class="value">'.$middle_project->field_project_size_value.'</div>'.
										$middle_p_image.
									'</div>
									<figure>
										<h3>'.l($middle_project->title, 'node/'.$middle_project->nid).'</h3>
										<blockquote>'.$middle_project->field_project_pull_quote_value.'</blockquote>
										<figcaption>'.$middle_project->field_pull_quote_credit_value.'</figcaption>
									</figure>
								</article>';
	}
	else
	{
		$mp_html = '';
	}

	if($middle_project)
		$p_opts['exclude'][] = $middle_project->nid;

	$right_project = get_project_random($p_opts);
	if($right_project)
	{
		$right_p_image = theme('image', array('path' => file_load($right_project->field_grid_image_fid)->uri,
																			      'alt' => $right_project->field_grid_image_alt));
		$right_ind = taxonomy_term_load($right_project->field_project_industry_tid);
		$rp_html = '<article class="article-highlight article-highlight-quote clear-after">
									<div class="image">
										<h4>'.$right_ind->name.'</h4>
										<div class="value">'.$right_project->field_project_size_value.'</div>'.
										$right_p_image.
									'</div>
									<figure>
										<h3>'.l($right_project->title, 'node/'.$right_project->nid).'</h3>
										<blockquote>'.$right_project->field_project_pull_quote_value.'</blockquote>
										<figcaption>'.$right_project->field_pull_quote_credit_value.'</figcaption>
									</figure>
								</article>';
	}
	else
	{
		$rp_html = '';
	}

	return $lp_html.$mp_html.$rp_html;
}

/**
 * Produce 3x grid of project highlights for use in page body
 *
**/
function views_register()
{
	$base_path = base_path();
	$top = language_block('78', 'register');
	$top_left = language_block('79', 'register');
	$top_right = language_block('80', 'register');
	$tree_left = language_block('81', 'register');
	$tree_right = language_block('82', 'register');

	$register_html = '';
	$register_html .= '<div class="tree-top"><div class="button">' . $top['content'] . '</div></div>' . "\r\n";
	$register_html .= '<div class="tree-top-branch"><div class="divider"></div></div>' . "\r\n";
	$register_html .= '<div class="column one-third">' . "\r\n";
	$register_html .= '<div class="button button-white">' . $top_left['content'] . '</div>' . "\r\n";
	$register_html .= '<div class="hidden">' . "\r\n";
	$register_html .= '<div class="column-branch"><div class="divider"></div></div>' . "\r\n";
	$register_html .= $tree_left['content'] . "\r\n";
	$register_html .=  '<form method="get" action="'.$base_path.'register-redirect" name="register_form">' . "\r\n";
	$register_html .= get_login_location_select() . '<button type="submit" name="submit" value="'.t('Go').'" class="button">'.t('Go').'</button>' . "\r\n";
	$register_html .= '<div class="error"></div>' . "\r\n";
	$register_html .=  '</form>' . "\r\n";
	$register_html .=  '</div>' . "\r\n";
	$register_html .= '</div>' . "\r\n";
	$register_html .= '<div class="column one-third tree-divider">' . "\r\n";
	$register_html .= '<div class="circle">'.t('OR').'</div>' . "\r\n";
	$register_html .= '</div>' . "\r\n";
	$register_html .= '<div class="column one-third">' . "\r\n";
	$register_html .= '<div class="button button-white">' . $top_right['content'] . '</div>' . "\r\n";
	$register_html .= '<div class="hidden">' . "\r\n";
	$register_html .= '<div class="column-branch"><div class="divider"></div></div>' . "\r\n";
	$register_html .= $tree_right['content'] . "\r\n";
	$register_html .= '</div>' . "\r\n";
	$register_html .= '</div>' . "\r\n";

	return $register_html;
}

/**
 * Produce resources overview listing
 *
**/
function views_resources_listing()
{
	$resources_html = '';

	$webinars = views_get_view_result('resource_overview_webinars', 'nid_webinars');
	$videos = views_get_view_result('resource_oveview_videos', 'nid_videos');
	$blogs = views_get_view_result('resource_overview_blog', 'nid_blogs');
	$other1 = views_get_view_result('resource_overview_other', 'nid_other_wp');
	$other2 = views_get_view_result('resource_overview_other', 'nid_other_fs');
	$other3 = views_get_view_result('resource_overview_other', 'nid_other_brochure');

	if(($w = sizeof($webinars)) > 0)
	{
		$resources_html .= '<section class="content with-headline">
													<div class="container clear">
														<h2>'.t('Webinars').'</h2>';
		for($i=0; $i<$w; $i++)
		{
			$cur_node = node_load($webinars[$i]->nid);
			$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
			$imgh4 = '';
			if($cur_term->name == 'Webinar')
			{
				if(!empty($cur_node->field_article_date))
				{
					$start = strtotime($cur_node->field_article_date[LANGUAGE_NONE][0]['value']);
					$end = strtotime($cur_node->field_article_date[LANGUAGE_NONE][0]['value2']);
					if($end < time())
					{
						$imgh4 = strtoupper(t('On Demand'));
					}
					elseif($start != $end)
					{
						$sm = date("n", $start);
						$em = date("n", $end);
						if((int)$em > (int)$sm)
						{
							$imgh4 = date("M j-", $start).date("M j, Y", $end);
						}
						else
						{
							$imgh4 = date("M j-", $start).date("j, Y", $end);
						}
					}
					else
					{
						$imgh4 = date("M j, Y", $start);
					}
				}
			}
			else
			{
				$imgh4 = $cur_term->name;
			}
		  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
											'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
		  $cur_img = theme('image', $cur_img);
			$blank = $cur_node->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1' ? '_blank' : '';

			$resources_html .= '<article class="article-highlight">
														<div class="image">'.
															(!empty($imgh4) ? '<h4><time datetime="'.date('Y-m-d', $start).'">'.strtoupper($imgh4).'</time></h4>' : '').
															image_link($cur_img, $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
														</div>
														<h3>'.
															l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
														</h3>
													</article>
													';
		}
		$resources_html .= l(t('View all webinars'), 'node/1313', array('attributes' => array('class' => 'button'))).'
											</div>
										</section>';
	}

	if(($w = sizeof($videos)) > 0)
	{
		$resources_html .= '<section class="content with-headline">
													<div class="container clear">
														<h2>'.t('Videos').'</h2>';
		for($i=0; $i<$w; $i++)
		{
			$cur_node = node_load($videos[$i]->nid);
			$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
			$imgh4 = '';

		  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
											'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
		  $cur_img = theme('image', $cur_img);

			//Maybe in the future load this but these are hardcoded into the view config as 425x239 as well
			//$width = $cur_node->{field_field_resources_video}[0]['rendered']['#display']['settings']['width'];
			//$height = $cur_node->{field_field_resources_video}[0]['rendered']['#display']['settings']['height'];
			$vurl = 'brightcove_dialog/nojs/video/425/239/node/' . $videos[$i]->nid . '/field_resources_video/0';
			$l_opts = array('attributes' => array('rel' => 'field_resources_video', 'class' => array('field_resources_video use-ajax')));

			$resources_html .= '<article class="article-highlight">
														<div class="image">'.
															(!empty($cur_term->name) ? '<h4>'.strtoupper($cur_term->name).'</h4>' : '').
															image_link($cur_img, $vurl, $l_opts).'
														</div>
														<h3>'.
															l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $vurl, $l_opts).'</h3>
													</article>
													';
		}
		$resources_html .= l(t('View all videos'), 'node/1312', array('attributes' => array('class' => 'button'))).'
											</div>
										</section>';
	}

	if(($w = sizeof($blogs)) > 0)
	{
		$resources_html .= '<section class="content with-headline">
													<div class="container clear">
														<h2>'.t('Blog').'</h2>';
		for($i=0; $i<$w; $i++)
		{
			$cur_node = node_load($blogs[$i]->nid);
			$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
			$imgh4 = '';

		  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
											'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
		  $cur_img = theme('image', $cur_img);

			$resources_html .= '<article class="article-highlight">
														<div class="image">'.
															(!empty($cur_term->name) ? '<h4>'.strtoupper($cur_term->name).'</h4>' : '').
															image_link($cur_img, $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => '_blank'))).'
														</div>
														<h3>'.
															l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => '_blank'))).'
														</h3>
													</article>
													';
		}
		$resources_html .= l(t('View all blog posts'), 'http://www.aconex.com/blogs', array('attributes' => array('class' => 'button', 'target' => '_blank'))).'
											</div>
										</section>';
	}

	$resources_html .= '<section class="content with-headline">
											<div class="container clear">
												<h2>'.t('Other Resources').'</h2>';

	for($i=0, $n=sizeof($other1); $i<$n; $i++)
	{
		$cur_node = node_load($other1[$i]->nid);
		$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
		$imgh4 = '';

	  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
										'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
	  $cur_img = theme('image', $cur_img);
		$blank = $cur_node->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1' ? '_blank' : '';

		$resources_html .= '<article class="article-highlight">
													<div class="image">'.
														(!empty($cur_term->name) ? '<h4>'.strtoupper($cur_term->name).'</h4>' : '').
														image_link($cur_img, $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</div>
													<h3>'.
														l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</h3>
												</article>
												';
	}

	for($i=0, $n=sizeof($other2); $i<$n; $i++)
	{
		$cur_node = node_load($other2[$i]->nid);
		$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
		$imgh4 = '';

	  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
										'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
	  $cur_img = theme('image', $cur_img);
		$blank = $cur_node->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1' ? '_blank' : '';

		$resources_html .= '<article class="article-highlight">
													<div class="image">'.
														(!empty($cur_term->name) ? '<h4>'.strtoupper($cur_term->name).'</h4>' : '').
														image_link($cur_img, $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</div>
													<h3>'.
														l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</h3>
												</article>
												';
	}

	for($i=0, $n=sizeof($other3); $i<$n; $i++)
	{
		$cur_node = node_load($other3[$i]->nid);
		$cur_term = taxonomy_term_load($cur_node->field_resource_type[LANGUAGE_NONE][0]['tid']);
		$imgh4 = '';

	  $cur_img = array('path' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['uri'],
										'alt' => $cur_node->field_grid_image[LANGUAGE_NONE][0]['alt']);
	  $cur_img = theme('image', $cur_img);
		$blank = $cur_node->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1' ? '_blank' : '';

		$resources_html .= '<article class="article-highlight">
													<div class="image">'.
														(!empty($cur_term->name) ? '<h4>'.strtoupper($cur_term->name).'</h4>' : '').
														image_link($cur_img, $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</div>
													<h3>'.
														l($cur_node->field_resource_preview_title[LANGUAGE_NONE][0]['value'], $cur_node->field_resources_title_link[LANGUAGE_NONE][0]['value'], array('attributes' => array('target' => $blank))).'
													</h3>
												</article>
												';
	}

	$resources_html .= '</div>
									</section>';

	return $resources_html;
}

/**
 * Creates a custom view for relevent articles to the current category
 *
 * @param: int
 * @return: array
**/
function views_body_resource_offers($resources)
{
	$offer_left = $offer_middle = $offer_right = '';
	if(sizeof($resources) > 0)
	{
		$region_break = FALSE;
		$v_opts = array('attributes' => array('rel' => 'field_resources_video', 'class' => array('field_resources_video use-ajax')));
		foreach ($resources as $r => $resource)
		{
		  $entity = entity_load('field_collection_item', array($resource['value']));
			// First check if this is the region we want
			foreach($entity as $eid => $field)
			{
				// region is a multi-select
				foreach($field->field_region[LANGUAGE_NONE] as $rg => $region)
				{
					if(is_current_region($region['tid']) || $region['tid'] == '1')
					{
						// 3 resource info parts
					  $resource_left = node_load($field->field_body_cta_left[LANGUAGE_NONE][0]['nid']);
					  $llink_opts = array();
						$lt_term = taxonomy_term_load($resource_left->field_resource_type[LANGUAGE_NONE][0]['tid']);
					  $lt_img = array('path' => $resource_left->field_grid_image[LANGUAGE_NONE][0]['uri'],
													  'alt' => $resource_left->field_grid_image[LANGUAGE_NONE][0]['alt']);
					  $lt_img = theme('image', $lt_img);

						if($lt_term->name == 'Video')
						{
							$rurl = 'brightcove_dialog/nojs/video/425/239/node/' . $resource_left->nid . '/field_resources_video/0';
							$llink_opts = $v_opts;
						}
						elseif(!empty($resource_left->field_resources_title_link))
						{
							$rurl = $resource_left->field_resources_title_link[LANGUAGE_NONE][0]['value'];
						}
						else
						{
							$rurl = 'node/'.$resource_left->nid;
						}
						$lt_img = image_link($lt_img, $rurl, $llink_opts);

						$offer_left = '<article class="article-highlight">
															<div class="image">'.
																(!empty($lt_term) ? '<h4>'.strtoupper($lt_term->name).'</h4>' : '').
																$lt_img.
													 '</div>
														<h3>'.l((string)$resource_left->field_cta_headline[LANGUAGE_NONE][0]['value'], $rurl, $llink_opts).'</h3>
														<p>'.$resource_left->field_cta_body[LANGUAGE_NONE][0]['value'].'</p>'.
													"</article>\n";

					  $resource_middle = node_load($field->field_body_cta_middle[LANGUAGE_NONE][0]['nid']);
					  $mlink_opts = array();
						$md_term = taxonomy_term_load($resource_middle->field_resource_type[LANGUAGE_NONE][0]['tid']);
					  $md_img = array('path' => $resource_middle->field_grid_image[LANGUAGE_NONE][0]['uri'],
													  'alt' => $resource_middle->field_grid_image[LANGUAGE_NONE][0]['alt']);
					  $md_img = theme('image', $md_img);

						if($md_term->name == 'Video')
						{
							$rurl = 'brightcove_dialog/nojs/video/425/239/node/' . $resource_middle->nid . '/field_resources_video/0';
							$mlink_opts = $v_opts;
						}
						elseif(!empty($resource_middle->field_resources_title_link))
						{
							$rurl = $resource_middle->field_resources_title_link[LANGUAGE_NONE][0]['value'];
						}
						else
						{
							$rurl = 'node/'.$resource_middle->nid;
						}
						$md_img = image_link($md_img, $rurl, $mlink_opts);

						$offer_middle = '<article class="article-highlight">
															<div class="image">'.
																(!empty($md_term) ? '<h4>'.strtoupper($md_term->name).'</h4>' : '').
																$md_img.
													 '</div>
														<h3>'.l($resource_middle->field_cta_headline[LANGUAGE_NONE][0]['value'], $rurl, $mlink_opts).'</h3>
														<p>'.$resource_middle->field_cta_body[LANGUAGE_NONE][0]['value'].'</p>'.
													"</article>\n";

					  $resource_right = node_load($field->field_body_cta_right[LANGUAGE_NONE][0]['nid']);
					  $rlink_opts = array();
						$rt_img = array('path' => $resource_right->field_grid_image[LANGUAGE_NONE][0]['uri'],
													  'alt' => $resource_right->field_grid_image[LANGUAGE_NONE][0]['alt']);
						$rt_img = theme('image', $rt_img);
						$rurl = !empty($resource_right->field_resources_title_link[LANGUAGE_NONE][0]['value']) ? trim($resource_right->field_resources_title_link[LANGUAGE_NONE][0]['value'], '/') : 'node/'.$resource_right->nid;
						if($resource_right->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] == '1')
							$rlink_opts['attributes']['target'] = '_blank';

				  	// Handle event vs. resource in right column
						if($resource_right->type == 'events')
						{
							$rt_term = new stdClass;
							$rt_term->name = t('Event');
							$rt_h3 = $resource_right->field_resource_preview_title[LANGUAGE_NONE][0]['value'];
							$rt_body = $resource_right->field_resource_short_description[LANGUAGE_NONE][0]['value'];
						}
						else
						{
							$rt_term = taxonomy_term_load($resource_right->field_resource_type[LANGUAGE_NONE][0]['tid']);
							$rt_h3 = (string)$resource_right->field_cta_headline[LANGUAGE_NONE][0]['value'];
							$rt_body = $resource_right->field_cta_body[LANGUAGE_NONE][0]['value'];

							if($rt_term->name == 'Video')
							{
								$rurl = 'brightcove_dialog/nojs/video/425/239/node/' . $resource_right->nid . '/field_resources_video/0';
								$rlink_opts = $v_opts;
							}
							elseif(!empty($resource_right->field_resources_title_link))
							{
								$rurl = $resource_right->field_resources_title_link[LANGUAGE_NONE][0]['value'];
							}
							else
							{
								$rurl = 'node/'.$resource_middle->nid;
							}
						}
						$rt_img = image_link($rt_img, $rurl, $rlink_opts);

						$offer_right = '<article class="article-highlight clear-after">
															<div class="image">'.
																(!empty($rt_term) ? '<h4>'.strtoupper($rt_term->name).'</h4>' : '').
																$rt_img.
													 '</div>
														<h3>'.l($rt_h3, $rurl, $rlink_opts).'</h3>
														<p>'.$rt_body.'</p>'.
													"</article>\n";

						if(is_current_region($region['tid']))
							$region_break = TRUE;
					}
					if($region_break)
						break;
				}
				if($region_break)
					break;
			}
			if($region_break)
				break;
		}
	}

	return $offer_left.$offer_middle.$offer_right;
}

/**
 * Creates a custom view for relevent articles to the current category
 *
 * @param: int
 * @return: array
**/
function views_solutions_overview()
{
	global $language;

	$sol_nodes = array();

	// Language qualifier
	$language_or = db_or();
	$language_or->condition('n.language', $language->language, '=');
	$language_or->condition('n.language', LANGUAGE_NONE, '=');

	// Get solutions types
	$sols_query = db_select('node', 'n');
	$sols_query->join('field_data_field_is_solution', 's', 'n.nid = s.entity_id');
	$sols_query->leftJoin('field_data_field_solution_order', 'so', 'n.nid = so.entity_id');
	$sols_query->fields('n', array('nid'))
							->condition('n.type', 'page', '=')
							->condition('s.field_is_solution_value', '1', '=')
							->condition($language_or)
							->orderBy('so.field_solution_order_value', 'ASC');
	$solutions = $sols_query->execute();

	$solutions_html = '';
	if($solutions->rowCount() > 0)
	{
		$i = 1;
		while($solution = $solutions->fetchObject())
		{
			$node = node_load($solution->nid);
			$solution_img = file_load($node->field_solution_icon[LANGUAGE_NONE][0]['fid']);
			$solution_img_hover = file_load($node->field_solution_icon_hover[LANGUAGE_NONE][0]['fid']);
			$simg = theme('image', array('path' => $solution_img->uri, 'alt' => ''/* $solution_img->field_solution_icon_alt */, 'attributes' => array('data-hover' => file_create_url($solution_img_hover->uri))));

			$solutions_html .= '<article class="article-highlight article-highlight-small'.(($i % 4) == 0 ? ' clear-after' : '').'">'.
														image_link($simg, 'node/'.$node->nid, array('attributes' => array('class' => 'icon'))).
														'<h3>'.l($node->field_solution_name[LANGUAGE_NONE][0]['value'],  'node/'.$node->nid).'</h3>'.
														'<p>'.$node->field_solution_tagline[LANGUAGE_NONE][0]['value'].'</p>'.
													"</article>\n";
			$i++;
		}
	}
	return $solutions_html;
}


// Borrowed from D6 mod - not used and here for reference

/**
 * Get the nodes in a region using country and content type
 * @param String $ctype
 * @param String $table
 */
function get_client_grid_nodes($token = "+"){
	$regional_clients = get_nodes_by_region_content_type('client','field_region','','',get_user_region_tid());
	$val = "";
	if(!empty($regional_clients)){
		$val = implode($token, $regional_clients);
	}
	return $val;
}

function get_nodes_by_region_content_type($ctype = "",$field = "",$additional_table = "",$additional_where = "",$region_tid = 1){

	$CID = "get_nodes_by_region_".md5("content_type_".$ctype.$field.$additional_table.$additional_where.$region_tid);
	if(($cache = cache_get($CID)) && !empty($cache->data)) {
		return unserialize($cache->data);
	}

	$region_table_name = "";
	$condition = "";
	if($field != ""){
		$region_table_name = ",content_".$field." cc ";
	}

	$sql = "SELECT DISTINCT(n.nid) FROM node n ".$region_table_name.$additional_table.",term_data td, term_hierarchy th WHERE 1=1 AND n.status = 1 ";
	if($ctype){
		$sql .= "AND n.type='".$ctype."' ";
	}

	if($region_table_name != "" && $field != ""){
		if($region_tid){
			$sql .= "AND n.vid=cc.vid AND cc.".$field."_value = ".$region_tid;
		}else if(!$additional_where && !$additional_table){
			$sql .= "AND n.vid=cc.vid AND cc.".$field."_value = 1";
		}
	}
	if($additional_where){
		$sql .= " ".$additional_where;
	}

	$result = db_query($sql);
	while( $row = db_fetch_array($result)){
		$all_nodes[] = $row['nid'];
	}

	$result = false;
	if(count($all_nodes) > 0){
		$result = $all_nodes;
	}

	cache_set($CID, serialize($result), 'cache', CACHE_TEMPORARY);
	return $result;
}
