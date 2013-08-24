<?php

/**
 * @file
 * Plugin to handle eduction links.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Education program block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the education program block.
 */
function thomas_more_education_program_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();
  if ($node && $node->type == 'education') {

    $field_title = field_get_items('node', $node, 'field_program_titel');
    $field_intro = field_get_items('node', $node, 'field_program_intro');
    $field_links = field_get_items('node', $node, 'field_program');

    if (!empty($field_intro)) {
      $content .= '<p>'. $field_intro['0']['safe_value'] .'</p>';
    }

    if (!empty($field_links)) {
      foreach ($field_links as $link) {
        $content .= l($link['title'], $link['url'], array('attributes' => array('class' => array('btn')))) . '<br />';
      }
    }
  }

  if (!empty($content)) {
    $content = '<div class="education-program">'. $content .'</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'education_program';
    $block->title       = $field_title['0']['safe_value'] ;
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_education_program_content_type_admin_title($subtype, $conf) {
  return t('Education program block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_education_program_content_type_admin_info($subtype, $conf) {
  return t('Education program block');
}
