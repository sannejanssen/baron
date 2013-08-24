<?php

/**
 * @file
 * Plugin to handle donwload brochures.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Education block download brochure'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the brochure download block.
 */
function thomas_more_brochure_download_content_type_render($subtype, $conf, $panel_args) {
  $content = '';

  $node = menu_get_object();
  if ($node && $node->type == 'area_of_interest') {

    $brochure = field_get_items('node', $node, 'field_brochure');

    if (!empty($brochure)) {
      $link = l('download', file_create_url($brochure[0]['uri']));
      $content .= '<p>Wil je liever alles op je gemak doornemen, '. $link .' of '. l('vraag de brochure aan', 'contact') .'.</p>';
    }
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'brochure_download';
    $block->title       = 'Brochure';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_brochure_download_content_type_admin_title($subtype, $conf) {
  return t('Education block download brochure');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_brochure_download_content_type_admin_info($subtype, $conf) {
  return t('Education block download brochure');
}
