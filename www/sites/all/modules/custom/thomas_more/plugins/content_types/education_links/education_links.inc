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
  'title' => t('Education links block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the education link block.
 */
function thomas_more_education_links_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();
  if ($node && $node->type == 'education' || $node->type == 'specialization') {

    // Left part of the block.
    $field_type = field_get_items('node', $node, 'field_opleidingstype');
    $field_modes = field_get_items('node', $node, 'field_studievormen');
    $field_modes_more = field_get_items('node', $node, 'field_more');
    $field_start_moments = field_get_items('node', $node, 'field_startmoment');

    // Start building HTML.
    $content .= '<ul class="extra bordered-list">';

    // Add type.
    if ($field_type) {
      $content .= '<li><h4>Type:</h4><p>'. taxonomy_term_load($field_type[0]['tid'])->name  .'</p></li>';
    }

    // Add studyforms.
    // Dit is niet langer nodig aangezien het verder op de pagina ook voorkomt
    /*if ($field_modes) {
      $modes = array();
      foreach ($field_modes as $mode) {
        $modes[] = taxonomy_term_load($mode['tid'])->name;
      }
      $more = '';
      if ($field_modes_more) {
        global $base_url;
        $more = l('Lees meer', $base_url . $field_modes_more[0]['safe_value']);
      }
      $content .= '<li><h4>Studievormen:</h4><p>'. implode(', ', $modes) . '</p>' . $more . '</li>';
    }*/

    // Add start moments.
    if ($field_start_moments) {
      $start_moments = array();
      foreach ($field_start_moments as $start_moment) {
        $start_moments[] = taxonomy_term_load($start_moment['tid'])->name;
      }

      $label = format_plural(count($start_moments), 'Startmoment', 'Startmomenten');
      $content .= '<li><h4>' . $label . ':</h4><p>'. implode(', ', $start_moments) .'</p></li>';
    }

    $content .= '</ul>';

    // Right part of the block.
    $field_links = field_get_items('node', $node, 'field_links');
    if (!empty($field_links)) {
      $content .= '<div class="links">';

      $links = array();
      foreach ($field_links as $link) {
        $content .= l($link['title'], $link['url'], array('attributes' => array('class' => array('btn')))) . '<br />';
      }

      $content .= '</div>';
    }
  }

  if (!empty($content)) {
    $content = '<div class="education-links">'. $content .'</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'education_links';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_education_links_content_type_admin_title($subtype, $conf) {
  return t('Education links block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_education_links_content_type_admin_info($subtype, $conf) {
  return t('Education links block');
}
