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
  'title' => t('Education study form block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the education study form block.
 */
function thomas_more_education_study_form_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();
  if ($node && $node->type == 'education') {

    $field_title = field_get_items('node', $node, 'field_studievormen_titel');
    $field_intro = field_get_items('node', $node, 'field_studievormen_intro');
    //$field_forms = field_get_items('node', $node, 'field_studievormen');
		$field_modes_more = field_get_items('node', $node, 'field_more');

    if (!empty($field_intro)) {
      $content .= $field_intro['0']['safe_value'];
    }

    /*if (!empty($field_forms)) {
      $forms = array();
      $i = 0;
      foreach ($field_forms as $form) {
        if ($i == 0) {
          $forms[] = taxonomy_term_load($form['tid'])->name;
        }
        else {
          $forms[] = strtolower(taxonomy_term_load($form['tid'])->name);
        }
        $i++;
      }
      $content .= '<p>'. implode(', ', $forms) .'</p>';
    }*/
    if (!empty($field_modes_more)) {
    	global $base_url;
    	$content .= '<p>'. l('Lees meer', $base_url . $field_modes_more[0]['safe_value']) .'</p>';
    }

  }

  if (!empty($content)) {
    $content = '<div class="education-study-form">'. $content .'</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'education_forms';
    $block->title       = $field_title['0']['safe_value'] ;
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_education_study_form_content_type_admin_title($subtype, $conf) {
  return t('Education study form block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_education_study_form_content_type_admin_info($subtype, $conf) {
  return t('Education study form block');
}
