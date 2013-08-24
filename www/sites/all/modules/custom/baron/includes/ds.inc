<?php

/**
 * @file
 * Display Suite functions.
 */

/**
 * DS field: show the event date information.
 */
function baron_ds_event_date($field) {


/*
  $node = $field['entity'];

  $field_bus = field_get_items('node', $node, 'field_bus_stop');
  $field_train = field_get_items('node', $node, 'field_train_stop');
  $field_car = field_get_items('node', $node, 'field_car');
  $field_bike = field_get_items('node', $node, 'field_bike');
  $content = '';

  if(!empty($field_bus)) {
    $content .= '<span class="mobility bus"><div class="icon">'. t('Bus') .'</div>'. $field_bus[0]['safe_value'] . '</span>';
  }

  if(!empty($field_train)) {
    $content .= '<span class="mobility train"><div class="icon">'. t('Train') .'</div>'. $field_train[0]['safe_value'] . '</span>';
  }

  if(!empty($field_car)) {
    $content .= '<span class="mobility car"><div class="icon">'. t('Car') .'</div>'. $field_car[0]['safe_value'] . '</span>';
  }

  if(!empty($field_bike)) {
    $content .= '<span class="mobility bike"><div class="icon">'. t('Bike') .'</div>'. $field_bike[0]['safe_value'] . '</span>';
  }

  if ($content != '') {
    $content = '<span class="label-inline label line">' . t('Mobility') . '</span>' . $content;
  }
  return $content;
  */

  return "Sanne";

}
