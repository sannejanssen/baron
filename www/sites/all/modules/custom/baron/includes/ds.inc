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

  $event_day = format_date($date[0]['value'], $type = 'custom', $format = 'd');
  $event_month = format_date($date[0]['value'], $type = 'custom', $format = 'm');
  $event_start = format_date($date[0]['value'], $type = 'custom', $format = 'H\ui');

  dsm('Day: ' . $event_day);
  dsm('Month: ' . $event_month);
  dsm('Start: ' . $event_start);

  $output = '<div class="date-time">';

  $output .= '<span class="date">';
  $output .= '<span class="day">' . $event_day . '</span>';
  $output .= '<span class="slash">/</span>';
  $output .= '<span class="month">' . $event_month . '</span>';
  $output .= '</span>';

  $output .= '<span class="time">' . $event_start . '</span>';

  $output .= '</div>'; // end date-time.

  return $output;
}
