<?php

/**
 * @file
 * Display Suite functions.
 */

/**
 * DS field: show the event date information.
 */
function baron_ds_event_date($field) {
  $node = $field['entity'];
  $date = field_get_items('node', $node, 'field_event_date');

  $date_event = date('Ymd', $date[0]['value']);
  $date_today = date('Ymd');

  $event_day = format_date($date[0]['value'], 'custom', 'd');
  $event_month = format_date($date[0]['value'], 'custom', 'm');
  $event_start = format_date($date[0]['value'], 'custom', 'H\ui');

  $output = '<div class="date-time-wrapper">';

  $output .= '<span class="date-wrapper">';

  if($date_event == $date_today) {
    $output .= '<span class="today">' . t('Today') . '</span>';
  }
  else {
    $output .= '<span class="day">' . $event_day . '</span>';
    $output .= '<span class="slash">/</span>';
    $output .= '<span class="month">' . $event_month . '</span>';

  }

  $output .= '</span>';

  $output .= '<span class="time-wrapper">';
  $output .= '<span class="start">' .  $event_start . '</span>';
  $output .= '</span>';

  $output .= '</div>'; // end date-time.

  return $output;
}
