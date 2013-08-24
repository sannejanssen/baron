<?php

/**
 * @file
 * Plugin to handle event/news detail information.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Detailed event/news information'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the event/news detail information.
 */
function thomas_more_detail_information_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();

  if ($node && $node->type == 'event' || $node->type == 'news') {
    $date = field_get_items('node', $node, 'field_date');
    $address = field_get_items('node', $node, 'field_adress');
    $type = field_get_items('node', $node, 'field_event_type');
    $contact_info = field_get_items('node', $node, 'field_contact_info');

    $content .= '<ul class="bordered-list">';

    if (!empty($contact_info)) {

      $content .= '<li>';
      $content .= '<h3>' . t('Contact') . '</h3>';
      $content .= '<p>' . $contact_info[0]['safe_value'] . '</p>';
      $content .= '</li>';
    }

    if (!empty($type)) {
      $type_term = taxonomy_term_load($type[0]['tid']);

      $content .= '<li>';
      $content .= '<h3>' . t('Type') . '</h3>';
      $content .= '<p>' . $type_term->name . '</p>';
      $content .= '</li>';
    }

    if (!empty($date)) {
      if ($date[0]['value'] == $date[0]['value2']) {
      // End date not provided or the same as startdate.
        $content .= '<li>';
        $content .= '<h3>' . t('Date') . '</h3>';
        if ($node->type == 'news') {
          $content .= '<p>' . format_date($date[0]['value'], 'full') . '</p>';
        }
        else {
          $content .= '<p>' . format_date($date[0]['value'], 'full') . ' ' . t('at') . ' ' . format_date($date[0]['value'], 'time') . '</p>';
        }
        $content .= '</li>';
      }
      else {
        // End date is different than start date.
        $content .= '<li>';
        $content .= '<h3>' . t('Date') . '</h3>';
        $content .= '<p>' . t('Start:') . ' ' . format_date($date[0]['value'], 'full') . ' ' . t('at') . ' ' . format_date($date[0]['value'], 'time') . '<br />';
        $content .= t('End:') . ' ' . format_date($date[0]['value2'], 'full') . ' ' . t('at') . ' ' . format_date($date[0]['value2'], 'time') . '</p>';
        $content .= '</li>';
      }
    }

    if (!empty($address)) {
      $content .= '<li>';
      $content .= '<h3>' . t('Location') . '</h3>';
      $content .= '<p>' . $address[0]['safe_value'] . '</p>';
      $content .= '</li>';
    }
    $content .= '</ul>';
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'detail_information';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_detail_information_content_type_admin_title($subtype, $conf) {
  return t('Detailed event/news information');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_detail_information_content_type_admin_info($subtype, $conf) {
  return t('Detailed event/news information');
}
