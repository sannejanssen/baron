<?php

/**
 * @file
 * Plugin to handle the campus mobility block
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Campus mobility block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the campus mobility block.
 *
 */
function thomas_more_campus_mobility_content_type_render($subtype, $conf, $panel_args) {
  $node = menu_get_object();
  $content = '';


  if ($node && $node->type == 'campus') {
    $field_bus = field_get_items('node', $node, 'field_bus_stop');
    $field_train = field_get_items('node', $node, 'field_train_stop');
    $field_car = field_get_items('node', $node, 'field_car');
    $field_bike = field_get_items('node', $node, 'field_bike');

    if(!empty($field_bus)) {
      $content .= '<p class="mobility bus"><span class="icon">'. t('Bus') .'</span>' . $field_bus[0]['safe_value'] . '</p>';
    }

    if(!empty($field_train)) {
      $content .= '<p class="mobility train"><span class="icon">'. t('Train') .'</span>' . $field_train[0]['safe_value'] . '</p>';
    }

    if(!empty($field_car)) {
      $content .= '<p class="mobility car"><span class="icon">'. t('Car') .'</span>' . $field_car[0]['safe_value'] . '</p>';
    }

    if(!empty($field_bike)) {
      $content .= '<p class="mobility bike"><span class="icon">'. t('Bike') .'</span>' . $field_bike[0]['safe_value'] . '</p>';
    }
  }



  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'campus_mobility';
    $block->title       = 'Mobiliteit';
    $block->content     = $content;
    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_campus_mobility_content_type_admin_title($subtype, $conf) {
  return t('Campus mobility block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_campus_mobility_content_type_admin_info($subtype, $conf) {
  return t('Campus mobility block');
}
