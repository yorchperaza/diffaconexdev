<?php

/**
 * Create translated block
 *
 *
**/
function language_block($block_id, $region = '')
{
	$block = '';
	if(module_exists('i18n_block'))
	{
		// This had worked but for some reason upon pushing it - block_list no longer pulls language content
		//$block = render_i18n_block('block_'.$block_id, $region);
		$block['content'] = render_language_block($block_id);
	}
	else
	{
		$block = module_invoke('block', 'block_view', $block_id);
	}

	return $block;
}

/**
 * Create link to homepage for specific language
 * Because the Aconex language naming scheme selected doesn't necessarily match the standard
 *
**/
function language_homepage()
{
	global $base_url, $language;

  $home_url = $base_url.'/';
  switch($language->language)
  {
	  case 'en':
	  // English - append nothing
	  break;
	  // non-traditional Chinese
	  case 'zh-hans':
	  	$home_url .= 'cn/';
	  break;
	  // Japanese
	  case 'ja':
	  	$home_url .= 'jp/';
	  break;
	  default:
	  	$home_url .= $language->language.'/';
  }

  return $home_url;
}

/**
 * Create link of translated menu
 *
 *
**/
function language_menu($menu_name)
{
  // Get the menu tree
  $menu_links = menu_tree($menu_name);
  // reform the array to be i18n_menu compatible
  $l_menu_links = array();
  foreach ($menu_links as $key => $value) {
    if (isset($value['#original_link'])) {
       $l_menu_links[$key]['link'] = $value['#original_link'];
    }
  }
  // localize the menu
  if (function_exists('i18n_menu_localize_tree')) {
    $l_menu_links = i18n_menu_localize_tree($l_menu_links);
  }
  return $l_menu_links;
}

/**
 * Create link of translated content if exists
 *
 *
**/
function language_link($node_path)
{
	global $language;

	// Return as default in case page is not yet translated
	$tlink = $node_path;
	if (function_exists('translation_path_get_translations')) {
		$tpaths = translation_path_get_translations($node_path);
	}

	if(!empty($tpaths))
		$tlink = $tpaths[$language->language];

	return $tlink;
}

/**
 * Create link of translated content if exists
 *
 *
**/
function language_node($node_id)
{
	global $language;

	// Return as default in case page is not yet translated
	$tnid = new StdClass;
	$tnid->nid = $node_id;
	if (function_exists('translation_node_get_translations')) {
		$tnodes = translation_node_get_translations($node_id);
	}

	if(!empty($tnodes))
		$tnid = $tnodes[$language->language];

	return $tnid;
}

/**
 * Create block of translated content if exists
 *
 *
**/
function render_language_block($block_id){
	$lblock = block_load('block', $block_id);
	$block_content = _block_render_blocks(array($lblock));
	$build = _block_get_renderable_array($block_content);

	return $build['block_'.$block_id]['#markup'];
}

/**
 * Create block of translated content if exists
 *
 *
**/
function render_i18n_block($block_id, $region = "hidden"){
	if ($list = block_list($region)) {
		foreach ($list as $key => $block) {
			if ($block_id == $key){
				return array('content' => $block->content['#markup']);
				//return theme('block', array($block->content));
			}
		}
	}
}